/*
 * sha256.h
 *
 *  Created on: Sep 14, 2015
 *      Author: jschmandt
 */

#ifndef SHA256_H_
#define SHA256_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define uchar unsigned char // 8-bit byte
#define uint unsigned long // 32-bit word

typedef struct {
   uchar data[64];
   uint datalen;
   uint bitlen[2];
   uint state[8];
} SHA256_CTX;

void sha256_transform(SHA256_CTX *ctx, uchar data[]);
void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, uchar data[], uint len);
void sha256_final(SHA256_CTX *ctx, uchar hash[]);

#endif /* SHA256_H_ */
