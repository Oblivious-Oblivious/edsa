#include "linked-list-dup.h"

EdsaLinkedList *linked_list_dup(EdsaLinkedList *list) {
  struct EdsaLLNode **probe = NULL;
  EdsaLinkedList *dup       = NULL;

  if(list == NULL) {
    return NULL;
  }

  probe = &(list->head);
  dup   = linked_list_new();
  if(dup == NULL) {
    return NULL;
  }

  while(*probe) {
    linked_list_add(dup, (*probe)->item);

    probe = (struct EdsaLLNode **)&(*probe)->next;
  }

  return dup;
}
