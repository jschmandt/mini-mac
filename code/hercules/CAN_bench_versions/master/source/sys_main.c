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

/**

CAN message box IDs

x101 0001 0000 0001
x102 0001 0000 0010
x103 0001 0000 0011

x201 0010 0000 0001
x202 0010 0000 0010
x203 0010 0000 0011

x301 0011 0000 0001
x302 0011 0000 0010
x303 0011 0000 0011

x401 0100 0000 0001
x402 0100 0000 0010
x403 0100 0000 0011

x501 0101 0000 0001
x502 0101 0000 0010
x503 0101 0000 0011

*/

// use this if you wan to auth messages with minimac
//#define USE_AUTH

/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "sys_core.h"
#include "can.h"
#include "minimac.h"
#include "stdlib.h"
#include "gio.h"
//#include "sys_pmu.h"
//#include "rti.h"

#include "sci.h"

//#define f_HCLK (float) 160.0 // f in [MHz]

/* Include ESM header file - types, definitions and function declarations for system driver */
#include "esm.h"

uint8  rx_data[8][8] = {0};
uint8 *rx_ptr = &rx_data[0][0];
uint32 error = 0;

uint16 acks = 0;

//unsigned char hist_recent[8][4] = {{ 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}};
//unsigned char hist_periodic[8][4] = {{ 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}};
unsigned char messages[4][4] = {{0x11, 0x11, 0x11, 0x11}, {0x22, 0x22, 0x22, 0x22}, {0x33, 0x33, 0x33, 0x33}, {0x44, 0x44, 0x44, 0x44}};

uint16 period;
uint32 tx_success_counter;
uint8 tx_success;

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

    _enable_interrupt_();

    gioInit();

    _enable_IRQ();
    sciInit();

    /* initialize can 1 and 2   */
    canInit(); /* can1 -> can2 */

    /** - enabling error interrupts */
    canEnableErrorNotification(canREG1);
	canEnableErrorNotification(canREG2);

	setup_message_boxes();

#ifdef USE_AUTH
	init_minimac();
#endif

	sciSend(scilinREG, 26, (unsigned char *)"\r\nMaster initialized\r\n");

	// B1  B2  B3  B4  B5  1
	// 111 011 011 111 111 1
	// xEDFF

	acks = 0x0;


	//while(1){
		master_start();

		//while(!canIsRxMessageArrived(canREG2, canMESSAGE_BOX1));
		//gioSetBit(gioPORTB,2,1);
		//while(1);

		// wait for message response from however many slave nodes there should be

		// wait for some interval
		// send random message again

		/*... wait until message receive on can2 */
		//while(!canIsRxMessageArrived(canREG2, canMESSAGE_BOX1));
		//canGetData(canREG2, canMESSAGE_BOX1, rx_data);  /* receive on can2  */



		//hmac(key, rec_msg, rec_mac);
		//minimac(rec_mac,4,rec_msg,rec_auth_msg);
		//uint32 auth_error = checkPackets(&authed_message[0],&rec_auth_msg[0],8);
		//if (auth_error == 0){
		//	counter++;
	//}

/* USER CODE END */
}

/* USER CODE BEGIN (4) */

