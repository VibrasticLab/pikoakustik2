/**
 * @file    ht_console.c
 * @brief   Console Shell code.
 *
 * @addtogroup Console
 * @{
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "ch.h"
#include "hal.h"
#include "ff.h"

#include "shell.h"
#include "chprintf.h"

#include "ht_config.h"

#include "ht_usb.h"
#include "ht_mmc.h"
#include "ht_led.h"
#include "ht_pta.h"
#include "ht_metri.h"
#include "ht_audio.h"
#include "ht_console.h"
#include "msg_my.h"

extern uint16_t lastnum;
extern FRESULT mmc_check_status;

extern uint8_t mode_status;
extern uint8_t channel_stt;
extern uint8_t mode_led;
extern uint8_t freq_count;

extern uint16_t sineSize;
extern int16_t i2s_tx_buf[I2S_BUFF_SIZE];

extern uint8_t calAmpl[6][2];

/*******************************************
 * Serial Command Callback
 *******************************************/

/**
 * @brief Test command callback
 * @details Enumerated and not called directly by any normal thread
 */
static void cmd_coba(BaseSequentialStream *chp, int argc, char *argv[]){
    (void)argc;
    (void)argv;

    if (argc > 0) {
      chprintf(chp, "Usage: coba\r\n");
      return;
    }
    chprintf(chp,"Serial Console at %d & buffer size %d bit\r\n",SERIAL_DEFAULT_BITRATE,SERIAL_BUFFERS_SIZE);
}

/**
 * @brief Test command callback in both UART and USB-CDC
 * @details Enumerated and not called directly by any normal thread
 */
static void cmd_tes(BaseSequentialStream *chp, int argc, char *argv[]){
    (void)argc;
    (void)argv;

    if (argc > 0) {
      chprintf(chp, "Usage: tes\r\n");
      return;
    }

    ht_commUART_Msg("Serial Comm in UART\r\n");
    ht_commUSB_Msg("Serial Comm in USB\r\n");
}

/**
 * @brief Test command callback for LED testing
 * @details Enumerated and not called directly by any normal thread
 */
static void cmd_led(BaseSequentialStream *chp, int argc, char *argv[]){
    (void)argv;

    if (argc != 1) {
      chprintf(chp, "Usage: led [a|b|c|1|0]\r\n");
      return;
    }

    if(mode_led==LED_READY){
      led_answer_off();
      led_result_off();

      if(strcmp(argv[0], "a")==0){
        led_answerA();
      }
      else if(strcmp(argv[0], "b")==0){
        led_answerB();
      }
      else if(strcmp(argv[0], "c")==0){
        led_answerC();
      }
      else if(strcmp(argv[0], "1")==0){
        led_resultYES();
      }
      else if(strcmp(argv[0], "0")==0){
        led_resultNO();
      }
      else{
        chprintf(chp, "Usage: led [a|b|c|1|0]\r\n");
      }
    }
    else{
      chprintf(chp,"Only Works in IDLE mode\r\n");
    }
}

/**
 * @brief Test command callback for MMC Storage functionality
 * @details Enumerated and not called directly by any normal thread
 */
static void cmd_mmc(BaseSequentialStream *chp, int argc, char *argv[]) {
  if(argc < 1){
     chprintf(chp,"usage: mmc [test|ls|lsnum|lsjson|cat|stt|dump] <file-number>\r\n");
     return;
  }

#if USER_MMC
  if(strcmp(argv[0], "test")==0){
    ht_mmc_testWrite();
    ht_mmc_testCat();
    chprintf(chp,"MMC Test Finished\r\n");
  }
  else if(strcmp(argv[0], "ls")==0){
    ht_mmc_lsFiles(LS_SHOWLIST);
  }
  else if(strcmp(argv[0], "lsnum")==0){
    ht_mmc_lsFiles(LS_SHOWNUM);
  }
  else if(strcmp(argv[0], "lsjson")==0){
    ht_mmc_lsFiles(LS_JSONNUM);
  }
  else if(strcmp(argv[0], "cat")==0){
    if(argc == 2){
      ht_mmc_catFiles(atoi(argv[1]),CAT_SINGLE_LINE);
    }
  }
  else if(strcmp(argv[0], "stt")==0){
    chprintf(chp,"MMC Status %2i\r\n", mmc_check_status);
  }
  else if(strcmp(argv[0], "dump")==0){
    chprintf(chp,"Dumping Session Buffer to MMC\r\n");
    ht_mmcMetri_bufferSave();
    chprintf(chp,"Buffer Dumping Done\r\n");
  }
#else
  (void) argv;
#endif

}

