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
#include "sci.h"
#include "sys_dma.h"

/* USER CODE BEGIN (0) */
#include "minimac.h"

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

	//canREG1 = master node
	if (node==canREG1){
		//uint8 tx_done = 0;
		// notification on message send
		if (messageBox == canMESSAGE_BOX1){
			//tx_done = 1; // define tx_done somewhere
			gioSetBit(gioPORTB, 2, 1);
		} else // notification on response from master message
		{

			unsigned char rec_frame[8] = { 0 };
			while(!canIsRxMessageArrived(node, messageBox));
			canGetData(node, messageBox, rec_frame); /* copy to RAM */

			// this block is just here to that you can debug whether or not you're receiving ACKs from every node you should
			uint32 rxID = canGetID(node, messageBox);
			unsigned char id = (uint8) (rxID >> 18U); //& 0x000007FFU)

			//unsigned char *id_str = "000";

			//strcpy(id_str, "201");

			char *uart_msg_prefix = "received msg from ID ";
			char *uart_msg_suffix = "\r\n";
			char uart_msg[32] = { 0 };
			strcpy(uart_msg, uart_msg_prefix);
			//strcpy(uart_msg+25, id_str);
			//strcpy(uart_msg+28, uart_msg_suffix);


			if (id == ((unsigned char) 101U)){
				strcat(uart_msg, "101");
			} else if (id == ((unsigned char) 102U)){
				strcat(uart_msg, "102");
			} else if (id == ((unsigned char) 103U)){
				strcat(uart_msg, "103");
			} else if (id == ((unsigned char) 201U)){
				strcat(uart_msg, "201");
			} else if (id == ((unsigned char) 202U)){
				strcat(uart_msg, "202");
			} else if (id == ((unsigned char) 203U)){
				strcat(uart_msg, "203");
			} else if (id == ((unsigned char) 211U)){
				strcat(uart_msg, "211");
			} else if (id == ((unsigned char) 212U)){
				strcat(uart_msg, "212");
			} else if (id == ((unsigned char) 213U)){
				strcat(uart_msg, "213");
			} else {
				strcat(uart_msg, "000");
			}

			//strcat(uart_msg, id_str);
			strcat(uart_msg, uart_msg_suffix);
			sciSend(scilinREG, 32, uart_msg);


			unsigned char rec_msg[4] = { 0 };
			rec_msg[0] = rec_frame[0];
			rec_msg[1] = rec_frame[1];
			rec_msg[2] = rec_frame[2];
			rec_msg[3] = rec_frame[3];

#ifdef USE_AUTH
			unsigned char check_frame[8] = { 0 };

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

			if (authed==1){
				sciSend(scilinREG, 11, "rx authed\n");
				//update_ack_list(id);
				update_counter();
				update_history(rec_msg);
			} else {
				sciSend(scilinREG, 14, "rx not authed\n");
			}



#endif //USE_AUTH

#ifndef USE_AUTH
			// do something
			update_ack_list(id);
#endif //USE_AUTH

		}
	} else if (node==canREG2) {
		// do shit
	} else { // CAN node 3 on master
		// do shit
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

#pragma WEAK(sciNotification)
void sciNotification(sciBASE_t *sci, uint32 flags)     
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (29) */
/* USER CODE END */
}

/* USER CODE BEGIN (30) */
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
