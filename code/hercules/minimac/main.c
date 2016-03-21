#include "minimac.h"

//http://stackoverflow.com/questions/11656532/returning-an-array-using-c
// look at for mem de-allocation issues

    // CAN messages are 64-bit, and we assume that they only use 4B of 8B available
    unsigned char messages[5][8] = {{ 0xB5, 0x00, 0xB4, 0xC2, 0x00, 0x00, 0x00, 0x00}, { 0xC4, 0x00, 0xB4, 0xC2, 0x00, 0x00, 0x00, 0x00}, { 0xD3, 0x00, 0xB4, 0xC2, 0x00, 0x00, 0x00, 0x00},{ 0xE2, 0x00, 0xB4, 0xC2, 0x00, 0x00, 0x00, 0x00},{ 0xF1, 0x00, 0xB4, 0xC2, 0x00, 0x00, 0x00, 0x00}};

    unsigned char key[32] = { 0xAA, 0xBB, 0xCC, 0xDD, 0x00, 0x01, 0x02, 0x03,
    0xAA, 0xBB, 0xCC, 0xDD, 0x00, 0x01, 0x02, 0x03,
    0xAA, 0xBB, 0xCC, 0xDD, 0x00, 0x01, 0x02, 0x03,
    0xAA, 0xBB, 0xCC, 0xDD, 0x00, 0x01, 0x02, 0x03};

unsigned long message_counter;
unsigned char rollover_counter;

/*
 * main.c
 */
int main(void) {

	/**
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    // MSP430 USB requires a Vcore setting of at least 2.  2 is high enough
    // for 8MHz MCLK, below.
    PMM_setVCore(PMM_BASE, PMM_CORE_LEVEL_2);

    initPorts();           // Config all the GPIOS for low-power (output low)
    initClocks(8000000);   // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz
    bcUartInit();          // Init the back-channel UART
    USB_setup(TRUE,TRUE);  // Init USB; if a USB host (PC) is present, connect
    __enable_interrupt();  // Enable interrupts globally
    **/

	//P1DIR |= BIT0;                            // P1.0 set as output
    //P1OUT ^= BIT0;

    message_counter = 0;
    rollover_counter = 0;

    unsigned int i;

#ifdef HMAC_MD5
        unsigned char mac[16];
        //unsigned char mac_len = 16; //mac_len used for debugging
#endif

#ifdef HMAC_SHA1
        unsigned char mac[20];
        //unsigned char mac_len = 20;
#endif

#ifdef HMAC_SHA256
        unsigned char mac[32];
        //unsigned char mac_len = 32;
#endif

    unsigned char authed_message[8];

    //TA0CTL = TASSEL_1 + MC_0 + TACLR;
    unsigned int j;
    unsigned int k;

    //uint16_t start = 0;
    //uint16_t finish = 0;
    //uint16_t exec_cycles = 0;
    for (j = 0; j < 200; j++){
    	for (k = 0; k < 5; k++){
    		// start timekeeping
   			//TA0CTL = TASSEL_1 + MC_0;
   			//start = TA0R;
   			//TA0CTL = TASSEL_1 + MC_2;
    	    hmac(key, messages[k], mac);
    	    minimac(mac,4,messages[k],authed_message);
    		// finish timekeeping
   			//finish = TA0R;
   			//TA0CTL = TASSEL_1 + MC_0 + TACLR;
   			//exec_cycles = finish-start;
   			// Transmit timekeeping

   			//unsigned char cc[2] = { 0 };
   			//cc[0] = (exec_cycles >> 8) & 0xFF;
   			//cc[1] = exec_cycles & 0x00FF;

   			//bcUartSend("****", 4);
   			//bcUartSend(cc, 2);
   			for (i = 50000; i > 0; i--);
    	}
    }

        /**
        hmac(key, messages[0], mac);
        //bcUartSend(mac, mac_len);
		minimac(mac,4,messages[0],authed_message);
		**/
	return 0;
}


