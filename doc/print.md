# jlibc - print.h

Pretty printing.

## Usage

```c
#define JLIBC_PRINT_NO_PREFIX
#include "/path/to/print.h"
```

If you do not define `JLIBC_PRINT_NO_PREFIX` before including `print.h`,
every macro or function name will need to be prefixed by `JLIBC_PRINT_`.

## Features

- `LOCATION`: String representing the file and the line where
  you call this macro (e.g. "foo.c:167")
- `PRINT_IN_COLOR`: Print a message in color. Use the `printf` format.
- `PRINT_VAR`: print a variable (its name) and its value.

### Predefined printing functions

Some common types printing functions are provided.

- `print_int`
- `print_uint`
- `print_float`
- `print_string`

## Example

See [print.c](../example/print.c) file.

## License

`print.h` is distributed under the term of the
[MIT](http://opensource.org/licenses/MIT) license.
