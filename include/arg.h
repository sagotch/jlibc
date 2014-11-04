/*
  The MIT License (MIT)

  Copyright (c) 2014 Julien Sagot <ju.sagot@gmail.com>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#ifndef JLIBC_ARG_H
#define JLIBC_ARG_H 1

#include <stdlib.h>
#include <string.h>

/**
 * `struct jl_arg_opt` need to be tagged with one of the followings.
 */
enum jl_arg_opt_t {
        JL_ARG_LONGLONG, // associate with (long long *)
        JL_ARG_STRING,   // associate with (char **)
        JL_ARG_FLAG      // associate with (char *)
} ;

/**
 * Structure representing an option,
 * @field name string that argument must match.
 * @field type `enum jl_arg_opt_t` tag to indicate how to handle the argument.
 * @field val void pointer which will be set according to `type`.
 */
struct jl_arg_opt {
        char * name ;            // e.g. "--foo"
        enum jl_arg_opt_t type ; // expected type
        void * val ;             // pointer which will receive arg value
} ;

/**
 * Parse arguments in order to set values for a set of options.
 * Note: current implementation use atoll in order to get integer values,
 * and is, as a result, not reliable.
 * Note: `--` is a special argument meaning that nothing after it is
 * an option.
 * @param ac maximum number of arguments to parse.
 * @param av argument values.
 * @param oc number of options in `ov`.
 * @param ov array of options you are looking for setting.
 * @param nc pointer to int which will reveive.
 */
static int jl_arg_parse_args (int ac, char ** av,
                              int oc, struct jl_arg_opt (* ov) [],
                              int * nc, char *** nv)
{
        int ai = 0 ; // current index in av
        while (ai < ac)
        {
                char is_opt = 0 ;
                int oi ; // current index in ov

                for (oi = 0; oi < oc; oi++)
                {
                        if (strcmp (av[ai], (* ov)[oi].name) != 0)
                        {
                                continue ;
                        }

                        is_opt = 1 ;

                        switch ((* ov)[oi].type)
                        {

                        case JL_ARG_LONGLONG:
                                if (ai > ac - 2)
                                {
                                        return -1 ;
                                }
                                * (long long *) (* ov) [oi] . val =
                                        atoll (av [ai + 1]) ;
                                ai += 2;
                                break;

                        case JL_ARG_STRING:
                                if (ai > ac - 2)
                                {
                                        return -1 ;
                                }
                                * (char **) ((* ov) [oi] . val) =
                                        av [ai + 1] ;
                                ai += 2;
                                break;

                        case JL_ARG_FLAG:
                                * (char *) (* ov) [oi] . val = 1;
                                ai += 1;
                                break;
                        }

                        break ; // for (oi = 0; oi < oc; oi++)

                }

                if (!is_opt) // No option in list matched
                {
                        break;
                }
        }

        // If current argument is '--' (force end of parsing),
        // remove it from argument list
        if (ai < ac && strcmp("--", av[ai]) == 0)
        {
                ai++;
        }

        // Set non-option number and pointer
        if (nc != NULL && nv != NULL)
        {
                * nc = ac - ai;
                * nv = * nc > 0 ? & av [ai] : NULL;
        }

        return 0;
}

/**
 * This macro allows to use `jl_arg_parse_args` with automatic computing
 * of the number of options in optv.
 */
#define JL_ARG_PARSE_ARG(argc,argv,optv,nc,nv)                          \
        do                                                              \
        {                                                               \
                jl_arg_parse_args ((argc), (argv),                      \
                                   sizeof(optv)/sizeof(*(optv)),        \
                                   &(optv),(nc),(nv));                  \
        }                                                               \
        while (0)

#endif // #ifndef JLIBC_ARG_H