void hmac(const unsigned char *key, unsigned char *message, unsigned char *mac)
{
	unsigned char k_ipad[65];
	unsigned char k_opad[65];

	memset( k_ipad, 0, sizeof(k_ipad));
	memset( k_opad, 0, sizeof(k_opad));
	memcpy( k_ipad, key, 32);
	memcpy( k_opad, key, 32);

	int i;
	for (i = 0; i < 64; i++)
	{
		k_ipad[i] ^= 0x36;
		k_opad[i] ^= 0x5c;
	}

	//bcUartSend(k_ipad, 64);
	//bcUartSend(k_opad, 64);

	unsigned char msgxctr[64] = { 0 };
	msgxctr[0] = message[0] ^ (message_counter & 0xF000);
	msgxctr[1] = message[1] ^ ((message_counter & 0x0F00) << 8);
	msgxctr[2] = message[2] ^ ((message_counter & 0x00F0) << 8);
	msgxctr[3] = message[3] ^ ((message_counter & 0x000F) << 8);

    for (i = 1; i < 16; i++){
        msgxctr[4*i] = msgxctr[0];
        msgxctr[(4*i)+1] = msgxctr[1];
        msgxctr[(4*i)+2] = msgxctr[2];
        msgxctr[(4*i)+3] = msgxctr[3];
    }
    //bcUartSend(msgxctr, 64);

	#ifdef HMAC_MD5
	/*
	 * HMAC-MD5
	 */

	MD5_CTX ctx_1;
	MD5_CTX ctx_2;
	unsigned char digest1[16];

	MD5_Init(&ctx_1);
	MD5_Update(&ctx_1, &k_ipad, 64);
	MD5_Update(&ctx_1, &msgxctr, 64);
	MD5_Final(digest1, &ctx_1);

	//bcUartSend(digest1, 16);

	MD5_Init(&ctx_2);
	MD5_Update(&ctx_2, &k_opad, 64);
	MD5_Update(&ctx_2, &digest1, 16);
	MD5_Final(mac, &ctx_2);
	#endif

	/*
	 * HMAC-SHA1
	 */
#ifdef HMAC_SHA1
    unsigned char digest1[20] = { 0 };
	SHA1_CTX ctx1, ctx2;

	// Hash one
	sha1_init(&ctx1);
	sha1_update(&ctx1,k_ipad, 64);
	sha1_update(&ctx1,msgxctr,64);
	sha1_final(&ctx1,digest1);

	//bcUartSend(digest1, 20);

    // Hash two
	sha1_init(&ctx2);
	sha1_update(&ctx2, k_opad, 64);
	sha1_update(&ctx2, digest1, 20);
	sha1_final(&ctx2, mac);
#endif

	/*
	 * HMAC-SHA256
	 */
#ifdef HMAC_SHA256
	unsigned char digest1[32] = { 0 };
	SHA256_CTX ctx1, ctx2;

	// Hash one
	sha256_init(&ctx1);
	sha256_update(&ctx1,k_ipad,64);
	sha256_update(&ctx1,msgxctr,64);
	sha256_final(&ctx1,digest1);

	//bcUartSend(digest1, 32);

	sha256_init(&ctx2);
	sha256_update(&ctx2,k_opad,64);
	sha256_update(&ctx2,digest1,32);
	sha256_final(&ctx2,mac);
#endif

	message_counter++;
	//bcUartSend(message, 8);
}

