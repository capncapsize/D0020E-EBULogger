/*
 * solutionTesting.c
 *
 *  Created on: Feb 27, 2015
 *      Author: machine
 */

#include "solutionTesting.h"


void testQueue(){
	printf("MAIN :: Test analyzer\n\n");
	int initT=0, dqeqT=0, ppfT=0, nT=0, fT=0;
	//Init test
	int dLen = linkLen(&dataQ),
			fLen = linkLen(&freeQ), i;
	if(dLen == 0 && fLen == 256){
		printf("Initialization of analyzer passed\n\n");
		initT = 1;
	} else
		printf("Initialization of analyzer failed\n\n");

//Dequeu and Enqueue
	datagram d;
	int passes = 0;
	for(i=0;i<10;i++){
		d = dequeue(&freeQ);
		enqueue(d, &dataQ);
	}
	dLen = linkLen(&dataQ);
	fLen = linkLen(&freeQ);
	if(dLen == 10 && fLen == 246)
		passes++;
	for(i=0;i<10;i++){
		d = dequeue(&dataQ);
		enqueue(d, &freeQ);
	}
	dLen = linkLen(&dataQ);
	fLen = linkLen(&freeQ);
	if(dLen == 0 && fLen == 256)
		passes++;
	if(passes == 2){
		printf("Enqueue and Dequeue Passed\n\n");
		dqeqT = 1;
	}
	else
		printf("Enqueue and Dequeue Failed\n\n");

//POP and PUSH test
	char a = 48;
	for(i=0; i < 5; i++){
		push(&a, 1);
		a = a + 1;

	}
	a = 48;
	char *b;
	int pass=0;
	for(i=0; i < 5; i++){
		b = pop();
		if(*b == a){
			a = a + 1;
			pass++;
		}else break;
	}
	dLen = linkLen(&dataQ);
	fLen = linkLen(&freeQ);
	if(pass == 5 && dLen == 0 && fLen == 256){
		printf("POP and PUSH functions passed\n\n");
		ppfT=1;
	}
	else
		printf("POP and PUSH functions failed\n"
				"DataQ length is %i should be 0\n"
				"FreeQ length is %i should be 256\n"
				"Buffer matches is %i should be 5\n\n", dLen, fLen, pass);
	//NULL return on empty q
	if(dLen != 0)
		printf("DataQ not empty due to last test failed. Skipping empty queue return null test\n\n");
	else{
		b = pop();
		if(b == NULL){
			printf("POP returns null on empty dataQ, passed\n\n");
			nT=1;
		}
		else
			printf("POP returns null on empty dataQ, failed\n\n");
	}

	//Final
	int fails;
	fails = testFinal();
	dLen = linkLen(&dataQ);
	fLen = linkLen(&freeQ);
	if(fails == 0 && dLen == 0 && fLen == 256){
		printf("Final test with 285 POP and 285 PUSH passed\n\n");
		fT=1;
	}
	else if(fails != 0)
		printf("\n\nFinal test failed with %i number of mismatched insertions vs extractions\n", fails);
	if(dLen != 0)
		printf("DataQ still contains %i datagrams. Should be empty.\n", dLen);
	if(fLen != 256)
		printf("FreeQ should contain 256 datagrams is only %i in queue\n", fLen);

	printf("\n\n\nTEST_COMPLETED\n\n"
			"Initialization test:\t%s\n"
			"Enqueue and Dequeue:\t%s\n"
			"POP and PUSH:\t\t%s\n"
			"Null return on empty q:\t%s\n"
			"Final test:\t\t%s\n"
			,initT ? "Pass" : "Failed"
			,dqeqT ? "Pass" : "Failed"
			,ppfT ? "Pass" : "Failed"
			,nT ? "Pass" : "Failed"
			,fT ? "Pass" : "Failed");

}



int testFinal(void){
        char h[5] = "", t[5] = "";
        char *a;
        int i, fails=0;
        for(i=0;i<100;i++){
                printf("Push: %i\n", (int)t[0]);
                volatile int y;
                for(y=0; y<0x8fffff; y++){}
                push(t, 20);
                t[0] = t[0] + 1;
        }

        for(i=0;i<30;i++){
                a = pop();
                printf("Pop: %i == Exp: %i\n", (int)a[0], (int)h[0]);
                volatile int y;
                for(y=0; y<0x4ffffff; y++){}
                if(a[0] == h[0]){
                        h[0] = h[0] +1;
                } else
                        fails++;
        }

        for(i=0;i<186;i++){
                printf("Push: %i\n", (int)t[0]);
                volatile int y;
                for(y=0; y<0xfffff; y++){}
                push(t, 20);
                t[0] = t[0] + 1;
        }

        for(i=0;i<256;i++){
                a = pop();
                printf("Pop: %i == Exp: %i\n", (int)a[0], (char)h[0]);
                volatile int y;
                for(y=0; y<0x4fffff; y++){}
                if(a[0] == h[0]){
                        h[0] = h[0] + 1;
                } else
                        fails++;
        }
        return fails;
}

