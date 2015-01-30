/**
 * Short example showing how to use the cpu test module.
 * Compile with:
 *     gcc -D_POSIX_SOURCE -std=c99 cpu.c
 */

#include <stdio.h>
#include <sys/times.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

#define JLIBC_CPU_NO_PREFIX 1
#include "../include/cpu.h"

#define GOAL 25.

int main (void)
{

	int pid ;
	struct tms t0, t1 ;
	clock_t c0, c1 ;
	float usg ;

        // Save current times.
	c0 = times (&t0) ;

	// Create a cpu load using 25% of the cpu
	CPU_LOAD (&pid, GOAL) ;

        // Let the child use load cpu for 20 seconds.
	sleep (20) ;

        // Stop the child
        kill (pid, SIGTERM) ;

        // times will collect values for waited-for children.
        waitpid (pid, NULL, 0) ;

	// Get current times.
	c1 = times (&t1) ;

	// Compute times difference
	usg = sysconf (_SC_CLK_TCK)
		* (t1.tms_cutime - t0.tms_cutime) / (c1 - c0) ;

	printf ("Average child CPU usage is about %f (%f required)\n",
		usg, GOAL) ;

	return 0 ;
}
