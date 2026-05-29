#ifndef __EDSA_VECTOR_H_
#define __EDSA_VECTOR_H_

#include "../preprocessor/preprocessor.h"

#include <stdarg.h> /* va_list, va_arg, va_start, va_end */
#include <stddef.h> /* ptrdiff_t */
#include <stdlib.h> /* NULL, realloc */
#include <string.h> /* memmove, memset */

/**
 * @brief Metadata for a vector.  Stores the size and capacity
 * of the vector one byte before the vector data
 * @param size -> The number of elements in the vector
 * @param capacity -> The current capacity in bytes (number of elements *
 * sizeof(type))
 */
typedef struct {
  size_t size;
  size_t capacity;
} _vector_header;

/**
 * @brief Calculates the header of a vector
 * @param self -> The vector pointer
 * @return The header of the vector
 */
#define _vector_get_header(self) ((_vector_header *)(self) - 1)

/**
 * @brief Grabs the sizeof the vector element by dereferencing the pointer
 * @param self -> The vector pointer
 * @return The sizeof the vector element
 */
#define _vector_selfptr_size(self) sizeof(*(self)) /* NOLINT */

/**
 * @brief A grow function that grows the vector by a given number of elements.
 * Is using the address of self and casting it to a void** and then
 * dereferencing it, a trick to treat all types as raw memory in a type-safe
 * manner.
 * @param self -> The vector pointer
 * @param n -> The number of elements to grow the vector by
 * @return The new pointer to the vector
 */
#define _vector_grow(self, n) \
  (*(void **)&(self) =        \
     _vector_growf((self), _vector_selfptr_size(self), (n), 0))

/**
 * @brief Decides whether to grow the vector or not based on the current
 * capacity
 * @param self -> The vector pointer
 * @param n -> The number of elements to grow the vector by
 * @return The new pointer to the vector
 */
#define _vector_maybegrow(self, n)                                             \
  ((!(self) ||                                                                 \
    _vector_get_header(self)->size + (n) > _vector_get_header(self)->capacity) \
     ? (_vector_grow(self, n), 0)                                              \
     : 0)

#ifndef vector_allocator
  #define vector_allocator realloc
#endif

#define vector_initialize(self) ((self) = NULL, _vector_maybegrow(self, 1))

/**
 * @brief Initializes a vector with a given size
 * @param v -> The vector to initialize
 * @param n -> The size of the vector
 */
#define vector_initialize_n(self, n)     \
  ((self) = NULL,                        \
   _vector_maybegrow(self, n),           \
   _vector_get_header(self)->size = (n), \
   memset((self), 0, (n) * sizeof((self)[0])))

/**
 * @brief Adds a new element in the vector
 * @param self -> The vector to use
 * @param item -> The item to add
 **/
#define vector_add(self, item) \
  (_vector_maybegrow(self, 1), \
   (self)[_vector_get_header(self)->size++] = (item))

/**
 * @brief Adds a larger element in the vector
 * @param self -> The vector to use
 * @param item -> The item to add (usually byte sized like char*)
 * @param n -> The number with which to extend size
 */
void _vector_add_n_helper(
  void *dest, const void *src, size_t n, size_t elem_size
);
#define vector_add_n(self, item, n)                                \
  do {                                                             \
    if((item) != NULL) {                                           \
      _vector_maybegrow(self, n);                                  \
      _vector_add_n_helper(                                        \
        (self) + vector_size(self), (item), (n), sizeof((self)[0]) \
      );                                                           \
      _vector_get_header(self)->size += (n);                       \
    }                                                              \
  } while(0)

/**
 * @brief Adds a vector to the end of the vector
 * @param self -> The vector to use
 * @param item -> The vector to add
 */
#define vector_add_vector(self, item) \
  vector_add_n(self, item, vector_size(item))

/**
 * @brief Delete a multiple values from the vector
 * @param self -> The vector to use
 * @param index -> The index to start
 * @param n -> The number of elements to delete
 **/
#define vector_remove_n(self, index, number_of_elements)                 \
  (memmove(                                                              \
     &(self)[(index)],                                                   \
     &(self)[(index) + (number_of_elements)],                            \
     _vector_selfptr_size(self) *                                        \
       (_vector_get_header(self)->size - (number_of_elements) - (index)) \
   ),                                                                    \
   _vector_get_header(self)->size -= (number_of_elements))

/**
 * @brief Delete a specific vector value by index
 * @param self -> The vector to use
 * @param index -> The index to delete
 **/
#define vector_remove(self, index) vector_remove_n(self, index, 1)

/**
 * @brief Deletes the last element of the vector
 * @param self -> The vector to use
 **/
#define vector_remove_last(self) vector_remove((self), vector_size(self) - 1)

/**
 * @brief Finds the last element of the vector
 * @param self -> The vector to use
 */
