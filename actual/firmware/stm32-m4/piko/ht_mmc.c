/**
 * @file    ht_mmc.c
 * @brief   MMC-SPI FAT-FS code.
 *
 * @addtogroup Storage
 * @{
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "ch.h"
#include "hal.h"
#include "ff.h"

#include "chprintf.h"

#include "ht_config.h"

#include "ht_mmc.h"
#include "ht_led.h"
#include "ht_audio.h"
#include "ht_metri.h"
#include "ht_console.h"

extern uint8_t mode_led;
extern uint8_t mode_status;

/**
 * @brief Global MMC Driver Pointer
 */
MMCDriver MMCD1;

/**
 * @brief Save file last number variable
 */
uint16_t lastnum;

/**
 * @brief Gobal MMC Initialization Status
 */
FRESULT mmc_check_status = FR_OK;

/**
 * @brief FatFS ready status flag
 */
static bool filesystem_ready = true;

/**
 * @brief MMC SPI Peripheral status flag
 */
static uint8_t mmc_spi_status_flag = MMC_SPI_OK;

/**
 * @brief Maximum speed SPI config
 * @details CPHA=0, CPOL=0, MSb first.
 */
const SPIConfig hs_spicfg = {
#ifdef CH_20
  false,
#endif

  NULL,
  GPIOA,
  15,

#ifdef ST_F401RE
  0, 0
#endif

#ifdef ST_F303RC
  0, SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0
#endif
};

/**
 * @brief Low speed SPI config
 * @details CPHA=0, CPOL=0, MSb first.
 */
const SPIConfig ls_spicfg = {
#ifdef CH_20
  false,
#endif

  NULL,
  GPIOA,
  15,

#ifdef ST_F401RE
  SPI_CR1_BR_2 | SPI_CR1_BR_1, 0
#endif

#ifdef ST_F303RC
  SPI_CR1_BR_2 | SPI_CR1_BR_1,
  SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0
#endif
};

/**
 * @brief MMC config struct
 */
static MMCConfig mmccfg = {&SPID3, &ls_spicfg, &hs_spicfg};

/**
 * @brief Buffer to store all JSON string parts
 */
static char buffMetriOnce[1250];

/*******************************************/

/**
 * @brief Parse filename string
 * @param String filename as input
 * @param String part filename as output
 * @param Position to look up
 * @param Separator character
 */
static void string_parse(char *strIn, char *strOut, uint8_t pos, char sep){
    char strInput[90];
    char strSplit[3][30];
    uint8_t i,j,cnt;

    strcpy(strInput,strIn);
    j=0; cnt=0;
    for(i=0;i<=strlen(strInput);i++){
        if(strInput[i]==' ' || strInput[i]=='\0' || strInput[i]==sep){
            strSplit[cnt][j]='\0';
            cnt++;
            j=0;
        }
        else {
            strSplit[cnt][j]=strInput[i];
            j++;
        }
    }

    strcpy(strOut,strSplit[pos]);
}

/**
 * @brief Get file number from filename string
 * @param String filename as input
 * @return Last file number
 */
static uint16_t get_fnum(char *strIn){
    char buffer[64];
    char filenum[16];
    uint16_t numOut;

    string_parse(strIn,buffer,1,'_');
    string_parse(buffer,filenum,0,'.');
    numOut = atoi(filenum);

    return numOut;
}

/**
 * @brief Scan file on MMC and get last (biggest) number
 * @param Drive path
 * @param Last file number
 * @param Show option (0: No List, 1: File number, 2: File names)
 * @return
 */
static FRESULT scanFiles(char *path, uint16_t *lastfnum, uint8_t showList){
    char strbuff[COMM_BUFF_SIZE];
    FRESULT err;
    DIR Dir;
    FILINFO Fno;
    uint16_t fnum;

    if(showList==LS_JSONNUM){
        ht_commUSB_Msg("{\"filelist\": {");
    }

    *lastfnum=0;
    err = f_opendir(&Dir,path);
    if(err==FR_OK){
        while(1){
            err=f_readdir(&Dir,&Fno);
            if(err!=FR_OK || Fno.fname[0]==0)break;

            if(!(Fno.fattrib & AM_DIR)){
                fnum = get_fnum(Fno.fname);
                if(*lastfnum<=fnum)*lastfnum=fnum;

                if(showList==LS_SHOWLIST){
                  ht_comm_Buff(strbuff,sizeof(strbuff),"%s\r\n",Fno.fname);
                  ht_commUSB_Msg(strbuff);
                }
                else if(showList==LS_SHOWNUM || showList==LS_JSONNUM){
                    ht_comm_Buff(strbuff,sizeof(strbuff),"%i, ",fnum);
                    ht_commUSB_Msg(strbuff);
                }
            }
        }

        if(showList==LS_SHOWNUM){
          ht_comm_Buff(strbuff,sizeof(strbuff),"0\r\n");
          ht_commUSB_Msg(strbuff);
        }
        else if(showList==LS_JSONNUM){
            ht_comm_Buff(strbuff,sizeof(strbuff),",0}}\r\n");
            ht_commUSB_Msg(strbuff);
        }

        f_closedir(&Dir);
    }
    return err;
}

