# Ju's C Library - Bench

Function benchmarking.

```c
#define JLIBC_BENCH_NO_PREFIX
#include "/path/to/bench.h"
```

If you do not define `JLIBC_BENCH_NO_PREFIX` before including `bench.h`,
every macro or function name will need to be prefixed by `JLIBC_BENCH_`.

## Features

Safe (check for error and set a failure flag to 1 if needed) and
unsafe function benchmarking.

Timespec structure printing function.

## Example

See [bench.c](../example/bench.c) file.

## License

`bench.h` is distributed under the term of the
[MIT](http://opensource.org/licenses/MIT) license.
