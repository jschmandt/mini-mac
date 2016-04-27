/** @file sys_main.c 
*   @brief Application main file
*   @date 02-Mar-2016
*   @version 04.05.02
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
// change code to use interrupt-driven CAN

#include "can.h"
#include "minimac.h"

#include "gio.h"
//#include "sys_pmu.h"
//#include "rti.h"

#include "sci.h"
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */

//#define f_HCLK (float) 160.0 // f in [MHz]

/* Include ESM header file - types, definitions and function declarations for system driver */
#include "esm.h"

//#define  D_SIZE 9

//uint8  tx_data[D_SIZE]  = {'H','E','R','C','U','L','E','S','\0'};
uint8  rx_data[8] = {0};
uint32 error = 0;

unsigned char hist_recent[8][4] = {{ 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}};
unsigned char hist_periodic[8][4] = {{ 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}};
unsigned int messages[4][4] = {{0x11, 0x11, 0x11, 0x11}, {0x22, 0x22, 0x22, 0x22}, {0x33, 0x33, 0x33, 0x33}, {0x44, 0x44, 0x44, 0x44}};

uint16 period = 100;

unsigned char key[32] = { 0xAA, 0xBB, 0xCC, 0xDD, 0x00, 0x01, 0x02, 0x03,
0xAA, 0xBB, 0xCC, 0xDD, 0x00, 0x01, 0x02, 0x03,
0xAA, 0xBB, 0xCC, 0xDD, 0x00, 0x01, 0x02, 0x03,
0xAA, 0xBB, 0xCC, 0xDD, 0x00, 0x01, 0x02, 0x03};

uint64 counter = 0;

uint32 checkPackets(uint8 *src_packet,uint8 *dst_packet,uint32 psize);
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */

    /* initialize can 1 and 2   */
    canInit(); /* can1 -> can2 */

    _enable_IRQ();
    sciInit();


    counter = 0;
#ifdef HMAC_SHA256
    unsigned char mac[32];
    unsigned char rec_mac[32];
    //unsigned char mac_len = 32;
#endif

#ifdef HMAC_SHA1
    unsigned char mac[20];
    unsigned char rec_mac[20];
#endif

#ifdef HMAC_MD5
    unsigned char mac[16];
    unsigned char rec_mac[16];
#endif

    unsigned char message[4];
	unsigned char rec_msg[4];

    unsigned char authed_message[8];
    unsigned char rec_auth_msg[8];

	while(1){

// if ECU_MASTER, pick a message to send at random and wait for responses
#ifdef ECU_MASTER
		uint16 which_message = int(rand() % 4);
		message = messages[which_message];

		hmac(key, message, mac);
		minimac(mac,4,message,authed_message);

	    /* transmit on can1 */
		canTransmit(canREG1, canMESSAGE_BOX1, authed_message);

		// switch can1 to RX mode

		// wait for message response from however many slave nodes there should be

		// send random message again
#endif //ECU_MASTER

// if ECU_SLAVE, wait for a message and respond to it
#ifdef ECU_SLAVE

#endif //ECU_SLAVE

// if ECU_PERIODIC, send the same message over and over again periodicially
#ifdef ECU_PERIODIC

#endif //ECU_PERIODIC



    /*... wait until message receive on can2 */
	//while(!canIsRxMessageArrived(canREG2, canMESSAGE_BOX1));
	//canGetData(canREG2, canMESSAGE_BOX1, rx_data);  /* receive on can2  */



//    	hmac(key, rec_msg, rec_mac);
//    	minimac(rec_mac,4,rec_msg,rec_auth_msg);
//    	uint32 auth_error = checkPackets(&authed_message[0],&rec_auth_msg[0],8);
//    	if (auth_error == 0){
//    		counter++;
//    	}
//    }

	counter++;

	}

/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/** @fn checkPackets(uint8 *src_packet,uint8 *dst_packet,uint32 psize)
*   @brief check two buffers and report error
*
*/
uint32 checkPackets(uint8 *src_packet,uint8 *dst_packet,uint32 psize)
{
   uint32 err=0;
   uint32 cnt=psize;

   while(cnt--)
   {
     if((*src_packet++) != (*dst_packet++))
     {
        err++;           /*  data error  */
     }
   }
   return (err);
}

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

void minimac(unsigned char *mac, unsigned int space, unsigned char *message, unsigned char *authed_message)
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
/* USER CODE END */
