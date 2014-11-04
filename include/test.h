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

#ifdef JL_TEST_ENABLE_COLOR
#define JL_TEST_COLOR_RED "\x1b[31m"
#define JL_TEST_COLOR_GREEN "\x1b[32m"
#define JL_TEST_COLOR_CYAN "\x1b[36m"
#define JL_TEST_COLOR_RESET "\x1b[0m"
#else
#define JL_TEST_COLOR_RED ""
#define JL_TEST_COLOR_GREEN ""
#define JL_TEST_COLOR_CYAN ""
#define JL_TEST_COLOR_RESET ""
#endif

/**
 * Structure used to record test suite informations.
 */
struct jl_test_test_suite
{
        char * id ;
        unsigned int test_total ;
        unsigned int test_success ;
} ;

/*
 * Create a new `struct jl_test_test_result` with `name` as its `id`.
 */
#define JL_TEST_NEW_SUITE(name) (struct jl_test_test_suite) {(name),0,0}

/**
 * Test statistics with no section will be recorded in `jl_test_orphan`.
 */
static struct jl_test_test_suite jl_test_orphans_suite =
        JL_TEST_NEW_SUITE ("jl_test_orphans_suite") ;

/**
 * Test suite we are currently running.
 */
static struct jl_test_test_suite * current_suite = &jl_test_orphans_suite ;

/**
 * Set the current suite to `s`.
 */
#define JL_TEST_START_SUITE(s)                                  \
        (JL_TEST_PRINT_IN_COLOR(JL_TEST_COLOR_CYAN, "[START]"), \
         printf(" %s\n", (s)->id),                              \
         current_suite = (s))

/**
 * Set the current suite to `jl_test_orphans_suite`.
 */
#define JL_TEST_STOP_SUITE()                                    \
        (JL_TEST_PRINT_IN_COLOR(JL_TEST_COLOR_CYAN, "[STOP]"),  \
         printf(" %s\n", current_suite->id),                    \
         current_suite = &jl_test_orphans_suite)

/**
 * Print [file:line number].
 */
#define JL_TEST_PRINT_FILE_LINE() printf ("[%s:%d]", __FILE__, __LINE__)

/**
 * Print `msg` with color `c` and restore terminal color.
 */
#define JL_TEST_PRINT_IN_COLOR(c,msg) printf (c msg JL_TEST_COLOR_RESET)

/**
 * Print a macro call as it would be written in a C source file.
 * @param macro name of the macro called (as string).
 * @param op1 first operand used in `macro`.
 * @param op2 second operand used in `macro`.
 * @param print printer used in `macro`
 */