/**
 * @brief Test command callback for Tone generation functionality
 * @details Enumerated and not called directly by any normal thread
 */
static void cmd_out(BaseSequentialStream *chp, int argc, char *argv[]) {
  uint8_t in_ampl;
  uint16_t in_freq;

  double vfreq=1;

  uint8_t lrc = 0;
  uint16_t tone_durr = 250;

  switch(argc){
    case 1:
      lrc = 0;
      in_freq = 500;

      if(strcmp(argv[0],"min")==0){
        in_ampl = 1;
      }

      if(strcmp(argv[0],"max")==0){
        in_ampl = 9;
      }

      break;

    case 2:
      lrc = 0;
      in_freq = atoi(argv[0]);
      in_ampl = atoi(argv[1]);
      break;

    case 3:
      lrc = atoi(argv[0]);;
      in_freq = atoi(argv[1]);
      in_ampl = atoi(argv[2]);
      break;

    case 4:
      lrc = atoi(argv[0]);
      in_freq = atoi(argv[1]);
      in_ampl = atoi(argv[2]);
      tone_durr = atoi(argv[3]);
      break;

    default:
      chprintf(chp,"usage: out <0/1> <freq> <ampl> <duration_ms>\r\n");
      return;
      break;
  }

  switch(lrc){
      case OUT_LEFT:
          ht_audio_LeftCh();
          break;

      case OUT_RIGHT:
          ht_audio_RightCh();
          break;
  }

  if(in_freq>=LOWEST_FREQ && in_freq<=8000){
      vfreq = (double) in_freq / 400; // 400 is known array length as default frequency
  }
  else{
      chprintf(chp,"frequency only between LOWEST_FREQ and 8000\r\n");
  }

  if(!(in_ampl>0 && in_ampl<12)){
      chprintf(chp,"amplitudo scaling only between 1 and 11\r\n");
      return;
  }

  ht_audio_ToneScale(vfreq, in_ampl);
  chprintf(chp,"Out: Freq:%5i Ampl:%2i\r\n",in_freq,in_ampl);

  ht_audio_Play(2*tone_durr);

  chprintf(chp,"Finished\r\n");
  ht_audio_DisableCh();
#ifdef PCB_P3
  ht_audio_LeftCh();
#endif
}

/**
 * @brief Test command callback for simpler Tone generation test
 * @details Enumerated and not called directly by any normal thread
 */
static void cmd_tone(BaseSequentialStream *chp, int argc, char *argv[]){
  if(argc != 1){chprintf(chp,"usage: tone [minl|minr|maxl|maxr]\r\n");return;}

  if(strcmp(argv[0],"minl")==0){
     ht_audio_LeftCh();
     ht_audio_ToneScale(1.25,1);
  }
  else if(strcmp(argv[0],"minr")==0){
      ht_audio_RightCh();
      ht_audio_ToneScale(1.25,1);
  }
  else if(strcmp(argv[0],"maxl")==0){
     ht_audio_LeftCh();
     ht_audio_ToneScale(1.25,9);
  }
  else if(strcmp(argv[0],"maxr")==0){
     ht_audio_RightCh();
     ht_audio_ToneScale(1.25,9);
  }

  ht_audio_Play(50*TEST_DURATION);
  ht_audio_DisableCh();
#ifdef PCB_P3
  ht_audio_LeftCh();
#endif
  chprintf(chp,"Finished\r\n");
}

