#ifndef MINIMAC_CONFIG_H
#define MINIMAC_CONFIG_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

/**********************
 * Only use one of these HMACs at a time
 **********************/

#define ECU_MASTER
//#define ECU_SLAVE
//#define ECU_PERIODIC

//#define HMAC_MD5
//#include "md5.h"

//#define HMAC_SHA1
//#include "sha1.h"

#define HMAC_SHA256
#include "sha256.h"
#include "sys_common.h"

//unsigned char *hmac(const unsigned char *key, unsigned char *message);
//unsigned char *minimac(unsigned char *mac, unsigned int space, unsigned char *message);

void hmac(unsigned char *message_ts, unsigned char *mac);
void tag(unsigned char *mac, unsigned int space, unsigned char *message, unsigned char *authed_message);
void init_minimac();
uint32 checkAuth(unsigned char *rec_frame, unsigned char *check_frame);

#endif
