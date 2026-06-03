#include "linked-list-base.h"

EdsaLinkedList *linked_list_new(void) {
  EdsaLinkedList *list = (EdsaLinkedList *)malloc(sizeof(EdsaLinkedList));

  if(list == NULL) {
    return NULL;
  }
  list->head      = NULL;
  list->length    = 0;
  list->allocator = NULL;
  list->alloc_fn  = NULL;
  list->free_fn   = NULL;
  return list;
}

void linked_list_add(EdsaLinkedList *list, void *item) {
  struct EdsaLLNode **probe  = NULL;
  struct EdsaLLNode *newnode = NULL;

  if(list == NULL || item == NULL) {
    return;
  }

  /* Use the address to take advantage of a pointer to pointer approach */
  probe = &(list->head);

  newnode = list->alloc_fn
              ? (struct EdsaLLNode *)list->alloc_fn(
                  list->allocator, NULL, sizeof(struct EdsaLLNode)
                )
              : (struct EdsaLLNode *)malloc(sizeof(struct EdsaLLNode));
  if(newnode == NULL) {
    return;
  }
  newnode->item = item;

  /* Traverse to the end of the linked list */
  while(*probe) {
    probe = (struct EdsaLLNode **)&(*probe)->next;
  }

  newnode->next = (struct EdsaLLNode *)*probe;
  *probe        = newnode;
  list->length++;
}

void linked_list_remove(EdsaLinkedList *list, void *item) {
  struct EdsaLLNode **probe = NULL;
  struct EdsaLLNode *old    = NULL;

  if(list == NULL || item == NULL) {
    return;
  }

  probe = &(list->head);

  while((*probe) && (*probe)->item != item) {
    probe = (struct EdsaLLNode **)&(*probe)->next;
  }

  if(*probe) {
    old    = *probe;
    *probe = (struct EdsaLLNode *)((*probe)->next);
    if(list->alloc_fn) {
      list->alloc_fn(list->allocator, old, 0);
    } else {
      free(old);
    }
    list->length--;
  }
}

void linked_list_free(EdsaLinkedList *list) {
  struct EdsaLLNode **probe = NULL;
  struct EdsaLLNode *next   = NULL;

  if(list == NULL) {
    return;
  }

  probe = &(list->head);

  while(*probe) {
    if(list->free_fn) {
      list->free_fn(list->allocator, (*probe)->item);
    }
    next = (*probe)->next;
    if(list->alloc_fn) {
      list->alloc_fn(list->allocator, *probe, 0);
    } else {
      free(*probe);
    }
    *probe = next;
  }

  list->head   = NULL;
  list->length = 0;
  free(list);
}

void linked_list_set_allocator(
  EdsaLinkedList *list,
  void *allocator_ctx,
  allocator_alloc_fn alloc_fn,
  allocator_free_fn free_fn
) {
  if(list == NULL) {
    return;
  }
  list->allocator = allocator_ctx;
  list->alloc_fn  = alloc_fn;
  list->free_fn   = free_fn;
}
