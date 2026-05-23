#ifndef __EDSA_LINKED_LIST_FUNCTIONAL_FUNCTIONS_H_
#define __EDSA_LINKED_LIST_FUNCTIONAL_FUNCTIONS_H_

#include "linked-list-base.h"

/**
 * @brief: A generic function type used upon iterable data structures
 * @param -> An element belonging to an iterable
 * @return -> A value that satisfies the callee's purpose (map, filter, reduce)
 **/
/* The param void* can have more than 1 argument stored as a list of some sort
 */
/* Since this is completely generic we can't check for validity of arguments */
/* The validity of the function is dependent on the callee */
typedef void *(*EdsaLinkedListLambda1)(void *);
typedef void *(*EdsaLinkedListLambda2)(void *, void *);

/**
 * @brief: Maps all linked list elements in iteration using a modifier function
 *pointer
 * @param list -> The linked list to map
 * @param modifier -> The modifier function
 * @return The mapped linked list duplicate
 **/
EdsaLinkedList *
linked_list_map(EdsaLinkedList *list, EdsaLinkedListLambda1 modifier);

/**
 * @brief: Filters all linked list elements in iteration using a filter function
 * @param list -> The linked list to filter
 * @param filter -> The filter functions
 * @return The filtered linked list duplicate
 **/
EdsaLinkedList *
linked_list_filter(EdsaLinkedList *list, EdsaLinkedListLambda1 filter);

/**
 * @brief: Reduces all linked list elements to some accumulated value using a
 * fold function
 * @param obj -> The linked list to reduce
 * @param fold -> The fold function
 * @return The accumulated result
 **/
void *linked_list_reduce(EdsaLinkedList *list, EdsaLinkedListLambda2 fold);

#endif
