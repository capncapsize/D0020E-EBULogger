/*
 * analyser.c
 *
 *  Created on: Jan 26, 2015
 *      Author: machine
 */

#include "queue.h"

#include <stdlib.h>
#include <pthread.h>

struct datagramBlock datagrams[256]; // 256 empty datagram

datagram freeQ = datagrams;
datagram dataQ = NULL;

volatile unsigned long dropped;
pthread_mutex_t queueLock;

void initDgramQ(void){ //Link every object
	int i;
	for(i=0; i < 255; i++){
		freeQ[i].byte_count = i;
	    freeQ[i].next = &(freeQ[i+1]);
	}
	freeQ[255].next = NULL;

	dropped = 0;
	pthread_mutex_init(&queueLock, NULL);
}

int push(char *buffer, int byte_count, long time){
	datagram new = dequeue(&freeQ);  // empty datagram - get data and put in dataQ
	if(new == NULL){
			dropped++;
			printf("Dropped: %lu\n", dropped);
			return 1;
	} else {
			char *cBuffer = malloc(sizeof(char)*(byte_count));
			memcpy(cBuffer, buffer, byte_count);
			new->byte_count = byte_count;
			new->databuff = cBuffer;
			new->time = time;
			enqueue(new, &dataQ);
			return 0;
	}
}

char *pop(long *time){// Select Item from front of the queue!!!
	datagram old = dequeue(&dataQ);
	if(old == NULL){					//Empty queue exception
		return NULL;
	}else{
		char *buffer;
		buffer = old->databuff;
		*time = old->time;
		enqueue(old,&freeQ);
		return buffer;
	}
}

datagram dequeue(datagram *queue){
	pthread_mutex_lock(&queueLock);
	datagram d = *queue;
	if(*queue){ 									//If the queue is not empty append datagram
		*queue = (*queue)->next;
	}else{
		//Handles empty queue
		pthread_mutex_unlock(&queueLock);
		return NULL;
	}
	pthread_mutex_unlock(&queueLock);
	return d;
}

void enqueue(datagram d, datagram *queue){
	pthread_mutex_lock(&queueLock);
	d->next = NULL;  //Resets the new datagrams next pointer
	if(*queue == NULL){ //If the queue is empty
		*queue = d;
	}else{
		datagram q = *queue;
		while(q->next)
			q = q->next;
		q->next = (datagram)d;
	}
	pthread_mutex_unlock(&queueLock);
}

int linkLen(datagram *q){
	int i, links = 0;
	datagram a = *q;
	for(i=0;;i++){
		if(a == NULL)
			break;
		else{
			a = a->next;
			links++;
		}
	}
	return links;
}