#if USE_FULL_SINE
static void cmd_ori(BaseSequentialStream *chp, int argc, char *argv[]) {
  uint8_t in_ampl;
  uint16_t in_freq;

  double vfreq=1;

  uint8_t lrc = 0;
  uint16_t tone_durr = 500;

  switch(argc){
    case 1:
      lrc = 0;
      in_freq = 500;

      if(strcmp(argv[0],"min")==0){
        in_ampl = 1;
      }

      if(strcmp(argv[0],"max")==0){
        in_ampl = 9;
      }

      break;

    case 2:
      lrc = 0;
      in_freq = atoi(argv[0]);
      in_ampl = atoi(argv[1]);
      break;

    case 3:
      lrc = atoi(argv[0]);;
      in_freq = atoi(argv[1]);
      in_ampl = atoi(argv[2]);
      break;

    case 4:
      lrc = atoi(argv[0]);
      in_freq = atoi(argv[1]);
      in_ampl = atoi(argv[2]);
      tone_durr = atoi(argv[3]);
      break;

    default:
      chprintf(chp,"usage: ori <0/1> <freq> <ampl> <duration_ms>\r\n");
      return;
      break;
  }

  switch(lrc){
      case OUT_LEFT:
          ht_audio_LeftCh();
          break;

      case OUT_RIGHT:
          ht_audio_RightCh();
          break;
  }

  if(in_freq>=LOWEST_FREQ && in_freq<=8000){
      vfreq = (double) in_freq / 400; // 400 is known array length as default frequency
  }
  else{
      chprintf(chp,"frequency only between LOWEST_FREQ and 8000\r\n");
  }

  if(!(in_ampl>0 && in_ampl<12)){
      chprintf(chp,"amplitudo scaling only between 1 and 11\r\n");
      return;
  }

  ht_audio_ToneScaleNoAtt(vfreq, in_ampl);
  chprintf(chp,"Ori: Freq:%5i Ampl:%2i\r\n",in_freq,in_ampl);

  ht_audio_Play(5*tone_durr);

  chprintf(chp,"Finished\r\n");
  ht_audio_DisableCh();
 #ifdef PCB_P3
  ht_audio_LeftCh();
 #endif
}
#endif

/**
 * @brief Test command callback for Tone Signal generation functionality
 * @details Enumerated and not called directly by any normal thread
 */
static void cmd_sig(BaseSequentialStream *chp, int argc, char *argv[]) {
  uint8_t in_ampl;
  uint16_t in_freq;

  double vfreq=1;

  uint8_t lrc = 0;
  uint8_t tone_ori = 0;

  uint16_t i;

  switch(argc){
    case 1:
      lrc = 0;
      in_freq = 500;

      if(strcmp(argv[0],"min")==0){
        in_ampl = 1;
      }

      if(strcmp(argv[0],"max")==0){
        in_ampl = 9;
      }

      break;

    case 2:
      lrc = 0;
      in_freq = atoi(argv[0]);
      in_ampl = atoi(argv[1]);
      break;

    case 3:
      lrc = atoi(argv[0]);;
      in_freq = atoi(argv[1]);
      in_ampl = atoi(argv[2]);
      break;

    case 4:
      lrc = atoi(argv[0]);
      in_freq = atoi(argv[1]);
      in_ampl = atoi(argv[2]);
      tone_ori = atoi(argv[3]);
      break;

    default:
      chprintf(chp,"usage: sig <0/1> <freq> <ampl> <duration_ms>\r\n");
      return;
      break;
  }

  switch(lrc){
      case OUT_LEFT:
          ht_audio_LeftCh();
          break;

      case OUT_RIGHT:
          ht_audio_RightCh();
          break;
  }

  if(in_freq>=LOWEST_FREQ && in_freq<=8000){
      vfreq = (double) in_freq / 400; // 400 is known array length as default frequency
  }
  else{
      chprintf(chp,"frequency only between LOWEST_FREQ and 8000\r\n");
  }

  if(!(in_ampl>0 && in_ampl<12)){
      chprintf(chp,"amplitudo scaling only between 1 and 11\r\n");
      return;
  }

  if(tone_ori==0){
    ht_audio_ToneScale(vfreq, in_ampl);
  }
  else if(tone_ori==1){
    ht_audio_ToneScaleNoAtt(vfreq, in_ampl);
 }

  chprintf(chp,"===============\r\n");

  for(i=0;i<sineSize;i++){
      chprintf(chp,"%d,",i2s_tx_buf[i]);
  }

  chprintf(chp,"\r\n===============\r\n");
}

/**
 * @brief Test command callback for Virtual Test with True answer only
 * @details Enumerated and not called directly by any normal thread
 */
