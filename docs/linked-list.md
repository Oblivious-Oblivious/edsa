# Linked List

Singly linked list of `void *` items with optional custom allocators.

## Include

```c
#include "edsa.h"
```

## API

| Function                                                  | Description                                               |
| --------------------------------------------------------- | --------------------------------------------------------- |
| `linked_list_new()`                                       | Allocate a list and initialize the head node              |
| `linked_list_add(list, obj)`                              | Append a pointer as a new node at the tail                |
| `linked_list_remove(list, obj)`                           | Find and unlink the first node whose `item` matches       |
| `linked_list_free(list)`                                  | Free the list structure and all nodes                     |
| `linked_list_set_allocator(list, ctx, alloc_fn, free_fn)` | Attach a custom allocator after `linked_list_new()`       |
| `linked_list_dup(list)`                                   | Shallow-copy the list into a new `EdsaLinkedList`         |
| `linked_list_map(list, modifier)`                         | Build a new list by applying `modifier` to each item      |
| `linked_list_filter(list, filter)`                        | Build a new list of items where `filter` returns non-NULL |
| `linked_list_reduce(list, fold)`                          | Fold items into one accumulated `void *` result           |

## Example

```c
#include "edsa.h"

#include <stdio.h>
#include <stdlib.h>

static long *heap_long(long v) {
  long *p = (long *)malloc(sizeof(long));
  *p      = v;
  return p;
}

static void heap_long_free(void *_allocator, void *ptr) {
  (void)_allocator;
  free(ptr);
}

static void linked_list_shallow_free(EdsaLinkedList *l) {
  linked_list_set_allocator(l, l->allocator, l->alloc_fn, NULL);
  linked_list_free(l);
}

static void *double_item(void *item) { return heap_long(*(long *)item * 2); }
static void *keep_positive_only(void *item) {
  return (void *)(long)(*(long *)item <= 0);
}
static void *sum(void *acc, void *item) {
  return (void *)(long)(*(long *)acc + *(long *)item);
}

int main(void) {
  EdsaLinkedList *l = NULL;
  EdsaLinkedList *copy = NULL;
  EdsaLinkedList *doubled = NULL;
  EdsaLinkedList *positives = NULL;
  void *total = NULL;
  long *neg = NULL;
  unsigned char buf[512];
  AllocatorArena arena = {0};

  l = linked_list_new();
  allocator_arena_init(&arena, buf, sizeof(buf));
  linked_list_set_allocator(l, &arena, allocator_arena_alloc, heap_long_free);

  linked_list_add(l, heap_long(10));
  neg = heap_long(-5);
  linked_list_add(l, neg);
  linked_list_add(l, heap_long(20));

  copy      = linked_list_dup(l);
  doubled   = linked_list_map(l, double_item);
  positives = linked_list_filter(l, keep_positive_only);
  total     = linked_list_reduce(positives, sum);

  printf("sum of positives: %ld\n", (long)total);

  linked_list_remove(l, neg);
  heap_long_free(NULL, neg);

  linked_list_free(doubled);
  linked_list_shallow_free(positives);
  linked_list_shallow_free(copy);
  linked_list_free(l);

  return 0;
}
```
