
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
int size = 0;
int num_threads = 0;

struct result_s
{
    int skiped;
    int rejected;
    int processed;
};

// void reset_stats()
// {
//     __asm__ __volatile__ (".byte 0x0F, 0x04; .word 0x40;");
// }

// void dump_stats()
// {
//     __asm__ __volatile__ (".byte 0x0F, 0x04; .word 0x41;");
// }


void gem5(char * pointer)
{
    __asm__ __volatile__ (".byte 0x0F, 0x04; .word 0x55;");
}

// void gem5_clean(char * pointer)
// {
//     __asm__ __volatile__ (".byte 0x0F, 0x04; .word 0x56;");
// }

// void *thread(void *args) 
// {
//     struct result_s *result = (struct result_s *)args;
//     result->skiped = 0;
//     result->rejected = 0;
//     result->processed = 0;

//     for(int i = 0; i < size; i++) {
//         if ( i % 0x100 == 0 )
//             result->skiped++;
//         else if ( *(data + i) == 0 )
//             result->rejected++;
//         else
//             result->processed++;
//     }
// }

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

int
main(void)
{
    struct timeval timeval1, timeval2, timeval_result;
    size = 4096;
    num_threads = 8;
    // srand((unsigned)time(NULL));
    bool enable_rejection = 1;
    pthread_t threads[num_threads];
    struct result_s results[num_threads];

    // data = (char* )memalign(PAGE, size);
    data = (char* )memalign(PAGE, 65536*256);
    // for(int i = 0; i < size; i++) 
    //     gem5(data+i);
    register int i,j;
    register int x=1;
    j=0;

    gettimeofday(&timeval1, NULL);
    

    for(i=0; i <4096; i++)
    {     
        // x=data[j];
        data[j]=1;
        j=j+128;
        if(j>=65536*256)
        {
            j=(j+1)%(65536*256);
        }
    }
        

    gettimeofday(&timeval2, NULL);
    timeval_subtract(&timeval_result, &timeval2, &timeval1);

    printf("runtime: %lu.%lu seconds.\n", timeval_result.tv_sec, timeval_result.tv_usec);




    return 0;
}
