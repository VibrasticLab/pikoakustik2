/**
 * @file    ht_usb.h
 * @brief   USB-CDC header.
 *
 * @addtogroup Console
 * @{
 */

#ifndef HT_USB_H
#define HT_USB_H

#ifdef PCB_P2_I2S_MODIFIED
#define usb_lld_connect_bus(usbp)
#define usb_lld_disconnect_bus(usbp)
#endif

extern const USBConfig usbcfg;
extern SerialUSBConfig serusbcfg;
extern SerialUSBDriver SDU1;

#endif // HT_USB_H

/** @} */