/**
 * @brief Checking readiness FatFS
 * @details Must calling before mounting actual media MMC
 * @details Checking both Peripheral and Filesystem status
 * @param[in] uint8_t Status to change LED mode or not
 */
static FRESULT mmc_check(void){
    FATFS FatFs;
    FRESULT err;

    uint32_t clusters;
    FATFS *fsp;

    mmc_spi_status_flag=MMC_SPI_OK;
    filesystem_ready=false;
    err = FR_OK;

    if(mmcConnect(&MMCD1)){
        filesystem_ready = true;
        f_mount(&FatFs, "", 0);
    }
    else{
        err = f_mount(&FatFs, "", 0);
        if(err == FR_OK){
            filesystem_ready = true;
        }
        else{
            if(mode_led!=LED_METRI)mode_led=LED_FAIL;
            return err;
        }
    }

    if(!filesystem_ready){
        mmc_spi_status_flag=MMC_SPI_FAIL;
        if(mode_led!=LED_METRI)mode_led=LED_FAIL;
        return err;
    }

    mmc_spi_status_flag=MMC_SPI_ERROR;
    err = f_getfree("", &clusters, &fsp);
    if(err == FR_OK){
        mmc_spi_status_flag=MMC_SPI_OK;
        if(mode_led!=LED_METRI)mode_led=LED_READY;
    }
    else{
        if(mode_led!=LED_METRI)mode_led=LED_FAIL;
        return err;
    }

    f_mount(0, "", 0);

    return err;
}

/*******************************************/

void ht_mmc_InitCheck(void){
    FATFS FatFs;

    uint32_t clusters;
    FATFS *fsp;

    mmc_spi_status_flag=MMC_SPI_OK;
    filesystem_ready=false;

    if(mmcConnect(&MMCD1)){
        filesystem_ready = true;
        mmc_check_status = f_mount(&FatFs, "", 0);
        if(mmc_check_status != FR_OK){
            if(mode_led!=LED_METRI)mode_led=LED_FAIL;
            return;
        }
    }
    else{
        mmc_check_status = f_mount(&FatFs, "", 0);
        if(mmc_check_status == FR_OK){
            filesystem_ready = true;
        }
        else{
            if(mode_led!=LED_METRI)mode_led=LED_FAIL;
            return;
        }
    }

    if(!filesystem_ready){
        mmc_spi_status_flag=MMC_SPI_FAIL;
        if(mode_led!=LED_METRI)mode_led=LED_FAIL;
        return;
    }

    mmc_spi_status_flag=MMC_SPI_ERROR;
    mmc_check_status = f_getfree("", &clusters, &fsp);
    if(mmc_check_status == FR_OK){
        mmc_spi_status_flag=MMC_SPI_OK;
        if(mode_led!=LED_METRI)mode_led=LED_READY;
    }
    else{
        if(mode_led!=LED_METRI)mode_led=LED_FAIL;
        return;
    }

    f_mount(0, "", 0);

    ht_mmc_Delay();
}

/*******************************************/

