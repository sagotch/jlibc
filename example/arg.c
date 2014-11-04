/**
 * Short example showing how to sue the jlibc arg module.
 * Compile with:
 *     gcc --std=c99 -o arg arg.c
 * Then test it:
 *    ./a.out --flag --integer 0 --string "Good Bye!" I am a not an option
 *    ./a.out --string "Good Bye!" --flag --integer 0
 *    ./a.out -- --flag --integer 0 --string "Good Bye!"
 */

#define JLIBC_ARG_NO_PREFIX
#include "../include/arg.h"
#include <stdio.h>

int main(int argc, char ** argv)
{

        long long int integer = 42 ;
        char flag = 0 ;
        char * string = "Hello, world!" ;

        int not_opts_count ;
        char ** not_opts ;

        struct jlibc_arg_opt opts [] = {
                {.name="--integer", .type=LONGLONG, .val=(void *) &integer},
                {.name="--string", .type=STRING, .val=(void *) &string},
                {.name="--flag", .type=FLAG, .val=(void *) &flag}
        } ;

        if (PARSE_ARG(argc - 1, &(argv[1]),
                      opts, &not_opts_count, &not_opts) != 0)
        {
                return 1 ;
        }

        printf ("integer = %lld\nflag = %d\nstring = %s\n",
                integer, flag, string) ;

        printf ("%d argument(s) remaining.\n", not_opts_count) ;

        for (int i = 0; i < not_opts_count; i++)
        {
                printf ("\t- %s\n", not_opts [i]) ;
        }

        return 0 ;
}
