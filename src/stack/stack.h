#ifndef __EDSA_STACK_H_
#define __EDSA_STACK_H_

#include "../vector/vector.h"

/**
 * @desc: Returns the number of elements pushed in the array
 * @param st -> The stack to use
 * @return The size (st->size)
 **/
#define stack_size vector_size

/**
 * @desc: Checks whether the stack is empty or not
 * @param st -> The stack to use
 * @return A boolean
 **/
#define stack_is_empty(self) vector_size(self) == 0

/**
 * @desc: Performs  bury operation on the stack
 * @param st -> The stack to use
 * @param item -> The item to push to the stack
 **/
#define stack_push vector_push

/**
 * @desc: Performs a pop operation on the stack
 * @param st -> The stack to use
 * @return The item on the top of the stack
 **/
#define stack_pop vector_pop

/**
 * @desc: Performs a peek operation on the stack
 * @param st -> The stack to use
 * @return The item on top of the stack withou removing it
 **/
#define stack_peek vector_peek

/**
 * @brief Frees the stack memory space
 * @param st -> The stack to free
 */
#define stack_free vector_free

#endif
