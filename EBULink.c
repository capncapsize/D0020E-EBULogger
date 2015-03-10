/*
 * EBULink.c
 *
 *  Created on: Jan 23, 2015
 *      Author: machine
 */

#include "EBULink.h"

volatile int exit_EBULink = 0;

int initSocket(void){
	int socketfd, byte_count;
	char buffer[256];
	struct sockaddr_in serv_addr;

	//Create Socket with set UDP
	socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(socketfd < 0){
		perror("SOCKET :: Initialization error");
		exit(1);
	}
	//Configure socket to be reusable
	int reuse = 1;
	if(setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))){
		perror("SOCKET :: Could not set configuration");
		exit(1);
	}
	//Struct socket
	bzero( (char*) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	//serv_addr.sin_addr.s_addr =  INADDR_ANY;
	serv_addr.sin_addr.s_addr =  inet_addr("10.0.0.1");
	serv_addr.sin_port = htons(DST_PORT0);

	//Bind socket to local address
	if( bind(socketfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
		shutdown(socketfd, 2);
		perror("SOCKET :: Could not bind socket to IP address");
		exit(1);
	}

	//Listen socket
	listen(socketfd, 5);
	//char b[200];
	//extractDatagram(socketfd, b, 200);
	return socketfd;
}

void* extractDatagram(int *s){
	struct sockaddr_in addr;
	char buffer [256];
	int buflen = 256;
	int socklen, byte_count=48;
	long time;
	socklen = sizeof(addr);
	while(!exit_EBULink){
		byte_count = recvfrom(*s, buffer, buflen, MSG_OOB, (struct sockaddr *)&addr, (unsigned int *)&socklen);
		time = getTime();
		push(buffer, byte_count, time);
	}
}

void printDatagramAsBit(char* buffer, int byte_count){
	int div = byte_count/8;
	int i, j;
	unsigned char c;
	for(i=0; i < byte_count; i++){
		c = (unsigned char)*buffer;
		buffer++;
		for(j=0; j < 8; j++){
			printf("%u", c&0x80 ? 1 : 0);
			c = c << 1;
		}
		if((i+1) % (div*2) == 0) printf("\n");
		else if((i+1) % div == 0) printf("  ");
		else printf(" ");
	}
	printf("\n");
}




