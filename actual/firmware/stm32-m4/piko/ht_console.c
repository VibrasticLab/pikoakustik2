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
#include "ht_metri.h"
#include "ht_audio.h"
#include "ht_console.h"
#include "msg_my.h"

extern uint8_t lastnum;
extern FRESULT mmc_check_status;

extern uint8_t mode_status;
extern uint8_t channel_stt;
extern uint8_t mode_led;

extern uint16_t sineSize;
extern int16_t i2s_tx_buf[I2S_BUFF_SIZE];

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

static void cmd_mmc(BaseSequentialStream *chp, int argc, char *argv[]) {
  if(argc < 1){
     chprintf(chp,"usage: mmc [test|ls|lsnum|lsjson|cat|stt|mkfs] <file-number>\r\n");
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
  else if(strcmp(argv[0], "mkfs")==0){
 #if USER_MMC_MKFS
    chprintf(chp,"Formatting MMC\r\n");
    ht_mmc_formatFS();
 #endif
  }
#else
  (void) argv;
#endif

}

static void cmd_out(BaseSequentialStream *chp, int argc, char *argv[]) {
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

  if(in_freq>=250 && in_freq<=8000){
      vfreq = (double) in_freq / 400; // 400 is known array length as default frequency
  }
  else{
      chprintf(chp,"frequency only between 250 and 8000\r\n");
  }

  if(!(in_ampl>0 && in_ampl<12)){
      chprintf(chp,"amplitudo scaling only between 1 and 11\r\n");
      return;
  }

  ht_audio_ToneScale(vfreq, in_ampl);
  chprintf(chp,"Out: Freq:%5i Ampl:%2i\r\n",in_freq,in_ampl);

  ht_audio_Play(5*tone_durr);

  chprintf(chp,"Finished\r\n");
  ht_audio_DisableCh();
}

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

  if(in_freq>=250 && in_freq<=8000){
      vfreq = (double) in_freq / 400; // 400 is known array length as default frequency
  }
  else{
      chprintf(chp,"frequency only between 250 and 8000\r\n");
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
}
#endif

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

  if(in_freq>=250 && in_freq<=8000){
      vfreq = (double) in_freq / 400; // 400 is known array length as default frequency
  }
  else{
      chprintf(chp,"frequency only between 250 and 8000\r\n");
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

static void cmd_virt(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void)argv;
    if (argc != 0) {
      chprintf(chp, "Usage: metri [virt|who]\r\n");
      return;
    }

    chprintf(chp, "Run Virtual Test Start\r\n");
    chprintf(chp, "DONT PUSH ANY BUTTON\r\n");
    chprintf(chp, "Keep this Serial Terminal open!!\r\n"); // THIS SHOULDN'T BE PROBLEM
    chprintf(chp, "\r\n");

#if USER_MMC
 #if USER_METRI_RECORD
    ht_mmc_InitCheck();
    if(mmc_check_status==FR_OK){
      ht_mmcMetri_chkFile();
    }
    else{
      chprintf(chp, "MMC Failed\r\n");
      chprintf(chp,"MMC Status %2i\r\n", mmc_check_status);
      return;
    }

  #if USER_METRI_RECONCE
    ht_mmcOnceMetri_jsonChStart(channel_stt);
  #else
    ht_mmcMetri_jsonChStart(channel_stt);
  #endif

 #endif
#endif

    mode_led = LED_METRI;
    mode_status = STT_VIRT;
}

/*******************************************/

/**
 * @brief Shell command and it's callback enumeration
 * @details Extending from internal shell's callback
 */
static const ShellCommand commands[] = {
  {"coba", cmd_coba},
  {"mmc", cmd_mmc},
  {"out", cmd_out},
#if USE_FULL_SINE
  {"ori", cmd_ori},
#endif
  {"sig", cmd_sig},
  {"tone", cmd_tone},
  {"virt", cmd_virt},
  {"htstate", esp32_MsgStatus},
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
