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

#include "ht_led.h"
#include "ht_usb.h"
#include "ht_console.h"

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

/**
 * @brief Shell command and it's callback enumeration
 * @details Extending from internal shell's callback
 */
static const ShellCommand commands[] = {
  {"coba", cmd_coba},
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
 * @brief Shell Driver Config
 * @details Serial Interface using USB1 (SDU1)
 */
static const ShellConfig shell_usb_cfg = {
  (BaseSequentialStream *)&SDU1,
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

/** @{ */
