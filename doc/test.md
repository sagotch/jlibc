# Ju's C Library - Test

Unit testing framework.

## Usage

```c
#define JLIBC_TEST_NO_PREFIX
#include "/path/to/test.h"
```

If you do not define `JLIBC_TEST_NO_PREFIX` before including `test.h`,
every macro or function name will need to be prefixed by `JLIBC_TEST_`.

To enable colors in test reports, add the `-DJLIBC_PRINT_ENABLE_COLOR`
flag to you C compiler.

## Features

### Basic equality tests

`ASSERT_X(op1,op2,print)` macros test two operands `op1` and `op2`
with a given operator. `print` is the function to use in order to
print these operands.

* `ASSERT_EQ`: test using `==` operator.
* `ASSERT_NEQ`: test using `!=` operator.
* `ASSERT_LT`: test using `<` operator.
* `ASSERT_LTE`: test using `<=` operator.
* `ASSERT_GT`: test using `>` operator.
* `ASSERT_GTE`: test using `>=` operator.

## Example

See [test.c](../example/test.c) file.

## License

`test.h` is distributed under the term of the
[MIT](http://opensource.org/licenses/MIT) license.
