/*
 * analyser.h
 *
 *  Created on: Jan 26, 2015
 *      Author: machine
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <string.h>

#define BUFLEN (int)256;


struct datagramBlock{
	int byte_count;
	long time;
	char *databuff;

	struct datagramBlock *next;

};

typedef struct datagramBlock *datagram;

datagram freeQ, dataQ;
/*
 * Initialize the queue bindign all dgrams into a queue
 */
void initDgramQ();
/*
 * buffer: Binary data from datagram
 * byte_count: Length of buffer in bytes
 * time: Time the datagram was received
 */
int push(char *buffer, int byte_count, long time);
/*
 * time: pointer where the time shall be stored for reading
 * returns buffer of data.
 */
char *pop(long *time);
/*
 * q: Take a queue and counts its links
 * returns counts
 */
int linkLen(datagram *q);
void enqueue(datagram d, datagram *queue);
datagram dequeue(datagram *queue);


#endif /* QUEUE_H_ */
