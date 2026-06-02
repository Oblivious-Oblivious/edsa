#include "linked-list-base.h"

EdsaLinkedList *linked_list_new(void) {
  EdsaLinkedList *list =
    (EdsaLinkedList *)linked_list_allocator(NULL, sizeof(EdsaLinkedList));

  if(list == NULL) {
    return NULL;
  } else {
    list->head   = NULL;
    list->length = 0;
    return list;
  }
}

void linked_list_add(EdsaLinkedList *list, void *item) {
  struct EdsaLLNode **probe  = NULL;
  struct EdsaLLNode *newnode = NULL;

  if(list == NULL || item == NULL) {
    return;
  }

  /* Use the address to take advantage of a pointer to pointer approach */
  probe = &(list->head);

  newnode =
    (struct EdsaLLNode *)linked_list_allocator(NULL, sizeof(struct EdsaLLNode));
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
    old    = linked_list_allocator(old, 0);
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
    next   = (*probe)->next;
    *probe = linked_list_allocator(*probe, 0);
    *probe = next;
  }

  list->head   = NULL;
  list->length = 0;
  list         = linked_list_allocator(list, 0);
}
