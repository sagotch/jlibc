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

#ifndef JLIBC_TEST_H
#define JLIBC_TEST_H 1

#include <stdio.h>
#include "print.h"

/**
 * Structure used to record test suite informations.
 */
struct jlibc_test_suite
{
        char * id ;
        unsigned int test_total ;
        unsigned int test_success ;
} ;

/*
 * Create a new `struct jl_test_test_result` with `name` as its `id`.
 */
#define JLIBC_TEST_NEW_SUITE(name) (struct jlibc_test_suite) {(name),0,0}

/**
 * Test statistics with no section will be recorded in `jlibc_test_orphans`.
 */
static struct jlibc_test_suite jlibc_test_orphans =
{"jlbc_test_orphans", 0, 0} ;

/**
 * Test suite we are currently running.
 */
static struct jlibc_test_suite * jlibc_test_current = &jlibc_test_orphans ;

/**
 * Set the jlibc_current suite to `s`.
 */
#define JLIBC_TEST_START_SUITE(s)                                       \
        do                                                              \
        {                                                               \
                JLIBC_PRINT_PRINT_IN_COLOR(JLIBC_PRINT_COLOR_CYAN,      \
                                           "[START] %s\n", (s)->id) ;   \
                jlibc_test_current = (s);                               \
        }                                                               \
        while (0)

/**
 * Set the jlibc_current suite to `jl_test_orphans_suite`.
 */
#define JLIBC_TEST_STOP_SUITE()                                         \
        do                                                              \
        {                                                               \
                JLIBC_PRINT_PRINT_IN_COLOR(JLIBC_PRINT_COLOR_CYAN,      \
                                           "[STOP] \%s\n",              \
                                           jlibc_test_current->id) ;    \
                jlibc_test_current = &jlibc_test_orphans;               \
        }                                                               \
        while (0)

/**
 * Print a failure message.
 * @param macro name of the macro called (as string).
 * @param op1 first operand used in test.
 * @param op2 second operand used in test.
 * @param print printing function for `exp` and `test` variables.
 */
