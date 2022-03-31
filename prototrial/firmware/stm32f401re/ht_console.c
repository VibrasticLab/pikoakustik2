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

#include "shell.h"
#include "chprintf.h"

#include "ht_config.h"

#include "ht_usb.h"
#include "ht_mmc.h"
#include "ht_console.h"
#include "msg_my.h"

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

/*******************************************/

static void cmd_mmc(BaseSequentialStream *chp, int argc, char *argv[]) {
  if(argc != 1){chprintf(chp,"usage: mmc [test]\r\n");return;}

  if(strcmp(argv[0], "test")==0){
    ht_mmc_testWrite();
    ht_mmc_testCat();
    chprintf(chp,"MMC Test Finished\r\n");
  }
}

/*******************************************/

/**
 * @brief Shell command and it's callback enumeration
 * @details Extending from internal shell's callback
 */
static const ShellCommand commands[] = {
  {"coba", cmd_coba},
  {"mmc", cmd_mmc},
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
