# Hash

Non-cryptographic hash functions for keys and buffers. Each returns `size_t` from a pointer and byte length.

## Include

```c
#include "edsa.h"
```

## API

| Function                      | Description                                                       |
| ----------------------------- | ----------------------------------------------------------------- |
| `hash_fnv1a(key, size)`       | FNV-1a; 32-bit variant on 32-bit targets, 64-bit otherwise        |
| `hash_komihash(key, size)`    | Fast komihash digest; default `TABLE_HASH_FUNCTION` for tables    |
| `hash_murmurhash3(key, size)` | MurmurHash3 128-bit core, folded to `size_t` (x86 vs x64 backend) |
| `hash_xxh3(key, size)`        | xxHash; `XXH32` on 32-bit, `XXH3_64bits` on 64-bit                |

On 32-bit builds (`PREPROCESSOR_32_BIT`), `hash_komihash` masks the result to 32 bits.

## Table integration

Override before including `edsa.h`:

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
  size_t len      = 5;

  printf("%zu\n", hash_fnv1a(key, len));
  printf("%zu\n", hash_komihash(key, len));
  printf("%zu\n", hash_murmurhash3(key, (int)len));
  printf("%zu\n", hash_xxh3(key, len));

  return 0;
}
```

## Licenses

Third-party implementations ship with their own licenses under `src/hash/komihash/` and `src/hash/xxh3/`.
