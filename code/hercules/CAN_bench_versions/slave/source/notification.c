/** @file notification.c 
*   @brief User Notification Definition File
*   @date 02-Mar-2016
*   @version 04.05.02
*
*   This file  defines  empty  notification  routines to avoid
*   linker errors, Driver expects user to define the notification. 
*   The user needs to either remove this file and use their custom 
*   notification function or place their code sequence in this file 
*   between the provided USER CODE BEGIN and USER CODE END.
*
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


/* Include Files */

#include "esm.h"
#include "sys_selftest.h"
#include "can.h"
#include "gio.h"
#include "sys_dma.h"

/* USER CODE BEGIN (0) */
#include "minimac.h"
#include "sci.h"

/* USER CODE END */
#pragma WEAK(esmGroup1Notification)
void esmGroup1Notification(uint32 channel)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (1) */
/* USER CODE END */
}

/* USER CODE BEGIN (2) */
/* USER CODE END */
#pragma WEAK(esmGroup2Notification)
void esmGroup2Notification(uint32 channel)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (3) */
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
#pragma WEAK(memoryPort0TestFailNotification)
void memoryPort0TestFailNotification(uint32 groupSelect, uint32 dataSelect, uint32 address, uint32 data)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (5) */
/* USER CODE END */
}

/* USER CODE BEGIN (6) */
/* USER CODE END */
#pragma WEAK(memoryPort1TestFailNotification)
void memoryPort1TestFailNotification(uint32 groupSelect, uint32 dataSelect, uint32 address, uint32 data)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (7) */
/* USER CODE END */
}

/* USER CODE BEGIN (8) */
/* USER CODE END */
#pragma WEAK(canErrorNotification)
void canErrorNotification(canBASE_t *node, uint32 notification)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (13) */
/* USER CODE END */
}

#pragma WEAK(canStatusChangeNotification)
void canStatusChangeNotification(canBASE_t *node, uint32 notification)  
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (14) */
/* USER CODE END */
}

#pragma WEAK(canMessageNotification)
void canMessageNotification(canBASE_t *node, uint32 messageBox)  
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (15) */


    /* node 1 - transfer request */
    //if(node==canREG1)
    //{
      //tx_done=1; /* confirm transfer request */
    //}

    /* node 2 - receive complete */
    //if(node==canREG2)
    //{
    //while(!canIsRxMessageArrived(canREG2, canMESSAGE_BOX1));
    //canGetData(canREG2, canMESSAGE_BOX1, rx_ptr); /* copy to RAM */
    //rx_ptr +=8;
    //}

	// tx
	/**uint8 tx_done = 0;
	if (messageBox == canMESSAGE_BOX1){
		tx_done = 1; // define tx_done somewhere
	}**/


	//gioSetBit(gioPORTB, 1, 1);
	/**uint8 which_node = 0;
	if (node==canREG1){
		which_node = 1;
	} else {
		which_node = 2;
	}**/

	// rx

#ifdef SLAVE_1
	unsigned char target_rx_id = 101U;
	unsigned char my_id = 201U;
#endif

#ifdef SLAVE_2
	unsigned char target_rx_id = 201U;
	unsigned char my_id = 211U;
