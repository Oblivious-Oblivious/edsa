#ifndef __EDSA_STACK_H_
#define __EDSA_STACK_H_

#include "../vector/vector.h"

/**
 * @brief Makes a stack allocator-aware
 */
#define stack_set_allocator vector_set_allocator

/**
 * @brief Returns the number of elements pushed in the array
 */
#define stack_size vector_size

/**
 * @brief Checks whether the stack is empty or not
 */
#define stack_is_empty vector_is_empty

/**
 * @brief Performs  bury operation on the stack
 */
#define stack_push vector_push

/**
 * @brief Performs a pop operation on the stack
 */
#define stack_pop vector_pop

/**
 * @brief Performs a peek operation on the stack
 */
#define stack_peek vector_peek

/**
 * @brief Frees the stack memory space
 */
#define stack_free vector_free

#endif
