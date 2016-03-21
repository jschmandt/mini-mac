/*
 * sha1.h
 *
 *  Created on: Sep 14, 2015
 *      Author: jschmandt
 */

#ifndef SHA1_H_
#define SHA1_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Signed variables are for wimps
#define uchar unsigned char
#define uint unsigned long // 32b?

typedef struct {
   uchar data[64];
   uint datalen;
   uint bitlen[2];
   uint state[5];
   uint k[4];
} SHA1_CTX;

void sha1_transform(SHA1_CTX *ctx, uchar data[]);
void sha1_init(SHA1_CTX *ctx);
void sha1_update(SHA1_CTX *ctx, uchar data[], uint len);
void sha1_final(SHA1_CTX *ctx, uchar hash[]);

#endif /* SHA1_H_ */
