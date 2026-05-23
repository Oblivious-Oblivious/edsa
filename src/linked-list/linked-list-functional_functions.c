#include "linked-list-functional-functions.h"

EdsaLinkedList *
linked_list_map(EdsaLinkedList *list, EdsaLinkedListLambda1 modifier) {
  EdsaLinkedList *dup       = NULL;
  struct EdsaLLNode **probe = NULL;

  if(list == NULL || modifier == NULL) {
    return NULL;
  }

  dup = linked_list_new();

  /* Typecast and use the address to take advantage of a pointer to pointer
   * approach */
  probe = &(list->head);

  /* Dereference once */
  while(*probe) {
    void *item = (*probe)->item;
    linked_list_add(dup, modifier(item));

    /* Point probe to the next node */
    probe = (struct EdsaLLNode **)&(*probe)->next;
  }

  return dup;
}

EdsaLinkedList *
linked_list_filter(EdsaLinkedList *list, EdsaLinkedListLambda1 filter) {
  EdsaLinkedList *dup       = NULL;
  struct EdsaLLNode **probe = NULL;

  if(list == NULL || filter == NULL) {
    return NULL;
  }

  dup = linked_list_new();

  /* Typecast and use the address to take advantage of a pointer to pointer
   * approach */
  probe = &(list->head);

  /* Dereference once */
  while(*probe) {
    void *item = (*probe)->item;
    if(!filter(item)) {
      linked_list_add(dup, item);
    }

    /* Point probe to the next node */
    probe = (struct EdsaLLNode **)&(*probe)->next;
  }

  return dup;
}

void *linked_list_reduce(EdsaLinkedList *list, EdsaLinkedListLambda2 fold) {
  struct EdsaLLNode **probe = NULL;
  void *accumulator         = NULL;

  if(list == NULL || fold == NULL) {
    return NULL;
  }

  probe = (&list->head);

  /* Get the initial value */
  /* Create the value that gets returned with the accumulation of the vector
   * elements */
  accumulator = (*probe)->item;

  /* Start counting from the next */
  probe = (struct EdsaLLNode **)&(*probe)->next;

  while(*probe) {
    void *current = (*probe)->item;
    accumulator   = fold(accumulator, current);
    probe         = (struct EdsaLLNode **)&(*probe)->next;
  }

  return accumulator;
}
