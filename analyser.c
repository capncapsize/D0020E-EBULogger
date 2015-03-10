#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "analyser.h"
#include "mongoAPI.h"
#include "EBULink.h"


void startAnalyzer(void)
{
	//Algorithm for translating
	char *DB = "test";				//Which database
	char *coll = "test";				//Which collection  //skopa_test_1, bom_test_1
	char *buff; 					//Datagram data buffer
	struct timespec tim, tim2;
	long time;
	tim.tv_sec = 0;
	tim.tv_nsec = 100000000;  //10ms
 
	while(1)
	{
		buff = pop(&time);									//Retreive new datagram
		if(buff != NULL){									//If none-empty
			insertIn(buff, time, DB, coll); 				//Insert into db
			continue;
		}
		nanosleep(&tim, &tim2);						//else sleep for 10ms before trying again
	} 
}