#endif

	uint32 rxID = canGetID(node, messageBox);
	unsigned char id = (uint8) (rxID >> 18U); //& 0x000007FFU)

	sciSend(scilinREG, 1, my_id);
	sciSend(scilinREG, 10, ": rx from ");
	sciSend(scilinREG, 1, id);
	sciSend(scilinREG, 2, "\n");

	//if (id == ((unsigned char) 101U)){ // rx'ed val from master
	if (id == target_rx_id){
		gioSetBit(gioPORTB, 1, 1);
		unsigned char rec_frame[8] = { 0 };
		unsigned char rec_msg[4] = { 0 };
		unsigned char check_frame[8] = { 0 };

		while(!canIsRxMessageArrived(node, messageBox));
		canGetData(node, messageBox, rec_frame); /* copy to RAM */

		rec_msg[0] = rec_frame[0];
		rec_msg[1] = rec_frame[1];
		rec_msg[2] = rec_frame[2];
		rec_msg[3] = rec_frame[3];

#ifdef USE_AUTH

#ifdef HMAC_SHA256
		unsigned char rec_mac[32];
#endif

#ifdef HMAC_SHA1
		unsigned char rec_mac[20];
#endif

#ifdef HMAC_MD5
		unsigned char rec_mac[16];
#endif

		// run mini-mac
		hmac(rec_msg, rec_mac);
		tag(rec_mac, 4, rec_msg, check_frame);

		// check auth
		uint32 authed = checkAuth(rec_frame, check_frame);
#endif //USE_AUTH

		extern unsigned char messages[4][4];
		uint32 response_success_counter = 0;

		unsigned char response[4] = { 0 };

		if (rec_msg[0] == messages[0][0]) {
			response[0] = messages[1][0];
			response[1] = messages[1][1];
			response[2] = messages[1][2];
			response[3] = messages[1][3];
		} else if (rec_msg[0] == messages[1][0]) {
			response[0] = messages[2][0];
			response[1] = messages[2][1];
			response[2] = messages[2][2];
			response[3] = messages[2][3];
		} else if (rec_msg[0] == messages[2][0]) {
			response[0] = messages[3][0];
			response[1] = messages[3][1];
			response[2] = messages[3][2];
			response[3] = messages[3][3];
		} else if (rec_msg[0] == messages[3][0]) {
			response[0] = messages[0][0];
			response[1] = messages[0][1];
			response[2] = messages[0][2];
			response[3] = messages[0][3];
		} else {
			response[0] = 0xA;
			response[1] = 0xB;
			response[2] = 0xC;
			response[3] = 0xD;
		}

#ifdef USE_AUTH

		if (authed){
			update_counter();
			update_history(rec_msg);
			sciSend(scilinREG, 1, my_id);
			sciSend(scilinREG, 11, "rx authed\n");

			gioSetBit(gioPORTB, 2, 1);

			unsigned char authed_response[8];

			hmac(response, rec_mac);
			tag(rec_mac,4,response,authed_response);


#ifdef SLAVE_1
		    /* transmit on can1 */
		    unsigned char tx_success = canTransmit(canREG1, canMESSAGE_BOX4, authed_response); // use ID 201 for now
			while (tx_success == 0){
				tx_success = canTransmit(canREG1, canMESSAGE_BOX4, authed_response);
			}
#endif

#ifdef SLAVE_2
		    unsigned char tx_success = canTransmit(canREG1, canMESSAGE_BOX7, authed_response); // use ID 201 for now
			while (tx_success == 0){
				tx_success = canTransmit(canREG1, canMESSAGE_BOX7, authed_response);
			}
#endif
			//above -> tx will have succeeded to get to here
			update_counter();
			update_history(response);
			gioSetBit(gioPORTB, 2, 1);
			response_success_counter++;
			//serial print (my_id: tx)
			sciSend(scilinREG, 1, my_id);
			sciSend(scilinREG, 6, ": tx\n");

			/**
#ifdef SLAVE_1
		// check if new message has been seen


	    unsigned char tx_success = canTransmit(canREG1, canMESSAGE_BOX4, authed_response); // use ID 201 for now
		while (tx_success == 0){
			tx_success = canTransmit(canREG1, canMESSAGE_BOX4, response);
		}
		//above -> tx will have succeeded to get to here
		update_counter();
		update_history(response);
		gioSetBit(gioPORTB, 2, 1);
		response_success_counter++;
#endif //SLAVE_1

#ifdef SLAVE_2
		// maybe this is an ECU that takes longer to gather it's response
		// think about how to deal with concurrent message send.. that may just be a problem this protocol has
		// alternatively, if the node gets an RX interrupt, MAC vals should update, the RX control flow just
		// needs to let the TX flow about that
		int lazy_wait = 0;
		for (lazy_wait = 0; lazy_wait < 160000000; lazy_wait++); // wait ~1s

		// check if new message has been seen


		unsigned char tx_success = canTransmit(canREG1, canMESSAGE_BOX7, authed_response); // use ID 301 for now
		while (tx_success == 0){
			tx_success = canTransmit(canREG1, canMESSAGE_BOX7, response);
		}
		//above -> tx will have succeeded to get to here
		update_counter();
		update_history(response);
		gioSetBit(gioPORTB, 2, 1);
		response_success_counter++;
#endif //SLAVE_2
		**/
		} else {
			sciSend(scilinREG, 1, my_id);
			sciSend(scilinREG, 15, "rx not authed\n");
		}
#endif //USE_AUTH

#ifndef USE_AUTH
#ifdef SLAVE_1
	    /* transmit on can1 */
		unsigned char tx_success = canTransmit(canREG1, canMESSAGE_BOX4, response); // use ID 201 for now
		while (tx_success == 0){
			tx_success = canTransmit(canREG1, canMESSAGE_BOX4, response);
		}
		gioSetBit(gioPORTB, 2, 1);
		response_success_counter++;
#endif //SLAVE_1

#ifdef SLAVE_2
	    /* transmit on can1 */
		unsigned char tx_success = canTransmit(canREG1, canMESSAGE_BOX7, response); // use ID 301 for now
		while (tx_success == 0){
			tx_success = canTransmit(canREG1, canMESSAGE_BOX7, response);
		}
		gioSetBit(gioPORTB, 2, 1);
		response_success_counter++;
#endif //SLAVE_2
#endif // not USE_AUTH



	}else{ // rx'ed value from another node -- if you're using AUTH you have to run the auth and update counter
		unsigned char rec_frame[8] = { 0 };
		unsigned char rec_msg[4] = { 0 };
		unsigned char check_frame[8] = { 0 };

		while(!canIsRxMessageArrived(node, messageBox));
		canGetData(node, messageBox, rec_frame); /* copy to RAM */

		rec_msg[0] = rec_frame[0];
		rec_msg[1] = rec_frame[1];
		rec_msg[2] = rec_frame[2];
		rec_msg[3] = rec_frame[3];

#ifdef USE_AUTH

#ifdef HMAC_SHA256
		unsigned char rec_mac[32];
#endif

#ifdef HMAC_SHA1
		unsigned char rec_mac[20];
#endif

#ifdef HMAC_MD5
		unsigned char rec_mac[16];
#endif

		// run mini-mac
		hmac(rec_msg, rec_mac);
		tag(rec_mac, 4, rec_msg, check_frame);

		// check auth
		uint32 authed = checkAuth(rec_frame, check_frame);
		if (authed){
			update_counter();
			update_history(rec_msg);
			sciSend(scilinREG, 1, my_id);
			sciSend(scilinREG, 11, "rx authed\n");
		} else {
			sciSend(scilinREG, 1, my_id);
			sciSend(scilinREG, 15, "rx not authed\n");
		}
#endif //USE_AUTH
	}

	/* USER CODE END */
}

/* USER CODE BEGIN (16) */
/* USER CODE END */
#pragma WEAK(gioNotification)
void gioNotification(gioPORT_t *port, uint32 bit)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (19) */
/* USER CODE END */
}

/* USER CODE BEGIN (20) */
/* USER CODE END */




/* USER CODE BEGIN (43) */
/* USER CODE END */


/* USER CODE BEGIN (47) */
/* USER CODE END */


/* USER CODE BEGIN (50) */
/* USER CODE END */


/* USER CODE BEGIN (53) */
/* USER CODE END */

#pragma WEAK(dmaGroupANotification)
void dmaGroupANotification(dmaInterrupt_t inttype, uint32 channel)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (54) */
/* USER CODE END */
}
/* USER CODE BEGIN (55) */
/* USER CODE END */

/* USER CODE BEGIN (56) */
/* USER CODE END */

/* USER CODE BEGIN (58) */
/* USER CODE END */

/* USER CODE BEGIN (60) */
/* USER CODE END */