void ht_mmc_testWrite(void){
    char buffer[MMC_STR_BUFF_SIZE];
    char strbuff[COMM_BUFF_SIZE];

    FATFS FatFs;
    FIL *Fil;
    UINT bw;
    FRESULT err;

    Fil = (FIL*)malloc(sizeof(FIL));

    err = mmc_check();
    if(err!=FR_OK){
        ht_comm_Buff(strbuff,sizeof(strbuff),"MMC Error code = %i\r\n",err);
        ht_commUSB_Msg(strbuff);
        return;
    }

    if( (filesystem_ready==true) && (mmc_spi_status_flag==MMC_SPI_OK) ){
        ht_mmc_Buff(buffer,sizeof(buffer),"Test\n");

        f_mount(&FatFs, "", 0);

        err = f_open(Fil, "/HTTEST.TXT", FA_WRITE | FA_READ | FA_OPEN_ALWAYS);
        if(err==FR_OK){
            f_lseek(Fil, f_size(Fil));
            f_write(Fil, buffer, strlen(buffer), &bw);
            f_close(Fil);
            ht_commUSB_Msg("MMC R/W Test Success\r\n");
            mode_led=LED_READY;
        }
        else{
            ht_comm_Buff(strbuff,sizeof(strbuff),"MMC Error code = %i\r\n",err);
            ht_commUSB_Msg(strbuff);
            mode_led=LED_FAIL;
        }

        f_mount(0, "", 0);
    }
    free(Fil);

    ht_mmc_Delay();
}

void ht_mmc_testCat(void){
    uint16_t line_num=0;
    char buffer[MMC_STR_BUFF_SIZE];
    char fname[MMC_FNAME_SIZE];
    char strbuff[COMM_BUFF_SIZE];

    FATFS FatFs;
    FIL *Fil;
    FRESULT err;

    Fil = (FIL*)malloc(sizeof(FIL));

    err = mmc_check();
    if(err!=FR_OK){
        ht_comm_Buff(strbuff,sizeof(strbuff),"MMC Error code = %i\r\n",err);
        ht_commUSB_Msg(strbuff);
        return;
    }

    strcpy(buffer,"");
    ht_mmc_Buff(fname,sizeof(fname),"/HTTEST.TXT");
    if( (filesystem_ready==true) && (mmc_spi_status_flag==MMC_SPI_OK) ){
        f_mount(&FatFs, "", 0);

        err=f_open(Fil, fname, FA_OPEN_EXISTING |FA_READ);
        if(err==FR_OK){
            char line[MMC_STR_BUFF_SIZE];
            TCHAR *eof;
            while(1){
                line_num++;
                strcpy(line,"");
                eof=f_readline(line,sizeof(line),Fil);
                if(eof[0]==0)break;

                // remove CR+LF so string is content only
                line[strcspn(line, "\r\n")] = 0;

                ht_comm_Buff(strbuff,sizeof(strbuff),"%3i %s\r\n",line_num,line);
                ht_commUSB_Msg(strbuff);
            }
            ht_comm_Buff(strbuff,sizeof(strbuff),"\r");
            ht_commUSB_Msg(strbuff);

            f_close(Fil);
        }
        else{
            ht_comm_Buff(strbuff,sizeof(strbuff),"Open Error:%d\r\n",err);
            ht_commUSB_Msg(strbuff);
        }

        f_mount(0, "", 0);
    }
    free(Fil);

    ht_mmc_Delay();
}

/*******************************************/

void ht_mmc_lsFiles(uint8_t showList){
    FATFS FatFs;
    FIL *Fil;
    FRESULT err;

    char buff[MMC_STR_BUFF_SIZE];
    char fname[MMC_FNAME_SIZE];

    Fil = (FIL*)malloc(sizeof(FIL));

    if(mmc_check()!=FR_OK){return;}

    if( (filesystem_ready==true) && (mmc_spi_status_flag==MMC_SPI_OK) ){
        err = f_mount(&FatFs,"",0);
        if(err==FR_OK){
            strcpy(buff,"/");
            err = scanFiles(buff, &lastnum, showList);
            if(err==FR_OK){
                if(lastnum < FILE_MAX_NUM){
                    ht_mmc_Buff(fname,sizeof(fname),"/HT_%i.TXT",lastnum);

                    err = f_open(Fil, fname, FA_READ | FA_OPEN_EXISTING);
                    if(err==FR_OK){
                        f_close(Fil);
                    }
                }
                else{
                    ht_commUSB_Msg("Warning: Maximum save number\r\n");
                }
            }
        }
        f_mount(0, "", 0);
    }
    free(Fil);

    ht_mmc_Delay();
}

