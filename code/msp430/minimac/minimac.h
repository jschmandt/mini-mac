#ifndef MINIMAC_CONFIG_H
#define MINIMAC_CONFIG_H

#include <msp430.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>


// ----- From SimpleUsbBackchannel
// Basic MSP430 and driverLib #includes
#include "driverlib/MSP430F5xx_6xx/wdt_a.h"
#include "driverlib/MSP430F5xx_6xx/ucs.h"
#include "driverlib/MSP430F5xx_6xx/pmm.h"
#include "driverlib/MSP430F5xx_6xx/sfr.h"

// USB API #includes
#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/types.h"
#include "USB_API/USB_Common/usb.h"

#include "USB_app/usbConstructs.h"

// Application #includes
#include "BCUart.h"           // Include the backchannel UART "library"
#include "hal.h"              // Modify hal.h to select your hardware

/**********************
 * Only use one of these HMACs at a time
 **********************/

//#define HMAC_MD5
//#include "md5.h"

//#define HMAC_SHA1
//#include "sha1.h"

#define HMAC_SHA256
#include "sha256.h"

//unsigned char *hmac(const unsigned char *key, unsigned char *message);
//unsigned char *minimac(unsigned char *mac, unsigned int space, unsigned char *message);

void hmac(const unsigned char *key, unsigned char *message, unsigned char *mac);
void minimac(unsigned char *mac, unsigned int space, unsigned char *message, unsigned char *authed_message);

#endif
