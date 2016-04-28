/*
 * minimac.c
 *
 *  Created on: Apr 27, 2016
 *      Author: Jackson
 */

#include "minimac.h"
#include "sys_common.h"

unsigned char hist_recent[8][4] = {{ 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}};
unsigned char hist_periodic[8][4] = {{ 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}};

uint64 counter;

void init_minimac()
{
	counter = 0;
}


// need a function that takes in a received message and responds with a valid / nonvalid signal, and updats counter + history as appropriate
// need a function to update history when a valid message is detected

// returns 0 if auth fails, 1 if auth passes
unsigned char checkAuth(unsigned char *message_rx){

	/**
	if (valid) {
		update_history;
		update_counter;
		return 1;
	} else {
		return 0;
	}
	**/

	return 0;
}

// call before updating counter
void update_history(unsigned char *message_rx){
	/*
	if (period) {
		update_periodic;
	}
	update_recent;
	 */
}

// slightly modified HMAC that salts input with history + counter
void hmac(const unsigned char *key, unsigned char *message_ts, unsigned char *mac)
{
	unsigned char k_ipad[65];
	unsigned char k_opad[65];

	memset( k_ipad, 0, sizeof(k_ipad));
	memset( k_opad, 0, sizeof(k_opad));
	memcpy( k_ipad, key, 32);
	memcpy( k_opad, key, 32);

	int i;
	int j;
	for (i = 0; i < 64; i++)
	{
		k_ipad[i] ^= 0x36;
		k_opad[i] ^= 0x5c;
	}

	//bcUartSend(k_ipad, 64);
	//bcUartSend(k_opad, 64);

	// 4B from message + 4*8=32B from recent hist + 4*8=32B from periodic hist + 8B from counter
	unsigned int concat_len = 76;

	// concat_input[concat_len]
	unsigned char concat_input[76];

	// replace 4 with messages size
	for (i = 0; i < 4; i++){
		concat_input[i] = message_ts[i];
	}

	unsigned int hist_recent_offset = 4;

	// replace 8 with num msgs in recent hist
	// replace 4 with hist message len
	for (i = 0; i < 8; i++){
		for (j = 0; j < 4; j++){
			concat_input[hist_recent_offset+(i*4)+j] = hist_recent[i][j];
		}
	}

	unsigned int hist_periodic_offset = 36;

	// replace 8 with num msgs in periodic hist
	// replace 4 with hist message len
	for (i = 0; i < 8; i++){
		for (j = 0; j < 4; j++){
			concat_input[hist_periodic_offset+(i*4)+j] = hist_periodic[i][j];
		}
	}

	unsigned int counter_offset = 68;

	//roll this up when you know it works
	concat_input[counter_offset] = (counter >> 56) & 0xFF;
	concat_input[counter_offset+1] = (counter >> 48) & 0xFF;
	concat_input[counter_offset+2] = (counter >> 40) & 0xFF;
	concat_input[counter_offset+3] = (counter >> 32) & 0xFF;
	concat_input[counter_offset+4] = (counter >> 24) & 0xFF;
	concat_input[counter_offset+5] = (counter >> 16) & 0xFF;
	concat_input[counter_offset+6] = (counter >> 8) & 0xFF;
	concat_input[counter_offset+7] = counter & 0xFF;

	/*
	 * HMAC-SHA256
	 */
#ifdef HMAC_SHA256
	unsigned char digest1[32] = { 0 };
	SHA256_CTX ctx1, ctx2;

	// Hash one
	sha256_init(&ctx1);
	sha256_update(&ctx1,k_ipad,64);
	sha256_update(&ctx1,concat_input,concat_len);
	sha256_final(&ctx1,digest1);

	//bcUartSend(digest1, 32);

	sha256_init(&ctx2);
	sha256_update(&ctx2,k_opad,64);
	sha256_update(&ctx2,digest1,32);
	sha256_final(&ctx2,mac);
#endif


#ifdef HMAC_SHA1
	unsigned char digest1[20] = { 0 };
	SHA1_CTX ctx1, ctx2;

	// Hash one
	sha1_init(&ctx1);
	sha1_update(&ctx1,k_ipad,64);
	sha1_update(&ctx1,concat_input,concat_len);
	sha1_final(&ctx1,digest1);

	sha1_init(&ctx2);
	sha1_update(&ctx2,k_opad,64);
	sha1_update(&ctx2,digest1,20);
	sha1_final(&ctx2,mac);
#endif

#ifdef HMAC_MD5
	MD5_CTX ctx_1;
	MD5_CTX ctx_2;
	unsigned char digest1[16];

	MD5_Init(&ctx_1);
	MD5_Update(&ctx_1, k_ipad, 64);
	MD5_Update(&ctx_1, concat_input, concat_len);
	MD5_Final(digest1, &ctx_1);

	MD5_Init(&ctx_2);
	MD5_Update(&ctx_2, k_opad, 64);
	MD5_Update(&ctx_2, digest1, 16);
	MD5_Final(mac, &ctx_2);
#endif

	// incrementing counter in main since we're sending/checking in the same device
	//counter++;
	//bcUartSend(message, 8);
}

void trim(unsigned char *mac, unsigned int space, unsigned char *message, unsigned char *authed_message)
{

#ifdef HMAC_SHA256

		char mmac_part[4] = { 0 };
		// roll it up, account for var len
		mmac_part[0] = mac[28];
		mmac_part[1] = mac[29];
		mmac_part[2] = mac[30];
		mmac_part[3] = mac[31];

#endif

#ifdef HMAC_SHA1

		char mmac_part[4] = { 0 };
		// roll it up, account for var len
		mmac_part[0] = mac[16];
		mmac_part[1] = mac[17];
		mmac_part[2] = mac[18];
		mmac_part[3] = mac[19];

#endif

#ifdef HMAC_MD5
		char mmac_part[4] = { 0 };
		mmac_part[0] = mac[12];
		mmac_part[1] = mac[13];
		mmac_part[2] = mac[14];
		mmac_part[3] = mac[15];
#endif

		//bcUartSend(mmac_part, 4);
		memcpy(authed_message, message, 4);
		//bcUartSend(authed_message, 8);
		authed_message[4] = mmac_part[0];
		authed_message[5] = mmac_part[1];
		authed_message[6] = mmac_part[2];
		authed_message[7] = mmac_part[3];
		//bcUartSend(authed_message, 8);


}