void ht_mmc_catFiles(uint16_t fnum, uint8_t lineType){
    char strbuff[COMM_BUFF_SIZE];
    char fname[MMC_FNAME_SIZE];
    FATFS FatFs;
    FIL *Fil;
    FRESULT err;

    Fil = (FIL*)malloc(sizeof(FIL));

    if(mmc_check()!=FR_OK){return;}

    ht_mmc_Buff(fname,sizeof(fname),"/HT_%i.TXT",fnum);
    if( (filesystem_ready==true) && (mmc_spi_status_flag==MMC_SPI_OK) ){
        f_mount(&FatFs, "", 0);

        err=f_open(Fil, fname, FA_OPEN_EXISTING |FA_READ);
        if(err==FR_OK){
            char line[MMC_STR_BUFF_SIZE];
            TCHAR *eof;
            while(1){
                strcpy(line,"");
                eof=f_readline(line,sizeof(line),Fil);
                if(eof[0]==0)break;

                // remove CR+LF so string is content only
                line[strcspn(line, "\r\n")] = 0;

                if(lineType==CAT_SINGLE_LINE){
                  ht_comm_Buff(strbuff,sizeof(strbuff),"%s",line);
                }
                else{
                  ht_comm_Buff(strbuff,sizeof(strbuff),"%s\r\n",line);
                }
                ht_commUSB_Msg(strbuff);
            }
            ht_comm_Buff(strbuff,sizeof(strbuff),"\r\n");
            ht_commUSB_Msg(strbuff);

            f_close(Fil);
        }
        else{
            ht_comm_Buff(strbuff,sizeof(strbuff),"Open Error:%d\r\n",err);
            ht_commUSB_Msg(strbuff);
        }

        f_mount(0, "", 0);
    }
    free(Fil);

    ht_mmc_Delay();
}

void ht_mmc_formatFS(void){
    char strbuff[COMM_BUFF_SIZE];
    FRESULT err;
    BYTE work[FF_MAX_SS];

#ifdef CH_20
    err = f_mkfs("", 0, work, sizeof work);
#endif

#ifdef CH_17
    err = f_mkfs("", FM_ANY, 0, work, sizeof work);
#endif

    if(err==FR_OK){
        ht_commUSB_Msg("Formatting Completed\r\n");
    }
    else{
        ht_comm_Buff(strbuff,sizeof(strbuff),"MMC Error %2i\r\n",err);
        ht_commUSB_Msg(strbuff);
    }
}

/*******************************************/

void ht_mmcMetri_chkFile(void){
#if USER_METRI_USELOG
    char strbuff[COMM_BUFF_SIZE];
#endif

    FATFS FatFs;
    FIL *Fil_last;
    FIL *Fil_new;
    FRESULT err;

    char buff[MMC_STR_BUFF_SIZE];
    char buffer[MMC_STR_BUFF_SIZE];
    char fname[MMC_FNAME_SIZE];

    Fil_last = (FIL*)malloc(sizeof(FIL));
    Fil_new = (FIL*)malloc(sizeof(FIL));

    if(mmc_check()!=FR_OK){return;}

    if( (filesystem_ready==true) && (mmc_spi_status_flag==MMC_SPI_OK) ){

        ht_mmc_Buff(buffer,sizeof(buffer),"{\"audiogram\":{\n");

        err = f_mount(&FatFs,"",0);
        if(err==FR_OK){
            strcpy(buff,"/");
            err = scanFiles(buff, &lastnum, LS_NOSHOW);

            // Record save file always start at 1
            if(lastnum==0) lastnum=1;

            if(lastnum < FILE_MAX_NUM){
                ht_mmc_Buff(fname,sizeof(fname),"/HT_%i.TXT",lastnum);

                err = f_open(Fil_last, fname, FA_READ | FA_OPEN_EXISTING);
                if(err==FR_OK){
                    f_close(Fil_last);
                    lastnum++;

#if USER_METRI_USELOG
                    ht_comm_Buff(strbuff,sizeof(strbuff),"File %s exist\r\n",fname);
                    ht_commUSB_Msg(strbuff);
                    ht_commUSB_Msg("File name incremented\r\n");
#endif
                    ht_mmc_Buff(fname,sizeof(fname),"/HT_%i.TXT",lastnum);
                    strcpy(buffMetriOnce, buffer);
                }
                else if(err==FR_NO_FILE){
#if USER_METRI_USELOG
                    ht_comm_Buff(strbuff,sizeof(strbuff),"File %s not exist\r\n",fname);
                    ht_commUSB_Msg(strbuff);
                    ht_commUSB_Msg("File name start new\r\n");
#endif
                    ht_mmc_Buff(fname,sizeof(fname),"/HT_%i.TXT",lastnum);
                    strcpy(buffMetriOnce, buffer);
                }
                else{
#if USER_METRI_USELOG
                    ht_comm_Buff(strbuff,sizeof(strbuff),"File %s error code = %i\r\n",fname,err);
                    ht_commUSB_Msg(strbuff);
#endif
                    mode_status = STT_IDLE;
                    mode_led = LED_READY;
                }
            }
            else{
                mode_status = STT_IDLE;
                mode_led = LED_READY;

#if USER_METRI_USELOG
                ht_commUSB_Msg("Warning: Maximum save number\r\n");
#endif
            }
        }
    }
    free(Fil_last);
    free(Fil_new);

    ht_mmc_Delay();
}

