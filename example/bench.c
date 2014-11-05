#include <stdio.h>
#include <time.h>

#define JLIBC_BENCH_NO_PREFIX 1
#include "../include/bench.h"

inline int clock_gettime_call (int clockid)
{
        static struct timespec t ;
        return clock_gettime (clockid, &t) ;
}

#define NB_REPEAT 10000000

int main (void)
{
        struct timespec t ;
        int failure = 0 ;

        printf ("\n*** Running clock_gettime (CLOCK_MONOTONIC)"
                " %d times ***\n", NB_REPEAT) ;

        BENCHMARK (clock_gettime_call(CLOCK_MONOTONIC), NB_REPEAT, t,
                   CLOCK_MONOTONIC, failure);
        if (!failure)
        {
                printf ("Wall clock time: ") ;
                PRINT_TIMESPEC (t) ;
                printf ("\n") ;
        }

        failure = 0 ;
        BENCHMARK (clock_gettime_call(CLOCK_MONOTONIC), NB_REPEAT, t,
                   CLOCK_PROCESS_CPUTIME_ID, failure);
        if (!failure)
        {
                printf ("CPU time: ") ;
                PRINT_TIMESPEC (t) ;
                printf ("\n") ;
        }
        return 0 ;
}
