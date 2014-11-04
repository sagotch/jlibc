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

#ifndef JLIBC_PRINT_H
#define JLIBC_PRINT_H 1

#ifdef JLIBC_PRINT_ENABLE_COLOR
#define JLIBC_PRINT_COLOR_RED "\x1b[31m"
#define JLIBC_PRINT_COLOR_GREEN "\x1b[32m"
#define JLIBC_PRINT_COLOR_CYAN "\x1b[36m"
#define JLIBC_PRINT_COLOR_RESET "\x1b[0m"
#else
#define JLIBC_PRINT_COLOR_RED ""
#define JLIBC_PRINT_COLOR_GREEN ""
#define JLIBC_PRINT_COLOR_CYAN ""
#define JLIBC_PRINT_COLOR_RESET ""
#endif

#define JLIBC_PRINT_STRINGIFY(x) #x
#define JLIBC_PRINT_TOSTRING(x) JLIBC_PRINT_STRINGIFY(x)
#define JLIBC_PRINT_LOCATION __FILE__ ":" JLIBC_PRINT_TOSTRING(__LINE__)

/**
 * Print `msg` with color `c` and restore terminal color.
 * `msg` is a
 * Note: This is supposed to work with gcc compiler and --std=c99 option.
 */
#define JLIBC_PRINT_PRINT_IN_COLOR(c,msg,...)                   \
        printf (c msg JLIBC_PRINT_COLOR_RESET, ##__VA_ARGS__)

/**
 * Print var value, e.g. `x = 1`.
 * @param var variable to print.
 * @param print function to use to print `var`.
 */
#define JLIBC_PRINT_PRINT_VAR(var,print,...)    \
        do                                      \
        {                                       \
                printf (#var " = ") ;           \
                print (var) ;                   \
        }                                       \
        while (0)

#ifdef JLIBC_PRINT_NO_PREFIX
#define COLOR_RED      JLIBC_PRINT_COLOR_RED
#define COLOR_GREEN    JLIBC_PRINT_COLOR_GREEN
#define COLOR_CYAN     JLIBC_PRINT_COLOR_CYAN
#define COLOR_RESET    JLIBC_PRINT_COLOR_RESET
#define LOCATION       JLIBC_PRINT_LOCATION
#define PRINT_IN_COLOR JLIBC_PRINT_PRINT_IN_COLOR
#define PRINT_VAR      JLIBC_PRINT_PRINT_VAR
#endif

#endif