#define JLIBC_TEST_PRINT_FAILURE(macro,op1,op2,print)           \
        do                                                      \
        {                                                       \
                JLIBC_PRINT_PRINT_IN_COLOR                      \
                        (JLIBC_PRINT_COLOR_RED,                 \
                         "[FAIL] [" JLIBC_PRINT_LOCATION "]");  \
                printf (#macro " ( " #op1 ", " #op2" )\n");     \
                printf ("\t");                                  \
                JLIBC_PRINT_PRINT_VAR(op1,print);               \
                printf ("\n");                                  \
                printf ("\t");                                  \
                JLIBC_PRINT_PRINT_VAR(op2,print);               \
                printf ("\n");                                  \
        }                                                       \
        while (0)

/**
 * Print a success message.
 * @param macro name of the macro called (as string).
 * @param op1 first operand used in test.
 * @param op2 second operand used in test.
 * @param print printing function for `exp` and `test` variables.
 */
#define JLIBC_TEST_PRINT_SUCCESS(macro,op1,op2,print)            \
         do                                                      \
         {                                                       \
                 JLIBC_PRINT_PRINT_IN_COLOR                      \
                         (JLIBC_PRINT_COLOR_GREEN,               \
                          "[OK] [" JLIBC_PRINT_LOCATION "]") ;   \
                 printf (#macro " ( " #op1 ", " #op2" )\n") ;    \
         }                                                       \
         while (0)

/**
 * Use this function to create other macro.
 * Be sure to surround macro arguments with parenthesis since it is
 * not done inside this one (because of pretty printing concern).
 * @param macro macro name.
 * @param cond is the test used (a boolean value).
 * @param op1 first operand used in test.
 * @param op2 first operand used in test.
 * @param print printing function for `typeof(op1)` values.
 */
#define JLIBC_TEST_MK_ASSERT(macro,cond,op1,op2,print)                  \
        do                                                      \
        {                                                               \
                jlibc_test_current->test_total++ ;                      \
                if (cond)                                               \
                {                                                       \
                        jlibc_test_current->test_success++ ;            \
                        JLIBC_TEST_PRINT_SUCCESS(macro,op1,op2,print) ; \
                }                                                       \
                else                                                    \
                {                                                       \
                        JLIBC_TEST_PRINT_FAILURE(macro,op1,op2,print) ; \
                }                                                       \
        }                                                               \
        while (0)


#define JLIBC_TEST_ASSERT_EQ(op1,op2,print)             \
        JLIBC_TEST_MK_ASSERT(JLIBC_TEST_ASSERT_EQ,      \
                             ((op1)==(op2)),            \
                             (op1),                     \
                             (op2),                     \
                             (print))

#define JLIBC_TEST_ASSERT_NEQ(op1,op2,print)            \
        JLIBC_TEST_MK_ASSERT(JLIBC_TEST_ASSERT_NEQ,     \
                             ((op1)!=(op2)),            \
                             (op1),                     \
                             (op2),                     \
                             (print))

#define JLIBC_TEST_ASSERT_LT(op1,op2,print)            \
        JLIBC_TEST_MK_ASSERT(JLIBC_TEST_ASSERT_LT,     \
                             ((op1)<(op2)),            \
                             (op1),                    \
                             (op2),                    \
                             (print))

#define JLIBC_TEST_ASSERT_LTE(op1,op2,print)           \
        JLIBC_TEST_MK_ASSERT(JLIBC_TEST_ASSERT_LTE,    \
                             ((op1)<=(op2)),           \
                             (op1),                    \
                             (op2),                    \
                             (print))

#define JLIBC_TEST_ASSERT_GT(op1,op2,print)            \
        JLIBC_TEST_MK_ASSERT(JLIBC_TEST_ASSERT_GT,     \
                             ((op1)>(op2)),            \
                             (op1),                    \
                             (op2),                    \
                             (print))

#define JLIBC_TEST_ASSERT_GTE(op1,op2,print)           \
        JLIBC_TEST_MK_ASSERT(JLIBC_TEST_ASSERT_GTE,    \
                             ((op1)>=(op2)),           \
                             (op1),                    \
                             (op2),                    \
                             (print))


/**
 * Print total number of tests and success ratio.
 */
#define JLIBC_TEST_PRINT_RESULTS(r)                                     \
        do                                                              \
        {                                                               \
                JLIBC_PRINT_PRINT_IN_COLOR                              \
                        (JLIBC_PRINT_COLOR_CYAN,                        \
                         "[RESULTS] %s\n", (r)->id) ;                   \
                printf ("\t  Total: %d tests\n",                        \
                        (r)->test_total);                               \
                printf ("\tSuccess: %d/%d (%d%%)\n",                    \
                        (r)->test_success,                              \
                        (r)->test_total,                                \
                        ((r)->test_success*100)                         \
                        / (r)->test_total);                             \
                printf ("\tFailure: %d/%d (%d%%)\n",                    \
                        (r)->test_total-(r)->test_success,              \
                        (r)->test_total,                                \
                        (((r)->test_total-(r)->test_success)*100)       \
                        / (r)->test_total);                             \
        }                                                               \
        while (0)

/*
 * Test if every test in a suite `r` was a succes or not.
 */
#define JLIBC_TEST_RETURN_CODE(r) ((r)->test_total == (r)->test_success)

/**
 * Basic printers you do not want to rewrite each time.
 * The use of `static` prevent `multiple definition` errors.
 */
static void jlibc_test_print_int (int d) { printf ("%d", d) ; }
static void jlibc_test_print_uint (unsigned int u) { printf ("%u", u) ; }
static void jlibc_test_print_float (float f) { printf ("%f", f) ; }
static void jlibc_test_print_string (char * s) { printf ("%s", s) ; }

#ifdef JLBIC_TEST_NO_PREFIX
#define NEW_SUITE     JLIBC_TEST_NEW_SUITE
#define START_SUITE   JLIBC_TEST_START_SUITE
#define STOP_SUITE    JLIBC_TEST_STOP_SUITE
#define RETURN_CODE   JLIBC_TEST_RETURN_CODE
#define PRINT_RESULTS JLIBC_TEST_PRINT_RESULTS
#define ASSERT_EQ     JLIBC_TEST_ASSERT_EQ
#define ASSERT_NEQ    JLIBC_TEST_ASSERT_NEQ
#define ASSERT_LT     JLIBC_TEST_ASSERT_LT
#define ASSERT_LTE    JLIBC_TEST_ASSERT_LTE
#define ASSERT_GT     JLIBC_TEST_ASSERT_GT
#define ASSERT_GTE    JLIBC_TEST_ASSERT_GTE
#define print_int     jlibc_test_print_int
#define print_uint    jlibc_test_print_uint
#define print_float   jlibc_test_print_float
#define print_string  jlibc_test_print_string
#endif

#endif // #ifndef JLIBC_TEST_H
