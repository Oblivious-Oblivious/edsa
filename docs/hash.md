# Hash

Non-cryptographic hash functions for keys and buffers. All return `size_t` and take a pointer plus byte length.

## Include

```c
#include "edsa.h"
```

## Functions

| Function                      | Description                                                  |
| ----------------------------- | ------------------------------------------------------------ |
| `hash_fnv1a(key, size)`       | FNV-1a (32-bit on 32-bit platforms, 64-bit otherwise)        |
| `hash_komihash(key, size)`    | komihash (default for `EdsaTable` via `TABLE_HASH_FUNCTION`) |
| `hash_murmurhash3(key, size)` | MurmurHash3 x86/x64 128-bit, truncated to `size_t`           |
| `hash_xxh3(key, size)`        | xxHash (XXH32 on 32-bit, XXH3_64bits on 64-bit)              |

On 32-bit builds (`PREPROCESSOR_32_BIT`), `hash_komihash` masks to 32 bits.

## Table integration

`table.h` uses `hash_komihash` by default. Override before including `edsa.h`:

```c
#define TABLE_HASH_FUNCTION hash_xxh3
#include "edsa.h"
```

## Example

```c
#include "edsa.h"
#include <stdio.h>

int main(void) {
  const char *key = "hello";
  size_t len = 5;

  printf("%zu\n", hash_fnv1a(key, len));
  printf("%zu\n", hash_komihash(key, len));
  printf("%zu\n", hash_murmurhash3(key, (int)len));
  printf("%zu\n", hash_xxh3(key, len));
}
```

## Licenses

Third-party implementations ship with their own licenses under `src/hash/komihash/` and `src/hash/xxh3/`.