void ht_mmcMetri_chkFileBuffer(void){
#if USER_METRI_USELOG
    char strbuff[COMM_BUFF_SIZE];
#endif

    FATFS FatFs;
    FIL *Fil_last;
    FIL *Fil_new;
    FRESULT err;

    char buff[MMC_STR_BUFF_SIZE];
    char fname[MMC_FNAME_SIZE];

    Fil_last = (FIL*)malloc(sizeof(FIL));
    Fil_new = (FIL*)malloc(sizeof(FIL));

    if(mmc_check()!=FR_OK){return;}

    if( (filesystem_ready==true) && (mmc_spi_status_flag==MMC_SPI_OK) ){

        err = f_mount(&FatFs,"",0);
        if(err==FR_OK){
            strcpy(buff,"/");
            err = scanFiles(buff, &lastnum, LS_NOSHOW);

            // Record save file always start at 1
            if(lastnum==0) lastnum=1;

            if(lastnum < FILE_MAX_NUM){
                ht_mmc_Buff(fname,sizeof(fname),"/HT_%i.TXT",lastnum);

                err = f_open(Fil_last, fname, FA_READ | FA_OPEN_EXISTING);
                if(err==FR_OK){
                    f_close(Fil_last);
                    lastnum++;

#if USER_METRI_USELOG
                    ht_comm_Buff(strbuff,sizeof(strbuff),"File %s exist\r\n",fname);
                    ht_commUSB_Msg(strbuff);
                    ht_commUSB_Msg("File name incremented\r\n");
#endif
                    ht_mmc_Buff(fname,sizeof(fname),"/HT_%i.TXT",lastnum);
                }
                else if(err==FR_NO_FILE){
#if USER_METRI_USELOG
                    ht_comm_Buff(strbuff,sizeof(strbuff),"File %s not exist\r\n",fname);
                    ht_commUSB_Msg(strbuff);
                    ht_commUSB_Msg("File name start new\r\n");
#endif
                    ht_mmc_Buff(fname,sizeof(fname),"/HT_%i.TXT",lastnum);
                }
                else{
#if USER_METRI_USELOG
                    ht_comm_Buff(strbuff,sizeof(strbuff),"File %s error code = %i\r\n",fname,err);
                    ht_commUSB_Msg(strbuff);
#endif
                    mode_status = STT_IDLE;
                    mode_led = LED_READY;
                }
            }
            else{
                mode_status = STT_IDLE;
                mode_led = LED_READY;

#if USER_METRI_USELOG
                ht_commUSB_Msg("Warning: Maximum save number\r\n");
#endif
            }
        }
    }
    free(Fil_last);
    free(Fil_new);

    ht_mmc_Delay();
}

void ht_mmcMetri_endResult(void){
    char buffer[MMC_STR_BUFF_SIZE];
    char fname[MMC_FNAME_SIZE];
    FATFS FatFs;
    FIL *Fil;
    UINT bw;
    FRESULT err;

    Fil = (FIL*)malloc(sizeof(FIL));

    if(mmc_check()!=FR_OK){return;}

    if( (filesystem_ready==true) && (mmc_spi_status_flag==MMC_SPI_OK) ){
        ht_mmc_Buff(buffer,sizeof(buffer),"\n}\n}");
        strcat(buffMetriOnce, buffer);
        if(lastnum < FILE_MAX_NUM){
            f_mount(&FatFs, "", 0);

            ht_mmc_Buff(fname,sizeof(fname),"/HT_%i.TXT",lastnum);
            err = f_open(Fil, fname, FA_WRITE | FA_READ | FA_CREATE_ALWAYS);
            if(err==FR_OK){
                f_lseek(Fil, f_size(Fil));
                ht_commUSB_Msg(buffMetriOnce);
                f_write(Fil, buffMetriOnce, strlen(buffMetriOnce), &bw);
                f_close(Fil);
            }

            f_mount(0, "", 0);
        }
        else{
            mode_status = STT_IDLE;
            mode_led = LED_READY;

#if USER_METRI_USELOG
            ht_commUSB_Msg("Warning: Maximum save number\r\n");
#endif
        }
    }
    free(Fil);

    ht_mmc_Delay();
}