#define vector_last(self) ((self)[_vector_get_header(self)->size - 1])

/**
 * @brief Checks if the vector is empty
 * @param self -> The vector to check
 * @return: true if the vector is empty, false otherwise
 */
#define vector_is_empty(self) (vector_size(self) == 0)

/**
 * @brief Get the total number of values inserted in the vector
 * @param self -> The vector to use
 * @return: The number of items in the vector
 **/
#define vector_size(self) ((self) ? (size_t)_vector_get_header(self)->size : 0)

/**
 * @brief Same as vector_size but returns a signed value
 * @param self -> The vector to use
 * @return: The number of items in the vector
 */
#define vector_size_signed(self) \
  ((self) ? (ptrdiff_t)_vector_get_header(self)->size : 0)

/**
 * @brief Gets the current total capacity of the vector
 * @param self -> The vector pointer
 * @return The capacity of the vector or 0 if the vector is NULL
 */
#define vector_capacity(self) \
  ((self) ? (size_t)_vector_get_header(self)->capacity : 0)

/**
 * @brief Same as vector_capacity but returns a signed value
 * @param self -> The vector pointer
 * @return The capacity of the vector or 0 if the vector is NULL
 */
#define vector_capacity_signed(self) \
  ((self) ? (ptrdiff_t)_vector_get_header(self)->capacity : 0)

/**
 * @brief Frees the memory of the vector
 * @param self -> The vector to free
 */
#define vector_free(self)                                                  \
  ((self)                                                                  \
     ? (*(void **)&(self) = vector_allocator(_vector_get_header(self), 0)) \
     : 0,                                                                  \
   (self) = NULL)

void *_vector_growf(void *self, size_t elemsize, size_t addlen, size_t min_cap);

#if PREPROCESSOR_C_VERSION >= 2011
  /**
   * @brief Creates a new vector and initializes it with the given arguments.
   * Using generic to have type-safe interaction for defined types of vectors.
   * We add a void* value as an extra argument to the variadics to allow for a
   * potential of a vector with 1 element.  In any case vector_new should be
   * typed and initialized properly by recognizing the first argument for the
   * generic choice.  Since its all macros it is possible to have any type even
   * if __VA_ARGS__ do not contain void*.
   * @param ... -> Initialization arguments
   * @return: The newly created vector
   */
  #define _vector_get_first_arg(first, ...) (first)
  #define _vector_new_dispatch(type, func, ...) \
    func(PREPROCESSOR_EXPANSIONS_NUMBER_OF_ELEMENTS(__VA_ARGS__), __VA_ARGS__)

  #define vector_new(...)                                \
    _vector_new_dispatch(                                \
      _vector_get_first_arg(__VA_ARGS__, (void *)0),     \
      _Generic(                                          \
        (_vector_get_first_arg(__VA_ARGS__, (void *)0)), \
        void *: _vector_voidptr_new,                     \
        char *: _vector_charptr_new,                     \
        const char *: _vector_charptr_new,               \
        int: _vector_int_new,                            \
        char: _vector_char_new,                          \
        long: _vector_long_new,                          \
        default: _vector_voidptr_new                     \
      ),                                                 \
      __VA_ARGS__                                        \
    )
#endif

#if PREPROCESSOR_C_VERSION >= 1999
  /**
   * @brief: Initializes a vector data structure
   * @param type -> The type for the initialization of the vector
   * @param name -> The name of the function to create
   * @return: The newly created vector
   */
  #define _vector_new(self, type, cast_type, argc)         \
    do {                                                   \
      va_list vars;                                        \
      va_start(vars, argc)                                 \
        ;                                                  \
        for(size_t i = 0; i < argc; i++) {                 \
          vector_add(self, (type)va_arg(vars, cast_type)); \
        }                                                  \
      va_end(vars);                                        \
    } while(0)

  #define vector_string_new(...)                                           \
    _vector_charptr_new(                                                   \
      PREPROCESSOR_EXPANSIONS_NUMBER_OF_ELEMENTS(__VA_ARGS__), __VA_ARGS__ \
    )
  #define vector_charptr_new(...)                                          \
    _vector_charptr_new(                                                   \
      PREPROCESSOR_EXPANSIONS_NUMBER_OF_ELEMENTS(__VA_ARGS__), __VA_ARGS__ \
    )
  #define vector_voidptr_new(...)                                          \
    _vector_voidptr_new(                                                   \
      PREPROCESSOR_EXPANSIONS_NUMBER_OF_ELEMENTS(__VA_ARGS__), __VA_ARGS__ \
    )
  #define vector_int_new(...)                                              \
    _vector_int_new(                                                       \
      PREPROCESSOR_EXPANSIONS_NUMBER_OF_ELEMENTS(__VA_ARGS__), __VA_ARGS__ \
    )
  #define vector_char_new(...)                                             \
    _vector_char_new(                                                      \
      PREPROCESSOR_EXPANSIONS_NUMBER_OF_ELEMENTS(__VA_ARGS__), __VA_ARGS__ \
    )
  #define vector_long_new(...)                                             \
    _vector_long_new(                                                      \
      PREPROCESSOR_EXPANSIONS_NUMBER_OF_ELEMENTS(__VA_ARGS__), __VA_ARGS__ \
    )
