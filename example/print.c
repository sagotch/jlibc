/**
 * gcc --std=c99 print.c -DJLIBC_PRINT_ENABLE_COLOR
 */

#include <stdio.h>

#define JLIBC_PRINT_NO_PREFIX 1
#include "../include/print.h"

int main (void)
{
        int i = 42 ;
        float f = 0.42 ;
        char * s = "Hello, world!" ;

        PRINT_IN_COLOR (COLOR_YELLOW, "%s\n", s) ;
        PRINT_IN_COLOR (COLOR_CYAN, "I'm blue!\n") ;
        PRINT_IN_COLOR (COLOR_RED, "Nope! You are cyan...\n") ;
        PRINT_IN_COLOR (COLOR_GREEN, "%d is my favorite number.\n", i) ;
        PRINT_IN_COLOR (COLOR_MAGENTA, "But I like %09f too.\n", f) ;

        PRINT_VAR (i, print_int) ; printf ("\n") ;
        PRINT_VAR (f, print_float) ; printf ("\n") ;
        PRINT_VAR (s, print_string) ; printf ("\n") ;

        return 0 ;
}
