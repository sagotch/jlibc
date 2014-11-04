/**
 * Short example showing how to use the jlibc test module.
 * Compile with:
 *     gcc -I ../include --std=c99 test.c
 * or  gcc -I ../include --std=c99 -DJLIBC_PRINT_ENABLE_COLOR test.c
 */

#define JLBIC_TEST_NO_PREFIX
#include "test.h"

int main (void)
{
        struct jlibc_test_suite eq_neq = NEW_SUITE ("eq_neq") ;
        START_SUITE(&eq_neq);
        ASSERT_EQ(0,2,print_int);
        ASSERT_NEQ(1,0,print_int);

        struct jlibc_test_suite lt_lte = NEW_SUITE ("lt_tle") ;
        START_SUITE(&lt_lte);
        ASSERT_LT(0.0,0.2,print_float);
        ASSERT_LTE(0.2,0.2,print_float);

        struct jlibc_test_suite gt_gte = NEW_SUITE ("gt_gte") ;
        START_SUITE(&gt_gte);
        ASSERT_GT(0.0,0.2,print_float);
        ASSERT_GTE(0.2,0.2,print_float);
        STOP_SUITE();

        ASSERT_EQ(0.0,0.0,print_float);

        PRINT_RESULTS(&eq_neq);
        PRINT_RESULTS(&lt_lte);
        PRINT_RESULTS(&gt_gte);
        PRINT_RESULTS(&jlibc_test_orphans);

        return RETURN_CODE(&eq_neq)
                && RETURN_CODE(&lt_lte)
                && RETURN_CODE(&gt_gte)
                && RETURN_CODE(&jlibc_test_orphans);
}