char *_vector_char_new(size_t argc, ...);
void **_vector_voidptr_new(size_t argc, ...);
char **_vector_charptr_new(size_t argc, ...);
int *_vector_int_new(size_t argc, ...);
long *_vector_long_new(size_t argc, ...);
#endif

/**
 * @brief Prints all elements of the vector
 * @param self -> The vector to print
 * @param format -> The format string to use
 */
#define vector_display(self, format)   \
  do {                                 \
    size_t i;                          \
    size_t vsize = vector_size(self);  \
    if(vsize > 0) {                    \
      printf("[");                     \
      for(i = 0; i < vsize - 1; i++) { \
        printf(format, self[i]);       \
        printf(", ");                  \
      }                                \
      printf(format, self[vsize - 1]); \
      printf("]\n");                   \
    }                                  \
  } while(0)

/**
 * @brief Get a memory duplicate of the passed vector
 * @param self -> The vector to use
 * @param dup -> The vector to duplicate to
 **/
#define vector_dup(self, dup)        \
  do {                               \
    size_t i;                        \
    size_t vlen = vector_size(self); \
    for(i = 0; i < vlen; i++) {      \
      vector_add((dup), self[i]);    \
    }                                \
  } while(0)

/**
 * @brief Maps all vector elements in iteration using a modifier function
 *pointer
 * @param self -> The vector to map
 * @param dup -> The new vector to map to
 * @param modifier -> The modifier function
 **/
#define vector_map(self, dup, modifier)       \
  do {                                        \
    size_t vlen = vector_size(self);          \
    if((void *)(self) == (void *)(dup)) {     \
      size_t i;                               \
      for(i = 0; i < vlen; i++) {             \
        (dup)[i] = modifier((self)[i]);       \
      }                                       \
    } else {                                  \
      size_t i;                               \
      for(i = 0; i < vlen; i++) {             \
        vector_add((dup), modifier(self[i])); \
      }                                       \
    }                                         \
  } while(0)

/**
 * @brief Filters all vector elements in iteration using a filter function
 * @param self -> The vector to filter
 * @param dup -> The new vector to store results
 * @param filter -> The filter function
 **/
#define vector_filter(self, dup, filter)       \
  do {                                         \
    size_t vlen = vector_size(self);           \
    if((void *)(self) == (void *)(dup)) {      \
      size_t i;                                \
      for(i = 0; i < vector_size(self); i++) { \
        if(filter(self[i])) {                  \
          vector_remove((dup), i);             \
          i--;                                 \
        }                                      \
      }                                        \
    } else {                                   \
      size_t i;                                \
      for(i = 0; i < vlen; i++) {              \
        if(!filter(self[i])) {                 \
          vector_add((dup), self[i]);          \
        }                                      \
      }                                        \
    }                                          \
  } while(0)

/**
 * @brief Selects vector elements according to a selector lambda
 * @param self -> The vector to select from
 * @param dup -> The new vector to store results
 * @param selector -> The selector function
 */
#define vector_select(self, dup, selector) vector_filter(self, dup, !selector)

/**
 * @brief Recudes all vector elements into a void* result using a foldl function
 * @param self -> The vector to reduce
 * @param fold -> The folding function to use
 * @param res -> The result pointer
 **/
#define vector_reduce(self, fold, res)          \
  do {                                          \
    if(self != NULL && vector_size(self) > 0) { \
      size_t i;                                 \
      size_t vlen = vector_size(self);          \
      *res        = self[0];                    \
      for(i = 1; i < vlen; i++) {               \
        *res = fold(*res, self[i]);             \
      }                                         \
    }                                           \
  } while(0)

/** @brief Pushes an element to the end of the vector (alias for vector_add) */
#define vector_push vector_add

/**
 * @brief Pops from the end of the vector
 * @param self -> vector
 * @return The last element of the vector
 */
#define vector_pop(self)                                            \
  (vector_size(self) > 0 ? (_vector_get_header(self)->size--,       \
                            (self)[_vector_get_header(self)->size]) \
                         : 0)

/**
 * @brief Peeks at the last element of the vector without removing it
 * @param self -> vector
 * @return The last element of the vector
 */
#define vector_peek(self) (self)[_vector_get_header(self)->size - 1]

#endif
