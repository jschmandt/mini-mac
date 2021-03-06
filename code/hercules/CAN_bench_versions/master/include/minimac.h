#ifndef MINIMAC_CONFIG_H
#define MINIMAC_CONFIG_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

/**********************
 * Only use one of these HMACs at a time
 **********************/

#define USE_AUTH

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
void update_counter();
void update_history(unsigned char *message_rx);


// these are implemented in sys_main..quit being lazy
void master_start();
void setup_message_boxes();
void update_ack_list(uint8 ID);

#endif