void minimac(unsigned char *mac, unsigned int space, unsigned char *message, unsigned char *authed_message)
{

#ifdef HMAC_MD5
	unsigned char mmac_full[16];
	unsigned int k;

	// messages are 64b, but the last 32b are zeros
	// use the first 4B of past 5 messages to increase confusion on the message
	for (k = 0; k < 16; k++) {
		mmac_full[k] = mac[k] ^ messages[0][k/4];
	}
	for (k = 0; k < 16; k++) {
		mmac_full[k] = mmac_full[k] ^ messages[1][k/4];
	}
	for (k = 0; k < 16; k++) {
		mmac_full[k] = mmac_full[k] ^ messages[2][k/4];
	}
	for (k = 0; k < 16; k++) {
		mmac_full[k] = mmac_full[k] ^ messages[3][k/4];
	}
	for (k = 0; k < 16; k++) {
		mmac_full[k] = mmac_full[k] ^ messages[4][k/4];
	}
	//bcUartSend(mmac_full, 16);

	// use counter to select start index of mmac
	unsigned int s = rollover_counter % 128;

	// determine which byte to start in
	unsigned int byte = (unsigned int) s / 8;

	// determine which bit to start with
	unsigned int shift = s % 8;

	//char mmac_final[8] = 0;
	if (space == 4){
		char mmac_part[4] = { 0 };

		if (s > 96) { // getting the mmac part will rollover the full mac
			unsigned int b1 = (byte + 1) % 16;
			mmac_part[0] = (mmac_full[byte] << shift) + (mmac_full[b1] >> (8-shift));
			mmac_part[1] = (mmac_full[b1] << shift) + (mmac_full[b1+1] >> (8-shift));
			mmac_part[2] = (mmac_full[b1+1] << shift) + (mmac_full[b1+2] >> (8-shift));
			mmac_part[3] = (mmac_full[b1+2] << shift) + (mmac_full[b1+3] >> (8-shift));
		} else {
			mmac_part[0] = (mmac_full[byte] << shift) + (mmac_full[byte+1] >> (8-shift));
			mmac_part[1] = (mmac_full[byte+1] << shift) + (mmac_full[byte+2] >> (8-shift));
			mmac_part[2] = (mmac_full[byte+2] << shift) + (mmac_full[byte+3] >> (8-shift));
			mmac_part[3] = (mmac_full[byte+3] << shift) + (mmac_full[byte+4] >> (8-shift));
		}
#endif

#ifdef HMAC_SHA1
		unsigned char mmac_full[20];
		unsigned int k;

		// messages are 64b, but the last 32b are zeros
		// use the first 4B of past 5 messages to increase confusion on the message
		for (k = 0; k < 20; k++) {
			mmac_full[k] = mac[k] ^ messages[0][k/4];
		}
		for (k = 0; k < 20; k++) {
			mmac_full[k] = mmac_full[k] ^ messages[1][k/4];
		}
		for (k = 0; k < 20; k++) {
			mmac_full[k] = mmac_full[k] ^ messages[2][k/4];
		}
		for (k = 0; k < 20; k++) {
			mmac_full[k] = mmac_full[k] ^ messages[3][k/4];
		}
		for (k = 0; k < 20; k++) {
			mmac_full[k] = mmac_full[k] ^ messages[4][k/4];
		}
		//bcUartSend(mmac_full, 20);

		// use counter to select start index of mmac
		unsigned int s = rollover_counter % 160;

		// determine which byte to start in
		unsigned int byte = (unsigned int) s / 8;

		// determine which bit to start with
		unsigned int shift = s % 8;

		//char mmac_final[8] = 0;
		if (space == 4){
			char mmac_part[4] = { 0 };

			if (s > 128) { // getting the mmac part will rollover the full mac
				unsigned int b1 = (byte + 1) % 20;
				mmac_part[0] = (mmac_full[byte] << shift) + (mmac_full[b1] >> (8-shift));
				mmac_part[1] = (mmac_full[b1] << shift) + (mmac_full[b1+1] >> (8-shift));
				mmac_part[2] = (mmac_full[b1+1] << shift) + (mmac_full[b1+2] >> (8-shift));
				mmac_part[3] = (mmac_full[b1+2] << shift) + (mmac_full[b1+3] >> (8-shift));
			} else {
				mmac_part[0] = (mmac_full[byte] << shift) + (mmac_full[byte+1] >> (8-shift));
				mmac_part[1] = (mmac_full[byte+1] << shift) + (mmac_full[byte+2] >> (8-shift));
				mmac_part[2] = (mmac_full[byte+2] << shift) + (mmac_full[byte+3] >> (8-shift));
				mmac_part[3] = (mmac_full[byte+3] << shift) + (mmac_full[byte+4] >> (8-shift));
			}
#endif

#ifdef HMAC_SHA256
		unsigned char mmac_full[32];
		unsigned int k;

		// messages are 64b, but the last 32b are zeros
		// use the first 4B of past 5 messages to increase confusion on the message
		for (k = 0; k < 32; k++) {
			mmac_full[k] = mac[k] ^ messages[0][k/4];
		}
		for (k = 0; k < 32; k++) {
			mmac_full[k] = mmac_full[k] ^ messages[1][k/4];
		}
		for (k = 0; k < 32; k++) {
			mmac_full[k] = mmac_full[k] ^ messages[2][k/4];
		}
		for (k = 0; k < 32; k++) {
			mmac_full[k] = mmac_full[k] ^ messages[3][k/4];
		}
		for (k = 0; k < 32; k++) {
			mmac_full[k] = mmac_full[k] ^ messages[4][k/4];
		}
		//bcUartSend(mmac_full, 32);

		// use counter to select start index of mmac
		unsigned int s = rollover_counter % 256;

		// determine which byte to start in
		unsigned int byte = (unsigned int) s / 8;

		// determine which bit to start with
		unsigned int shift = s % 8;

		//char mmac_final[8] = 0;
		if (space == 4){
			char mmac_part[4] = { 0 };

			if (s > 224) { // getting the mmac part will rollover the full mac
				unsigned int b1 = (byte + 1) % 256;
				mmac_part[0] = (mmac_full[byte] << shift) + (mmac_full[b1] >> (8-shift));
				mmac_part[1] = (mmac_full[b1] << shift) + (mmac_full[b1+1] >> (8-shift));
				mmac_part[2] = (mmac_full[b1+1] << shift) + (mmac_full[b1+2] >> (8-shift));
				mmac_part[3] = (mmac_full[b1+2] << shift) + (mmac_full[b1+3] >> (8-shift));
			} else {
				mmac_part[0] = (mmac_full[byte] << shift) + (mmac_full[byte+1] >> (8-shift));
				mmac_part[1] = (mmac_full[byte+1] << shift) + (mmac_full[byte+2] >> (8-shift));
				mmac_part[2] = (mmac_full[byte+2] << shift) + (mmac_full[byte+3] >> (8-shift));
				mmac_part[3] = (mmac_full[byte+3] << shift) + (mmac_full[byte+4] >> (8-shift));
			}
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
	rollover_counter++;
}