void master_start()
{
#ifdef USE_AUTH

#ifdef HMAC_SHA256
    unsigned char mac[32];
#endif

#ifdef HMAC_SHA1
    unsigned char mac[20];
#endif

#ifdef HMAC_MD5
    unsigned char mac[16];
#endif

    unsigned char authed_message[8];

#endif //USE_AUTH

	unsigned char message[4];

    tx_success_counter = 0;
    tx_success = 0;

	//unsigned char which_message = (rand() % 4);
    unsigned char which_message = 3;

	message[0] = messages[which_message][0];
	message[1] = messages[which_message][1];
	message[2] = messages[which_message][2];
	message[3] = messages[which_message][3];

	gioSetBit(gioPORTB, 1, 0);

	acks = 0;

#ifdef USE_AUTH
	hmac(message, mac);
	tag(mac,4,message,authed_message);
	tx_success = canTransmit(canREG1, canMESSAGE_BOX1, authed_message);
	sciSend(scilinREG, 34, (unsigned char *) "attempting to xmit authed message ");
	sciSend(scilinREG, 8, authed_message);
	sciSend(scilinREG, 4, "\r\n");
#endif //USE_AUTH

#ifndef USE_AUTH
	tx_success = canTransmit(canREG1, canMESSAGE_BOX1, message);
#endif //USE_AUTH

	if (tx_success==1){
		tx_success_counter++;
		gioSetBit(gioPORTB, 1, 1);
		sciSend(scilinREG, 27, (unsigned char *)"Master transmit success\r\n");
		update_counter();
		update_history(message);
	} else {
		sciSend(scilinREG, 24, (unsigned char *)"Master transmit fail\r\n");
	}
}

// updates the list of nodes that have ACKed
void update_ack_list(uint8 ID){

	//sciSend(scilinREG, 17, (unsigned char *)"Updating ACKs\r\n");

	// 101: 100 000 000 000 000 0	0x8000
	// 102: 010 000 000 000 000 0	0x4000
	// 103: 001 000 000 000 000 0	0x2000
	// 201: 000 100 000 000 000 0	0x1000
	// 202: 000 010 000 000 000 0	0x0800
	// 203: 000 001 000 000 000 0	0x0400
	// 301: 000 000 100 000 000 0	0x0200
	// 302: 000 000 010 000 000 0	0x0100
	// 303: 000 000 001 000 000 0	0x0080
	// 401: 000 000 000 100 000 0	0x0040
	// 402: 000 000 000 010 000 0	0x0020
	// 403: 000 000 000 001 000 0	0x0010
	// 501: 000 000 000 000 100 0	0x0008
	// 502: 000 000 000 000 010 0	0x0004
	// 503: 000 000 000 000 001 0	0x0002

	// expecting ACKs from two nodes
	if (ID == ((unsigned char) 201U)){
		acks |= 0x1000;
	} else if (ID == ((unsigned char) 301U)){
		acks |= 0x0200;
	}

	if (acks == 0x1200){
		sciSend(scilinREG, 21, (unsigned char *)"All ACKs received\r\n");
	}
}

void setup_message_boxes()
{
    // ID=101, DIR=TX
	uint32 new_arb_val = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)101U & (uint32)0x000007FFU) << (uint32)18U);
	canUpdateID(canREG1, canMESSAGE_BOX1, new_arb_val);

	// ID=102, DIR=RX
	new_arb_val = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)102U & (uint32)0x000007FFU) << (uint32)18U);
	canUpdateID(canREG1, canMESSAGE_BOX2, new_arb_val);

	// ID=103, DIR=RX
	new_arb_val = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)103U & (uint32)0x000007FFU) << (uint32)18U);
	canUpdateID(canREG1, canMESSAGE_BOX3, new_arb_val);

	// ID=201, DIR=RX
	new_arb_val = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)201U & (uint32)0x000007FFU) << (uint32)18U);
	canUpdateID(canREG1, canMESSAGE_BOX4, new_arb_val);

	// ID=202, DIR=RX
	new_arb_val = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)202U & (uint32)0x000007FFU) << (uint32)18U);
	canUpdateID(canREG1, canMESSAGE_BOX5, new_arb_val);

	// ID=211, DIR=RX
	new_arb_val = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)211U & (uint32)0x000007FFU) << (uint32)18U);
	canUpdateID(canREG1, canMESSAGE_BOX6, new_arb_val);

	// ID=212, DIR=RX
	new_arb_val = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)212U & (uint32)0x000007FFU) << (uint32)18U);
	canUpdateID(canREG1, canMESSAGE_BOX7, new_arb_val);
}

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


/* USER CODE END */
