# Ju's C Library - Arg

Command line arguments parsing and options setting.

```c
#define JLIBC_ARG_NO_PREFIX
#include "/path/to/arg.h"
```

If you do not define `JLIBC_ARG_NO_PREFIX` before including `arg.h`,
every macro or function name will need to be prefixed by `JLIBC_ARG_`.

## Features

`PARSE_ARG(argc, argv, optv, nc, nv)` will parse `argv` (which contains
`argv` values), and set options contained in `optv` array depending on
what is found during parsing. `nc` and `nv` are pointers which will receive
the address of the first argument not being an option defined in `optv`
and the number of remaining of values after it (including the one pointed
by `nv`).

## Example

See [arg.c](../example/arg.c) file.

## License

`test.h` is distributed under the term of the
[MIT](http://opensource.org/licenses/MIT) license.
