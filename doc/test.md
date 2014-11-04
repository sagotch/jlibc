# SAFT

SAFT (for Simple-As-F*ck Testing), is a basic unit testing framework
for C language.

## Usage

Include `SAFT.h` in your test file. If you want to enable colors in
test reports, add `-DSAFT_ENABLE_COLOR` flag to you C compiler.

## Features

### Basic equality tests

`SAFT_ASSERT_X(op1,op2,print)` macros test two operands `op1` and
`op2` with a given operator. `print` is the function to use in order
to print these operands.

* `SAFT_ASSERT_EQ`: test using `==` operator.
* `SAFT_ASSERT_NEQ`: test using `!=` operator.
* `SAFT_ASSERT_LT`: test using `<` operator.
* `SAFT_ASSERT_LTE`: test using `<=` operator.
* `SAFT_ASSERT_GT`: test using `>` operator.
* `SAFT_ASSERT_GTE`: test using `>=` operator.

### Predefined printing functions

Some printing functions for common types are provided.

* `saft_print_int`
* `saft_print_uint`
* `saft_print_float`
* `saft_print_string`

## Example

This file:
```
#include "SAFT.h"

int main (void)
{
        SAFT_ASSERT_EQ(0,2,saft_print_int);
        SAFT_ASSERT_NEQ(1,0,saft_print_int);

        SAFT_ASSERT_LT(0.0,0.2,saft_print_float);
        SAFT_ASSERT_LTE(0.2,0.2,saft_print_float);

        SAFT_ASSERT_GT(0.0,0.2,saft_print_float);
        SAFT_ASSERT_GTE(0.2,0.2,saft_print_float);

        SAFT_PRINT_RESULTS();
        return 0 ;
}
```

Produce this output:
```
[FAIL] [bar.c:5] SAFT_ASSERT_EQ ( (0), (2) )
       (0) = 0
       (2) = 2
[OK] [bar.c:6] SAFT_ASSERT_NEQ ( (1), (0) )
[OK] [bar.c:8] SAFT_ASSERT_LT ( (0.0), (0.2) )
[OK] [bar.c:9] SAFT_ASSERT_LTE ( (0.2), (0.2) )
[FAIL] [bar.c:11] SAFT_ASSERT_GT ( (0.0), (0.2) )
       (0.0) = 0.000000
       (0.2) = 0.200000
[OK] [bar.c:12] SAFT_ASSERT_GTE ( (0.2), (0.2) )
[RESULTS]
          Total: 6 tests
          Success: 4/6 (66%)
          Failure: 2/6 (33%)
```

## License

`SAFT.h` is distributed under the term of the
[MIT](http://opensource.org/licenses/MIT) license.
