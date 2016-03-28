#ifndef MINIMAC_CONFIG_H
#define MINIMAC_CONFIG_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

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
