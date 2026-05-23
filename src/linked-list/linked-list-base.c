#include "linked-list-base.h"

EdsaLinkedList *linked_list_new(void) {
  EdsaLinkedList *list = (EdsaLinkedList *)malloc(sizeof(EdsaLinkedList));
  list->head           = NULL;
  list->length         = 0;
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

  /* Create a new node */
  newnode       = (struct EdsaLLNode *)malloc(sizeof(struct EdsaLLNode));
  newnode->item = (void *)malloc(sizeof(item));
  newnode->item = item;

  /* Traverse to the end of the linked list */
  while(*probe) {
    probe = (struct EdsaLLNode **)&(*probe)->next;
  }

  newnode->next = (struct EdsaLLNode *)*probe;
  *probe        = newnode;
  list->length++;
}

/* TODO -> FIX MEMORY WHEN REMOVING */
void linked_list_remove(EdsaLinkedList *list, void *item) {
  struct EdsaLLNode **probe = NULL;

  if(list == NULL || item == NULL) {
    return;
  }

  probe = &(list->head);

  while((*probe) && (*probe)->item != list) {
    probe = (struct EdsaLLNode **)&(*probe)->next;
  }

  *probe = (struct EdsaLLNode *)((*probe)->next);
}

void linked_list_free(EdsaLinkedList *list) {
  struct EdsaLLNode **probe = NULL;
  struct EdsaLLNode *next   = NULL;

  if(list == NULL) {
    return;
  }

  probe = &(list->head);

  while(*probe) {
    next = (*probe)->next;
    free(*probe);
    *probe = next;
  }

  list->head   = NULL;
  list->length = 0;
}