#define JL_TEST_PRINT_MACRO_CALL(macro,op1,op2)         \
        printf (#macro " ( " #op1 ", " #op2" )")

/**
 * @param var variable to print.
 * @param print function to use to print `var`.
 */
#define JL_TEST_PRINT_VAR(var,print)            \
        do                                      \
        {                                       \
                printf ("\t" #var " = ") ;      \
                print (var) ;                   \
        }                                       \
        while (0)
/**
 * Print a failure message.
 * @param macro name of the macro called (as string).
 * @param op1 first operand used in test.
 * @param op2 second operand used in test.
 * @param print printing function for `exp` and `test` variables.
 */
#define JL_TEST_PRINT_FAILURE(macro,op1,op2,print)                      \
        do                                                              \
        {                                                               \
                JL_TEST_PRINT_IN_COLOR(JL_TEST_COLOR_RED,"[FAIL] ") ;   \
                JL_TEST_PRINT_FILE_LINE() ; printf(" ") ;               \
                JL_TEST_PRINT_MACRO_CALL(macro,op1,op2) ; printf ("\n") ; \
                JL_TEST_PRINT_VAR(op1,print) ; printf ("\n") ;          \
                JL_TEST_PRINT_VAR(op2,print) ; printf ("\n") ;          \
        }                                                               \
        while (0)

/**
 * Print a success message.
 * @param macro name of the macro called (as string).
 * @param op1 first operand used in test.
 * @param op2 second operand used in test.
 * @param print printing function for `exp` and `test` variables.
 */
#define JL_TEST_PRINT_SUCCESS(macro,op1,op2,print)                      \
        do                                                              \
        {                                                               \
         JL_TEST_PRINT_IN_COLOR(JL_TEST_COLOR_GREEN,"[OK] ") ;          \
         JL_TEST_PRINT_FILE_LINE() ; printf(" ") ;                      \
         JL_TEST_PRINT_MACRO_CALL(macro,op1,op2) ; printf ("\n") ;      \
         }                                                              \
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
#define JL_TEST_MK_ASSERT(macro,cond,op1,op2,print)                     \
        do                                                              \
        {                                                               \
                current_suite->test_total++ ;                           \
                if (cond)                                               \
                {                                                       \
                        current_suite->test_success++ ;                 \
                        JL_TEST_PRINT_SUCCESS(macro,op1,op2,print) ;    \
                }                                                       \
                else                                                    \
                {                                                       \
                        JL_TEST_PRINT_FAILURE(macro,op1,op2,print) ;    \
                }                                                       \
        }                                                               \
        while (0)


#define JL_TEST_ASSERT_EQ(op1,op2,print)                \
                JL_TEST_MK_ASSERT(JL_TEST_ASSERT_EQ,    \
                                  ((op1)==(op2)),       \
                                  (op1),                \
                                  (op2),                \
                                  (print))

#define JL_TEST_ASSERT_NEQ(op1,op2,print)               \
                JL_TEST_MK_ASSERT(JL_TEST_ASSERT_NEQ,   \
                                  ((op1)!=(op2)),       \
                                  (op1),                \
                                  (op2),                \
                                  (print))

#define JL_TEST_ASSERT_LT(op1,op2,print)                \
                JL_TEST_MK_ASSERT(JL_TEST_ASSERT_LT,    \
                                  ((op1)<(op2)),        \
                                  (op1),                \
                                  (op2),                \
                                  (print))

#define JL_TEST_ASSERT_LTE(op1,op2,print)               \
                JL_TEST_MK_ASSERT(JL_TEST_ASSERT_LTE,   \
                                  ((op1)<=(op2)),       \
                                  (op1),                \
                                  (op2),                \
                                  (print))

#define JL_TEST_ASSERT_GT(op1,op2,print)                \
                JL_TEST_MK_ASSERT(JL_TEST_ASSERT_GT,    \
                                  ((op1)>(op2)),        \
                                  (op1),                \
                                  (op2),                \
                                  (print))

#define JL_TEST_ASSERT_GTE(op1,op2,print)               \
                JL_TEST_MK_ASSERT(JL_TEST_ASSERT_GTE,   \
                                  ((op1)>=(op2)),       \
                                  (op1),                \
                                  (op2),                \
                                  (print))


/**
 * Print total number of tests and success ratio.
 */
#define JL_TEST_PRINT_RESULTS(r)                                        \
                do                                                      \
                {                                                       \
                        JL_TEST_PRINT_IN_COLOR(JL_TEST_COLOR_CYAN,      \
                                               "[RESULTS] ") ;          \
                        printf ("%s\n", (r)->id);                       \
                        printf ("\t  Total: %d tests\n",                \
                                (r)->test_total);                       \
                        printf ("\tSuccess: %d/%d (%d%%)\n",            \
                                (r)->test_success,                      \
                                (r)->test_total,                        \
                                ((r)->test_success*100)                 \
                                / (r)->test_total);                     \
                        printf ("\tFailure: %d/%d (%d%%)\n",            \
                                (r)->test_total-(r)->test_success,      \
                                (r)->test_total,                        \
                                (((r)->test_total-(r)->test_success)    \
                                 *100)                                  \
                                / (r)->test_total);                     \
                }                                                       \
                while (0)

/*
 * Test if every test in a suite `r` was a succes or not.
 */
#define JL_TEST_RETURN_CODE(r)                          \
                ((r)->test_total == (r)->test_success)

/**
 * Basic printers you do not want to rewrite each time.
 * The use of `static` prevent `multiple definition` errors.
 */
static void jl_test_print_int (int d) { printf ("%d", d) ; }
static void jl_test_print_uint (unsigned int u) { printf ("%u", u) ; }
static void jl_test_print_float (float f) { printf ("%f", f) ; }
static void jl_test_print_string (char * s) { printf ("%s", s) ; }

#endif // #ifndef JLIBC_TEST_H
