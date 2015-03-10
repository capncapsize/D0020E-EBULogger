/*
 * EBULink.h
 *
 *  Created on: Jan 23, 2015
 *      Author: machine
 */

#ifndef EBULINK_H_
#define EBULINK_H_

//Includes
//Standard C lib
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <time.h>

//Sleep
#include <unistd.h>

//Sockets
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//Function Defenition
int initSocket(void);
int extractDatagram(int s, char *buffer, int buflen, struct sockaddr *addr);
void printDatagramAsBit(char* buffer, int byte_count);

//Definition
//EBU
#define SRC_ADDR "10.0.0.2"
#define SRC_PORT0 (int) 25100
#define SRC_PORT1 (int) 25300

//Industrial PC
#define DST_ADDR "10.0.0.1"
#define DST_PORT0 (int) 25101
#define DST_PORT1 (int) 25301

#endif /* EBULINK_H_ */
