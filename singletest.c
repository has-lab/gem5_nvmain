
#include <err.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <malloc.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>

#include <gem5/m5ops.h>

#define PAGE    4096
#define BLOCK   64

volatile char * data = NULL;
int * getrand;
int size = 0;


int timeval_subtract(struct timeval *result, struct timeval *x, struct timeval *y)
{
    /* Perform the carry for the later subtraction by updating Y. */
    if (x->tv_usec < y->tv_usec)
    {
        int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
        y->tv_usec -= 1000000 * nsec;
        y->tv_sec += nsec;
    }
    if (x->tv_usec - y->tv_usec > 1000000)
    {
        int nsec = (x->tv_usec - y->tv_usec) / 1000000;
        y->tv_usec += 1000000 * nsec;
        y->tv_sec -= nsec;
    }

    /* Compute the time remaining to wait.
       `tv_usec' is certainly positive. */
    result->tv_sec = x->tv_sec - y->tv_sec;
    result->tv_usec = x->tv_usec - y->tv_usec;

    /* Return 1 if result is negative. */
    return x->tv_sec < y->tv_sec;
}

void addrwrite(volatile char * addr,int length)
{
    register int i;
    register int j=length;
    for(i=0;i<j;i+64)
    {
        addr[i]=1;
    }
}

void addrread(volatile char *addr,int length)
{
    register int i;
    register int j=length;
    register int x=0;
    for(i=0;i<j;i=i+64)
    {
        x=addr[i];
    }
}


int
main(void)
{
    struct timeval timeval1, timeval2, timeval_result;

    // data = (char* )memalign(PAGE, size);
    data = (char* )memalign(PAGE, 4096*4096);
    // getrand = (int *)malloc(4096*sizeof(int));
    register int m,i,j,x=0;
    j=0;
    // for(i = 0; i < 4096; i++) 
    // {
    //     getrand[i]=rand()%(4096*4096);
    // }
    for(i = 0; i < 4096*4096; i=i+4096) 
    {
        data[i]=1;
    }
    gettimeofday(&timeval1, NULL);
    

    for(i=0; i <4096; i++)
    {     
        for(x=0;x<64;x=x+64)
        {
            // data[j+x]=1;
            m=data[j+x];
        }
        j=j+1;
        x=rand()%(4096*4096);
        // x=j+1;
        // j=rand()%(4096*4096);
        if(j>=4096*4096)
        {
            j=(j+1)%(4096*4096);
        }
    }
        

    gettimeofday(&timeval2, NULL);
    timeval_subtract(&timeval_result, &timeval2, &timeval1);

    printf("runtime: %lu.%lu seconds.\n", timeval_result.tv_sec, timeval_result.tv_usec);




    return 0;
}