void ht_mmcMetri_bufferSave(void){
    char fname[MMC_FNAME_SIZE];
    FATFS FatFs;
    FIL *Fil;
    UINT bw;
    FRESULT err;

    Fil = (FIL*)malloc(sizeof(FIL));

    if(mmc_check()!=FR_OK){return;}

    if( (filesystem_ready==true) && (mmc_spi_status_flag==MMC_SPI_OK) ){
        if(lastnum < FILE_MAX_NUM){
            f_mount(&FatFs, "", 0);

            ht_mmc_Buff(fname,sizeof(fname),"/HT_%i.TXT",lastnum);
            err = f_open(Fil, fname, FA_WRITE | FA_READ | FA_CREATE_ALWAYS);
            if(err==FR_OK){
                f_lseek(Fil, f_size(Fil));
                ht_commUSB_Msg(buffMetriOnce);
                f_write(Fil, buffMetriOnce, strlen(buffMetriOnce), &bw);
                f_close(Fil);
            }

            f_mount(0, "", 0);
        }
        else{
            mode_status = STT_IDLE;
            mode_led = LED_READY;

#if USER_METRI_USELOG
            ht_commUSB_Msg("Warning: Maximum save number\r\n");
#endif
        }
    }
    free(Fil);

    ht_mmc_Delay();
}

void ht_mmcMetri_bufferShow(void){
    ht_commUSB_Msg("Buffer Content:\r\n");
    ht_commUSB_Msg(buffMetriOnce);
}

/*******************************************/

void ht_mmcOnceMetri_jsonChStart(uint8_t lr_ch){
  char buffer[MMC_STR_BUFF_SIZE];

  if(lr_ch==OUT_LEFT){
      ht_mmc_Buff(buffer,sizeof(buffer),"\n\"ch_0\":{");
  }
  else if(lr_ch==OUT_RIGHT){
      ht_mmc_Buff(buffer,sizeof(buffer),",\n\"ch_1\":{");
  }

  strcat(buffMetriOnce, buffer);
}

void ht_mmcOnceMetri_jsonChClose(void){
  char buffer[MMC_STR_BUFF_SIZE];
  ht_mmc_Buff(buffer,sizeof(buffer),"}");

  strcat(buffMetriOnce, buffer);
}

void ht_mmcOnceMetri_jsonComma(void){
  char buffer[MMC_STR_BUFF_SIZE];
  ht_mmc_Buff(buffer,sizeof(buffer),",");

  strcat(buffMetriOnce, buffer);
}

void ht_mmcOnceMetri_hearingResult(double freq, uint8_t freqidx, uint8_t ample){
  char buffer[MMC_STR_BUFF_SIZE];
  ht_mmc_Buff(buffer,sizeof(buffer),"\n\"freq_%i\":{\"freq\":%6.3f,\"ampl\":%i,", freqidx, freq, ample);

  strcat(buffMetriOnce, buffer);
}

void ht_mmcOnceMetri_hearingRecord(uint8_t *resArray, uint8_t lastIdx, uint8_t lastAmpl){
  char buffer[MMC_STR_BUFF_SIZE];
  uint8_t i;

  for(i=lastIdx;i<TEST_MAX_COUNT;i++){
      resArray[i] = lastAmpl;
  }

  ht_mmc_Buff(buffer,sizeof(buffer),"\"record\":[%i",resArray[0]);
  for(i=1;i<TEST_MAX_COUNT;i++){
      ht_mmc_Buff(buffer,sizeof(buffer),"%s,%i",buffer,resArray[i]);
  }
  ht_mmc_Buff(buffer,sizeof(buffer),"%s]}",buffer);

  strcat(buffMetriOnce, buffer);
}

/*******************************************/

void ht_mmc_Init(void){
    palSetPadMode(GPIOC, 12, PAL_MODE_ALTERNATE(6));    //MOSI
    palSetPadMode(GPIOC, 11, PAL_MODE_ALTERNATE(6));    //MISO
    palSetPadMode(GPIOC, 10, PAL_MODE_ALTERNATE(6));    //SCK
    palSetPadMode(GPIOA, 15, PAL_MODE_OUTPUT_PUSHPULL); //NSS
    palSetPad(GPIOA, 15);

    mmcObjectInit(&MMCD1);
    mmcStart(&MMCD1, &mmccfg);

    chThdSleepMilliseconds(500);
}

/** @} */
