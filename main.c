/*
 * main.c
 *
 *  Created on: Jan 22, 2015
 *      Author: machine
 */

#include "main.h"



int main(void){
	int s = initSocket();
	initDgramQ();
	//testQueue();
	//create thread for datagram
	pthread_t EBUlink;
	if(pthread_create(&EBUlink, NULL, (void *)*extractDatagram, &s))
	{
		printf("Error on create thread\n");
		return 1;
	}
	startAnalyzer();
	//join two differernt threads
	if(pthread_join(EBUlink, NULL))
	{
		printf("Error joining\n");
		return 2;

	}

	printf("\nEXIT_SUCCESS\n");
	return 0;
}

void testPDAB(){
	char buffer[10] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa};
	buffer[0] = 0x1;
	printf("%02x\n", (unsigned char)buffer[0]);
	printDatagramAsBit((char *)buffer, 10);
}
