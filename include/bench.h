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

#ifndef JLIBC_BENCH_H
#define JLIBC_BENCH_H 1


/**
 * timespec structure printing function.
 */
#define JLIBC_BENCH_PRINT_TIMESPEC(t)                   \
        printf ("%ld.%09ld", (t)->tv_sec, (t)->tv_nsec)

/**
 * Compute difference between to timespec structures.
 * Every parameter is a struct timespec pointer.
 * @param res will receive the diff.
 * @param start first point in time.
 * @param start second point in time.
 */
#define JLIBC_BENCH_TIMESPEC_DIFF(res,start,end)                        \
        do                                                              \
        {                                                               \
                (res)->tv_sec = (end)->tv_sec - (start)->tv_sec ;       \
                (res)->tv_nsec = (end)->tv_nsec - (start)->tv_nsec ;    \
                if ((res)->tv_nsec < 0)                                 \
                {                                                       \
                        (res)->tv_sec -= 1;                             \
                        (res)->tv_nsec += 1E9 ;                         \
                }                                                       \
        }                                                               \
        while (0)
/**
 *
 * @param expression you want to benchmark. *MUST* return 0 on success.
 * @param n number of times `call` should be repeated.
 * @param t pointer to timespec structure to be filled with benchmark result.
 * @param clockid clockid_t to use to get times.
 * @param failure_flag variable which will be set to one if `call` fails.
 */
#define JLIBC_BENCH_BENCHMARK(call, n, t, clockid, failure_flag)        \
        do                                                              \
        {                                                               \
                int JLIBC_BENCH_i = (n) ;                               \
                struct timespec JLIBC_BENCH_start, JLIBC_BENCH_end ;    \
                if (clock_gettime ((clockid), &JLIBC_BENCH_start))      \
                {                                                       \
                        *(failure_flag) = 1 ;                           \
                        break ;                                         \
                }                                                       \
                while ((JLIBC_BENCH_i) --> 0)                           \
                {                                                       \
                        if (call)                                       \
                        {                                               \
                                *(failure_flag) = 1 ;                   \
                                break ;                                 \
                        }                                               \
                }                                                       \
                if (clock_gettime ((clockid), &JLIBC_BENCH_end))        \
                {                                                       \
                        *(failure_flag) = 1 ;                           \
                        break ;                                         \
                }                                                       \
                JLIBC_BENCH_TIMESPEC_DIFF                               \
                        (t, &JLIBC_BENCH_start, &JLIBC_BENCH_end);      \
        }                                                               \
        while (0)


#endif // #ifndef JLIBC_BENCH_H

#ifdef JLIBC_BENCH_NO_PREFIX
#define PRINT_TIMESPEC JLIBC_BENCH_PRINT_TIMESPEC
#define TIMESPEC_DIFF JLIBC_BENCH_TIMESPEC_DIFF
#define BENCHMARK JLIBC_BENCH_BENCHMARK
#endif
