#ifndef __EDSA_MIN_PQ_BINARY_HEAP_H_
#define __EDSA_MIN_PQ_BINARY_HEAP_H_

#include "../boolean/boolean.h"

#include <stdio.h>  /* printf */
#include <stdlib.h> /* realloc */

#ifndef pq_allocator
  #define pq_allocator realloc
#endif

typedef struct EdsaMinPQBinaryHeap {
  void **A;
  size_t size;
  size_t max_size;
} EdsaMinPQBinaryHeap;

/**
 * @brief Allocated new memory space for the PQ
 * @param max_size -> The maximum size to store
 * @return EdsaMinPQBinaryHeap* -> The newly created object
 */
EdsaMinPQBinaryHeap *pq_new(size_t max_size);

/**
 *
 * @brief Checks whether the structure is empty or not
 * @param self -> The PQ object
 * @return true -> if empty else false
 */
bool pq_is_empty(EdsaMinPQBinaryHeap *self);

/**
 * @brief Get the minimum element (ON THE MIN_PQ ITS JUST `pq[0]`)
 * @param self -> The PQ object
 * @return void* -> The value of the minimum element
 */
void *pq_get_min(EdsaMinPQBinaryHeap *self);

/**
 * @brief Deletes the minimum element and fixes the heap
 * @param self -> The PQ object
 * @return void* -> The element deleted
 */
void *pq_delete_min(EdsaMinPQBinaryHeap *self);

/**
 * @brief Balance the heap upwards
 * @param self -> The PQ object
 * @param i -> The index of the element to fix
 * @param key -> The value of the element to fix
 */
void pq_fix_up(EdsaMinPQBinaryHeap *self, size_t index, void *key);

/**
 * @brief Balance the heap downwards
 * @param self -> The PQ object
 * @param i -> The index of the element to fix
 * @param key -> The value of the element to fix
 */
void pq_fix_down(EdsaMinPQBinaryHeap *self, size_t index, void *key);

/**
 * @brief Insert a new node on the priory queue
 * @param self -> The PQ object
 * @param key -> The value of the new element
 */
void pq_insert(EdsaMinPQBinaryHeap *self, void *key);

/**
 * @brief Prints the current elements of the PQ
 * @param self -> The PQ object
 */
void pq_print(EdsaMinPQBinaryHeap *self);

/**
 * @brief Resets the priority queue by freeling the structure and reallocating
 * space
 * @param self -> The PQ object
 */
void pq_reset(EdsaMinPQBinaryHeap *self);

/**
 * @brief Frees the priority queue
 * @param self -> The PQ object
 */
void pq_free(EdsaMinPQBinaryHeap *self);

#endif
