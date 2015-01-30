# Ju's C Library - CPU

Busy you CPU.

## Usage

```c
#define JLIBC_CPU_NO_PREFIX
#include "/path/to/cpu.h"
```

If you do not define `JLIBC_CPU_NO_PREFIX` before including `cpu.h`,
every macro or function name will need to be prefixed by `JLIBC_CPU_`.

## Features

`cpu.h` can make your CPU busy at a certain rate. It may be useful
to test your application in a low (available) ressources environment.

Use `CPU_LOAD(&pid,25.)` to fork a child process which will create
CPU load using 25% of CPU capacity.

## Example

See [cpu.c](../example/cpu.c) file.

## License

`cpu.h` is distributed under the term of the
[MIT](http://opensource.org/licenses/MIT) license.