static void cmd_virt(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void)argv;
    if (argc != 0) {
      chprintf(chp, "Usage: virt\r\n");
      return;
    }

    chprintf(chp, "Run Virtual Test Start\r\n");
    chprintf(chp, "DONT PUSH ANY BUTTON\r\n");
    chprintf(chp, "\r\n");

#if USER_MMC
 #if USER_METRI_RECORD
    ht_mmc_InitCheck();
    if(mmc_check_status==FR_OK){
      ht_mmcMetri_chkFile();
      ht_mmcMetri_bufferOrder();
    }
    else{
      chprintf(chp,"MMC Failed\r\n");
      chprintf(chp,"MMC Status %2i\r\n", mmc_check_status);
      return;
    }

    ht_mmcOnceMetri_jsonChStart(channel_stt);

 #endif
#endif

    freq_count = 0;
    ht_metri_Progress(freq_count);

    mode_led = LED_METRI;
    mode_status = STT_VIRT;

#if USER_ESP32
  #if USER_ESPIOSTT
    my_iosttSTMrun(TRUE);
  #endif
#endif

}

/**
 * @brief Test command callback for Virtual Test with False answer only
 * @details Enumerated and not called directly by any normal thread
 */
static void cmd_triv(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void)argv;
    if (argc != 0) {
      chprintf(chp, "Usage: triv\r\n");
      return;
    }

    chprintf(chp, "Run Virtual Wrong Test Start\r\n");
    chprintf(chp, "DONT PUSH ANY BUTTON\r\n");
    chprintf(chp, "\r\n");

#if USER_MMC
 #if USER_METRI_RECORD
    ht_mmc_InitCheck();
    if(mmc_check_status==FR_OK){
      ht_mmcMetri_chkFile();
      ht_mmcMetri_bufferOrder();
    }
    else{
      chprintf(chp,"MMC Failed\r\n");
      chprintf(chp,"MMC Status %2i\r\n", mmc_check_status);
      return;
    }

    ht_mmcOnceMetri_jsonChStart(channel_stt);

 #endif
#endif

    freq_count = 0;
    ht_metri_Progress(freq_count);

    mode_led = LED_METRI;
    mode_status = STT_TRIV;

#if USER_ESP32
  #if USER_ESPIOSTT
    my_iosttSTMrun(TRUE);
  #endif
#endif

}

/**
 * @brief Test command callback for show buffer record in memory
 * @details Enumerated and not called directly by any normal thread
 */
static void cmd_bufr(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void) argv;
    if (argc != 0){
        chprintf(chp, "Usage: bufr\r\n");
        return;
    }

    ht_mmcMetri_bufferShow();
}

/*******************************************/

#if USER_ESP32

/**
 * @brief Test command callback for show PTA JSON
 * @details Enumerated and not called directly by any normal thread
 */
static void cmd_pta(BaseSequentialStream *chp, int argc, char *argv[]){
    uint16_t fileID = 0;
    int idJSON;
    char strjson[METRI_BUFFER_SIZE];
    char ptaJSON[COMM_BUFF_SIZE];
    char ptaComm[COMM_BUFF_SIZE];

    if (argc > 1){
        chprintf(chp, "Usage: pta <number>\r\n");
        return;
    }

    if(argc==0){
        fileID = ht_mmc_getLastNum();
    }
    else if(argc==1){
        fileID = atoi(argv[0]);
    }

    ht_mmc_catFilesBuffer(fileID,strjson);
    idJSON = ht_ptaParse(strjson);
    if(idJSON<0){
      return;
    }

    ht_ptaLoadArray(idJSON,strjson);
    ht_ptaFinalCSV(fileID,ptaJSON);

    ht_comm_Buff(ptaComm,sizeof(ptaComm),"mpta %s\r\n",ptaJSON);
    ht_commUSB_Msg(ptaComm);
    ht_commUART_Msg(ptaComm);
}

static void cmd_esp(BaseSequentialStream *chp, int argc, char *argv[]) {
    if(argc!=1){
        chprintf(chp,"Usage: esp [wifi]\r\n");
        return;
    }

    if(strcmp(argv[0],"wifi")==0){
        ht_commUSB_Msg("wifi 1\r\n");
        ht_commUART_Msg("wifi 1\r\n");
    }

}

