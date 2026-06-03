#ifndef __EDSA_MIN_PQ_BINARY_HEAP_H_
#define __EDSA_MIN_PQ_BINARY_HEAP_H_

#include "../vector/vector.h"

#include <stdio.h>  /* printf */
#include <string.h> /* memcpy */

/**
 * @brief Swaps two heap slots byte-by-byte
 * @param a -> Pointer to the first element
 * @param b -> Pointer to the second element
 */
#define _pq_swap_values(a, b)         \
  do {                                \
    char _pq_t[sizeof(*(a))];         \
    memcpy(_pq_t, (a), sizeof(*(a))); \
    memcpy((a), (b), sizeof(*(b)));   \
    memcpy((b), _pq_t, sizeof(*(a))); \
  } while(0)

/**
 * @brief Checks whether the structure is empty or not
 */
#define pq_is_empty vector_is_empty

/**
 * @brief The number of elements currently in the PQ
 */
#define pq_size vector_size

/**
 * @brief Get the minimum element (ON THE MIN_PQ ITS JUST `pq[0]`)
 * @param self -> The PQ object
 * @return The value of the minimum element, or NULL if empty
 */
#define pq_get_min(self) (vector_size(self) > 0 ? (self)[0] : 0)

/**
 * @brief Balance the heap upwards
 * @param self -> The PQ object
 * @param index -> The index of the element to fix
 * @param key -> The value of the element to fix
 */
#define pq_fix_up(self, index, key)                               \
  do {                                                            \
    size_t _pq_i  = (index);                                      \
    (self)[_pq_i] = (key);                                        \
    while(_pq_i > 0 && (self)[(_pq_i - 1) / 2] > (self)[_pq_i]) { \
      _pq_swap_values(&(self)[(_pq_i - 1) / 2], &(self)[_pq_i]);  \
      _pq_i = (_pq_i - 1) / 2;                                    \
    }                                                             \
  } while(0)

/**
 * @brief Balance the heap downwards
 * @param self -> The PQ object
 * @param index -> The index of the element to fix
 * @param key -> The value of the element to fix
 */
#define pq_fix_down(self, index, key)                                     \
  do {                                                                    \
    size_t _pq_i    = (index);                                            \
    size_t _pq_size = vector_size(self);                                  \
    (self)[_pq_i]   = (key);                                              \
    for(;;) {                                                             \
      size_t _pq_left  = (2 * _pq_i) + 1;                                 \
      size_t _pq_right = (2 * _pq_i) + 2;                                 \
      size_t _pq_small = _pq_i;                                           \
      if(_pq_left < _pq_size && (self)[_pq_left] < (self)[_pq_small]) {   \
        _pq_small = _pq_left;                                             \
      }                                                                   \
      if(_pq_right < _pq_size && (self)[_pq_right] < (self)[_pq_small]) { \
        _pq_small = _pq_right;                                            \
      }                                                                   \
      if(_pq_small == _pq_i) {                                            \
        break;                                                            \
      }                                                                   \
      _pq_swap_values(&(self)[_pq_i], &(self)[_pq_small]);                \
      _pq_i = _pq_small;                                                  \
    }                                                                     \
  } while(0)

/**
 * @brief Insert a new node on the priority queue
 * @param self -> The PQ object
 * @param key -> The value of the new element
 */
#define pq_insert(self, key)                                     \
  do {                                                           \
    vector_push((self), (key));                                  \
    pq_fix_up((self), vector_size(self) - 1, vector_last(self)); \
  } while(0)

/**
 * @brief Deletes the minimum element and fixes the heap.  Read it first with
 * `pq_get_min`.  Does nothing on an empty queue
 * @param self -> The PQ object
 */
#define pq_delete_min(self)              \
  do {                                   \
    if(vector_size(self) > 0) {          \
      (self)[0] = vector_last(self);     \
      vector_remove_last(self);          \
      pq_fix_down((self), 0, (self)[0]); \
    }                                    \
  } while(0)

/**
 * @brief Prints the current elements of the PQ
 * @param self -> The PQ object
 */
#define pq_print(self)                                     \
  do {                                                     \
    if((self) != NULL) {                                   \
      size_t _pq_i;                                        \
      for(_pq_i = 0; _pq_i < vector_size(self); _pq_i++) { \
        printf("%ld\n", (long)(self)[_pq_i]);              \
      }                                                    \
      printf("\n");                                        \
    }                                                      \
  } while(0)

/**
 * @brief Resets the priority queue by emptying it while keeping its capacity
 * @param self -> The PQ object
 */
#define pq_reset(self)                    \
  do {                                    \
    if(self) {                            \
      _vector_get_header(self)->size = 0; \
    }                                     \
  } while(0)

/**
 * @brief Frees the priority queue
 */
#define pq_free vector_free

/**
 * @brief Makes a priority queue allocator-aware
 */
#define pq_set_allocator vector_set_allocator

#endif
