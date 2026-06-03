# Table

Open-addressing hash table with linear probing. Keys are C strings; values are `size_t`.

## Include

```c
#include "edsa.h"
```

## API

| Function                                            | Description                                                    |
| --------------------------------------------------- | -------------------------------------------------------------- |
| `table_init(self)`                                  | Allocate bucket vectors on a stack- or static `EdsaTable`      |
| `table_add(self, key, value)`                       | Insert or update a key-value pair                              |
| `table_get(self, key)`                              | Lookup by key; `TABLE_UNDEFINED` when missing                  |
| `table_remove(self, key)`                           | Remove a key (tombstone for probing)                           |
| `table_size(self)`                                  | Number of live entries                                         |
| `table_add_all(src, dest)`                          | Copy every entry from `src` into `dest`                        |
| `table_add_all_non_labels(src, dest)`               | Copy entries except keys starting with `@::`                   |
| `table_deinit(self)`                                | Free internal vectors; safe to call on zero-initialized tables |
| `table_set_allocator(self, ctx, alloc_fn, free_fn)` | Attach a custom allocator after `table_init()`                 |

Default hash: `hash_komihash` (`TABLE_HASH_FUNCTION`). See [hash](hash.md).

## Example

```c
#include "edsa.h"

#include <stdio.h>

int main(void) {
  unsigned char buf[4096];
  AllocatorArena arena = {0};
  EdsaTable t          = {0};
  EdsaTable src        = {0};
  EdsaTable dst        = {0};

  allocator_arena_init(&arena, buf, sizeof(buf));
  table_init(&t);
  table_set_allocator(&t, &arena, allocator_arena_alloc, NULL);

  table_add(&t, "key1", 100);
  table_add(&t, "key2", 200);
  table_add(&t, "key3", 300);

  printf("%zu\n", table_size(&t));
  printf("%zu\n", table_get(&t, "key1"));
  printf("%zu\n", table_get(&t, "key2"));
  printf("%zu\n", table_get(&t, "key3"));
  printf("%zu\n", table_get(&t, "key4")); /* TABLE_UNDEFINED */

  table_remove(&t, "key2");
  printf("%zu\n", table_size(&t));
  printf("%zu\n", table_get(&t, "key2")); /* TABLE_UNDEFINED */

  table_init(&src);
  table_add(&src, "a", 1);
  table_add(&src, "b", 2);
  table_init(&dst);
  table_add(&dst, "existing", 99);
  table_add_all(&src, &dst);
  printf("%zu\n", table_get(&dst, "a"));
  printf("%zu\n", table_get(&dst, "existing"));
  table_deinit(&src);
  table_deinit(&dst);

  table_init(&src);
  table_add(&src, "plain", 10);
  table_add(&src, "@::label", 20);
  table_init(&dst);
  table_add(&dst, "@::keep", 99);
  table_add_all_non_labels(&src, &dst);
  printf("%zu\n", table_get(&dst, "plain"));
  printf("%zu\n", table_get(&dst, "@::label")); /* TABLE_UNDEFINED */
  printf("%zu\n", table_get(&dst, "@::keep"));
  table_deinit(&src);
  table_deinit(&dst);

  table_deinit(&t);

  return 0;
}
```
