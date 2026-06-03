# Linked List

Singly linked list of `void *` items with optional custom allocators.

## Include

```c
#include "edsa.h"
```

## API

| Function                                                  | Description                   |
| --------------------------------------------------------- | ----------------------------- |
| `linked_list_new()`                                       | Allocate a new list           |
| `linked_list_add(list, obj)`                              | Append a pointer              |
| `linked_list_remove(list, obj)`                           | Remove first matching pointer |
| `linked_list_free(list)`                                  | Free list structure and nodes |
| `linked_list_set_allocator(list, ctx, alloc_fn, free_fn)` | Use a custom allocator        |

## Example

```c
#include "edsa.h"

int main(void) {
  EdsaLinkedList *l = linked_list_new();

  linked_list_add(l, (void *)1);
  linked_list_add(l, (void *)2);
  linked_list_remove(l, (void *)1);

  linked_list_free(l);
}
```