static void cmd_aud(BaseSequentialStream *chp, int argc, char *argv[]) {
    uint8_t audPercent;
    uint8_t runPercent;
    char strProgress[10];

    if(argc!=1){
        chprintf(chp,"Usage: aud [percent]\r\n");
        return;
    }

    audPercent = atoi(argv[0]);
    if(audPercent<=0) {runPercent=0;}
    else if(audPercent>=100) {runPercent=100;}
    else{runPercent=audPercent;}

    ht_comm_Buff(strProgress, sizeof(strProgress),"aud %i\r\n", runPercent);
    ht_commUSB_Msg(strProgress);
    ht_commUART_Msg(strProgress);
}

#endif

/*******************************************/

/**
 * @brief Shell command and it's callback enumeration
 * @details Extending from internal shell's callback
 */
static const ShellCommand commands[] = {
  {"coba", cmd_coba},
  {"mmc", cmd_mmc},
  {"out", cmd_out},
  {"tes",cmd_tes},
#if USE_FULL_SINE
  {"ori", cmd_ori},
#endif
  {"led", cmd_led},
  {"sig", cmd_sig},
  {"tone", cmd_tone},
  {"virt", cmd_virt},
  {"triv", cmd_triv},
  {"bufr", cmd_bufr},
  {"pta", cmd_pta},
#if USER_ESP32
  {"esp", cmd_esp},
  {"aud", cmd_aud},
#endif
  {NULL, NULL}
};

/*******************************************
 * Serial Peripheral Setup
 *******************************************/

/**
 * @brief USB Shell Console pointer
 */
static thread_t *shelltp_usb = NULL;

/**
 * @brief UART Shell Console pointer
 */
static thread_t *shelltp_uart = NULL;

/**
 * @brief Shell Driver Config
 * @details Serial Interface using USB1 (SDU1)
 */
static const ShellConfig shell_usb_cfg = {
  (BaseSequentialStream *)&SDU1,
  commands
};

/**
 * @brief Shell Driver Config
 * @details Serial Interface using UART1 (SD1)
 */
static const ShellConfig shell_uart_cfg = {
  (BaseSequentialStream *)&SD1,
  commands
};


void ht_commUSB_Init(void){
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

    usbDisconnectBus(serusbcfg.usbp);
    usbStop(serusbcfg.usbp);
    chThdSleepMilliseconds(1500);
    usbStart(serusbcfg.usbp, &usbcfg);
    usbConnectBus(serusbcfg.usbp);
}

void ht_commUSB_shInit(void){
  if (!shelltp_usb && (SDU1.config->usbp->state == USB_ACTIVE)) {
    shelltp_usb = chThdCreateFromHeap(NULL, SHELL_WA_SIZE, "shell_usb", NORMALPRIO, shellThread, (void *)&shell_usb_cfg);
  }
  else {
    if (chThdTerminatedX(shelltp_usb)) {
        chThdRelease(shelltp_usb);
        shelltp_usb = NULL;
    }
  }
}

void ht_commUSB_Msg(char *string){
    if(SDU1.config->usbp->state == USB_ACTIVE){
        chprintf((BaseSequentialStream *)&SDU1,string);
    }
}

void ht_commUART_Init(void){

#ifdef CH_20
    // reconfigure overlap UART1 pins to reset
    palSetPadMode(GPIOC, 4,PAL_MODE_RESET); //TX
    palSetPadMode(GPIOC, 5,PAL_MODE_RESET); //RX
#endif

    palSetPadMode(GPIOA, 9,PAL_MODE_ALTERNATE(7)); //TX
    palSetPadMode(GPIOA,10,PAL_MODE_ALTERNATE(7)); //RX
    sdStart(&SD1,NULL);
}

void ht_commUART_shInit(void){
    if (!shelltp_uart) {
      shelltp_uart = chThdCreateFromHeap(NULL, SHELL_WA_SIZE, "shell_uart", NORMALPRIO, shellThread, (void *)&shell_uart_cfg);
    }
    else {
      if (chThdTerminatedX(shelltp_uart)) {
          chThdRelease(shelltp_uart);
          shelltp_uart = NULL;
      }
    }
}

void ht_commUART_Msg(char *string){
    chprintf((BaseSequentialStream *)&SD1,string);
}

/** @{ */
