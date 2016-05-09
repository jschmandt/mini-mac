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

//#include "sci.h"

//#define f_HCLK (float) 160.0 // f in [MHz]

/* Include ESM header file - types, definitions and function declarations for system driver */
#include "esm.h"

uint8  rx_data[8][8] = {0};
uint8 *rx_ptr = &rx_data[0][0];
uint32 error = 0;

//unsigned char hist_recent[8][4] = {{ 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}};
//unsigned char hist_periodic[8][4] = {{ 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00},{ 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}, { 0x00, 0x00, 0x00, 0x00}};
unsigned char messages[4][4] = {{0x11, 0x11, 0x11, 0x11}, {0x22, 0x22, 0x22, 0x22}, {0x33, 0x33, 0x33, 0x33}, {0x44, 0x44, 0x44, 0x44}};

uint16 period;
uint32 tx_success_counter;
uint8 tx_done;

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

    /* initialize can 1 and 2   */
    canInit(); /* can1 -> can2 */

    /** - enabling error interrupts */
    canEnableErrorNotification(canREG1);
	canEnableErrorNotification(canREG2);

    //_enable_IRQ();
    //sciInit();

#ifdef HMAC_SHA256
    unsigned char mac[32];
    //unsigned char rec_mac[32];
    //unsigned char mac_len = 32;
#endif

#ifdef HMAC_SHA1
    unsigned char mac[20];
    //unsigned char rec_mac[20];
#endif

#ifdef HMAC_MD5
    unsigned char mac[16];
    //unsigned char rec_mac[16];
#endif

#ifdef ECU_MASTER
    unsigned char message[4];
    unsigned char authed_message[8];
#endif // ECU_MASTER

    tx_success_counter = 0;

	while(1){

// if ECU_MASTER, pick a message to send at random and wait for responses
#ifdef ECU_MASTER
		unsigned char which_message = (rand() % 4);

		message[0] = messages[which_message][0];
		message[1] = messages[which_message][1];
		message[2] = messages[which_message][2];
		message[3] = messages[which_message][3];

		hmac(message, mac);
		tag(mac,4,message,authed_message);

		// give message ID "10"
		uint32 new_arb_val = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)10U & (uint32)0x000007FFU) << (uint32)18U);
		canUpdateID(canREG1, canMESSAGE_BOX1, new_arb_val);

	    /* transmit on can1 */
		unsigned char tx_success = canTransmit(canREG1, canMESSAGE_BOX1, authed_message);
//	    while(tx_done == 0){};                 /* ... wait until transmit request is through        */
//	    tx_done=0;
		if (tx_success)
			tx_success_counter++;

		while(1);

		// wait for message response from however many slave nodes there should be

		// wait for some interval
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


/* USER CODE END */
