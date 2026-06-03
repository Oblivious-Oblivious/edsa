# Preprocessor

Compile-time macros for C standard detection, variadic counting, and related metaprogramming.

## Include

```c
#include "edsa.h"
```

## API

| Macro                                             | Description                                                      |
| ------------------------------------------------- | ---------------------------------------------------------------- |
| `PREPROCESSOR_C_VERSION`                          | Detected C dialect as a year (`1989`, `1999`, `2011`, `2023`, …) |
| `PREPROCESSOR_EXPANSIONS_NUMBER_OF_ELEMENTS(...)` | Expand to the number of variadic arguments (C99+)                |
| `PREPROCESSOR_GNU`                                | Defined on GCC, Clang, and compatible toolchains                 |
| `PREPROCESSOR_32_BIT`                             | `1` when `uintptr_t` is 32-bit wide, otherwise `0`               |
| `p_inline`                                        | `static inline` (or `static` on pre-C99) with compiler hints     |

See `src/preprocessor/preprocessor.h` for the full macro set (loops, defer, type traits, etc.).

## Example

```c
#include "edsa.h"

#include <stdio.h>

p_inline int triple(int x) { return x * 3; }

int main(void) {
  printf("C version: %d\n", PREPROCESSOR_C_VERSION);
  printf("pointer width: %s-bit\n", PREPROCESSOR_32_BIT ? "32" : "64");

#ifdef PREPROCESSOR_GNU
  printf("toolchain: GNU-compatible\n");
#else
  printf("toolchain: other\n");
#endif

#if PREPROCESSOR_C_VERSION >= 1999
  printf(
    "variadic count: %d\n", PREPROCESSOR_EXPANSIONS_NUMBER_OF_ELEMENTS(a, b, c)
  );
#else
  printf("variadic count: (requires C99+)\n");
#endif

  printf("triple(4): %d\n", triple(4));

  return 0;
}
```
