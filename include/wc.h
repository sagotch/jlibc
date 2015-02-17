#include <string.h>
#include <stdlib.h>

#define JLIBC_WC_INCR(x) do { if ((x) != NULL) { *(x) += 1 } } while (0)

#define JLIBC_WC_DELIM "\n\r\t\v\f "

/** NOTE: If the input does not end with a '\n',
 *  the last line will not be counted. */

/**
 * Step WC on one char
 * @param c char matched at this step
 * @param cc char counter, may be NULL
 * @param wc word counter, may be NULL
 * @param lc line counter, may be NULL
 * @param o indicates if last call ended with a possibly
 *        unterminated word.
 * @param d character set to be used as word delimiter
 * @param dlen length of character set d
 */
#define JLIBC_WC_STEP(c,cc,wc,lc,o,d,dlen)      \
        do                                      \
        {                                       \
                JLIBC_WC_INCR (cc) ;            \
                if ((c) == '\n')                \
                {                               \
                        JLIBC_WC_INCR (lc) ;    \
                }                               \
                if (memchr ((d), (c), (dlen)))  \
                {                               \
                        if (*(o))               \
                        {                       \
                                *(o) = 0 ;      \
                        }                       \
                }                               \
                else if (!(*(o)))               \
                {                               \
                        JLIBC_WC_INCR (wc) ;    \
                        *(o) = 1 ;              \
                }                               \
        }                                       \
        while (0)


/**
 * Iterate JLIBC_WC_STEP on a buffer. Same parameter as JLIBC_WC_STEP
 * with additional:
 * @param b buffer
 * @param blen buffer length
 */
#define JLIBC_WC_WC(cc,wc,lc,o,d,dlen,b,blen)                           \
        do                                                              \
        {                                                               \
                for (int jlibc_i = 0 ; jlibc_i < (blen) ; jlibc_i++)    \
                {                                                       \
                        JLIBC_WC_STEP (b[jlibc_i],cc,wc,lc,o,d,dlen) ;  \
                }                                                       \
        }                                                               \
        while (0)
