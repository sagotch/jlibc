/*
  The MIT License (MIT)

  Copyright (c) 2014 Julien Sagot <ju.sagot@gmail.com>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef SAFT_H
#define SAFT_H 1

#include <stdio.h>

#ifdef SAFT_ENABLE_COLOR
#define SAFT_COLOR_RED "\x1b[31m"
#define SAFT_COLOR_GREEN "\x1b[32m"
#define SAFT_COLOR_CYAN "\x1b[36m"
#define SAFT_COLOR_RESET "\x1b[0m"
#else
#define SAFT_COLOR_RED ""
#define SAFT_COLOR_GREEN ""
#define SAFT_COLOR_CYAN ""
#define SAFT_COLOR_RESET ""
#endif

static int SAFT_TEST_TOTAL = 0 ;
static int SAFT_TEST_SUCCESS = 0 ;

/**
 * Print [file:line number].
 */
#define SAFT_PRINT_FILE_LINE() printf ("[%s:%d]", __FILE__, __LINE__)

/**
 * Print a failure message.
 * @param op1 first operand used in test.
 * @param op2 second operand used in test.
 * @param print printing function for `exp` and `test` variables.
 */
#define SAFT_PRINT_FAILURE(op1,op2,print)               \
        do                                              \
        {                                               \
                printf (SAFT_COLOR_RED) ;               \
                SAFT_PRINT_FILE_LINE() ;                \
                printf (" Failure\n") ;                 \
                printf (SAFT_COLOR_RESET) ;             \
                printf ("\top1: ") ;                    \
                print (op1) ;                           \
                printf ("\n\top2: ") ;                  \
                print (op2) ;                           \
                printf ("\n") ;                         \
        }                                               \
        while (0)

/**
 * Print a success message.
 */
#define SAFT_PRINT_SUCCESS()                    \
        do                                      \
        {                                       \
                printf (SAFT_COLOR_GREEN) ;     \
                SAFT_PRINT_FILE_LINE() ;        \
                printf (" Success\n") ;         \
                printf (SAFT_COLOR_RESET) ;     \
        }                                       \
        while (0)

/**
 * Use this function to create other macro.
 * @param cond is the test used (a boolean value)
 * @param op1 first operand used in test.
 * @param op2 first operand used in test.
 * @param print printing function for `typeof(op1)` values.
 */
#define SAFT_MK_ASSERT(cond,op1,op2,print)                              \
        do                                                              \
        {                                                               \
                SAFT_TEST_TOTAL++;                                      \
                if (cond)                                               \
                {                                                       \
                        SAFT_TEST_SUCCESS++;                            \
                        SAFT_PRINT_SUCCESS() ;                          \
                }                                                       \
                else                                                    \
                {                                                       \
                        SAFT_PRINT_FAILURE((op1),(op2),print) ;         \
                }                                                       \
        }                                                               \
        while (0)


#define SAFT_ASSERT_EQ(op1,op2,print)                                   \
                SAFT_MK_ASSERT(((op1)==(op2)),(op1),(op2),(print))

#define SAFT_ASSERT_NEQ(op1,op2,print)                                  \
                SAFT_MK_ASSERT(((op1)!=(op2)),(op1),(op2),(print))

#define SAFT_ASSERT_LT(op1,op2,print)                                   \
                SAFT_MK_ASSERT(((op1)<(op2)),(op1),(op2),(print))

#define SAFT_ASSERT_LTE(op1,op2,print)                                  \
                SAFT_MK_ASSERT(((op1)<=(op2)),(op1),(op2),(print))

#define SAFT_ASSERT_GT(op1,op2,print)                                   \
                SAFT_MK_ASSERT(((op1)>(op2)),(op1),(op2),(print))

#define SAFT_ASSERT_GTE(op1,op2,print)                                  \
                SAFT_MK_ASSERT(((op1)>=(op2)),(op1),(op2),(print))


/**
 * Print total number of tests and success ratio.
 */
#define SAFT_PRINT_SUMMARY()                                            \
                do                                                      \
                {                                                       \
                        printf (SAFT_COLOR_CYAN);                       \
                        printf ("Ran %d tests.\n", SAFT_TEST_TOTAL);    \
                        printf ("Success: %d/%d (%d%%).\n",             \
                                SAFT_TEST_SUCCESS,                      \
                                SAFT_TEST_TOTAL,                        \
                                (SAFT_TEST_SUCCESS * 100)               \
                                / SAFT_TEST_TOTAL);                     \
                        printf (SAFT_COLOR_RESET);                      \
                }                                                       \
                while (0)

/**
 * Basic printers you do not want to rewrite each time.
 * The use of `static` prevent `multiple definition` errors.
 */
static void saft_print_int (int d) { printf ("%d", d) ; }
static void saft_print_uint (unsigned int u) { printf ("%u", u) ; }
static void saft_print_float (float f) { printf ("%f", f) ; }
static void saft_print_string (char * s) { printf ("%s", s) ; }

#endif
