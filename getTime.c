

    #include <sys/time.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include "getTime.h"



    struct timeval tv;

    long getTime(void)
    {
        gettimeofday(&tv, (void *)0);							//Get epoch time
        long usec = tv.tv_usec  + tv.tv_sec*1000000;
           return usec;

    }

