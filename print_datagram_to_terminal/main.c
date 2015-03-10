/*
 * main.c
 *
 *  Created on: Jan 22, 2015
 *      Author: machine
 */

#include "main.h"
#include "EBULink.h"

int debug = 0;

int main(void){
	initSocket();
	printf("Hello\n");
	if (debug) printf("debug on\n");
	return 0;

}

void testPDAB(){
	char buffer[10] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa};
	buffer[0] = 0x1;
	printf("%02x\n", (unsigned char)buffer[0]);
	printDatagramAsBit((char *)buffer, 10);
}
