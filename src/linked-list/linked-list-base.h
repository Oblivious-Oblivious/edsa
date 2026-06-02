#ifndef __EDSA_LINKED_LIST_BASE_H_
#define __EDSA_LINKED_LIST_BASE_H_

#include <stdlib.h> /* realloc */

#ifndef linked_list_allocator
  #define linked_list_allocator realloc
#endif

/**
 * @brief: A linked list node with a typed object item
 * @param item -> The typed object contained in the linked list node
 * @param next -> The next node on the linked list
 **/
struct EdsaLLNode {
  void *item;
  struct EdsaLLNode *next;
};

/**
 * @brief: A helper linked list helper struct containing the head node
 * @param length -> The number of elements in the linked list
 * @param head -> The head node of the list
 **/
typedef struct EdsaLinkedList {
  size_t length;
  struct EdsaLLNode *head;
} EdsaLinkedList;

/**
 * @brief: Creates a new linked list instance and initiates the head node
 * @return The newly created typed linked list
 **/
EdsaLinkedList *linked_list_new(void);

/**
 * @brief: Adds a new node in the linked list
 * @param list -> The list to append to
 * @param obj -> The node to append
 **/
void linked_list_add(EdsaLinkedList *list, void *obj);

/**
 * @brief: Finds and removes a node from the list
 * @param list -> The list to remove from
 * @param obj -> The node to remove
 **/
void linked_list_remove(EdsaLinkedList *list, void *obj);

/**
 * @brief Frees the list structure
 * @param list -> The list to free
 */
void linked_list_free(EdsaLinkedList *list);

#endif
