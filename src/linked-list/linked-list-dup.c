#include "linked-list-dup.h"

EdsaLinkedList *linked_list_dup(EdsaLinkedList *list) {
  struct EdsaLLNode **probe = NULL;
  EdsaLinkedList *dup       = NULL;

  if(list == NULL) {
    return NULL;
  }

  /* Use the address to take advantage of a pointer to pointer approach */
  probe = &(list->head);
  dup   = linked_list_new();

  while(*probe) {
    linked_list_add(dup, (*probe)->item);

    /* Move to the next item */
    probe = (struct EdsaLLNode **)&(*probe)->next;
  }

  return dup;
}
