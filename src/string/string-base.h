#ifndef __EDSA_STRING_BASE_H_
#define __EDSA_STRING_BASE_H_

#include "../boolean/boolean.h"
#include "../vector/vector.h"

#include <stddef.h> /* size_t */

/**
 * @brief Makes a string allocator-aware
 */
#define string_set_allocator vector_set_allocator

/**
 * @brief Create an string
 * @param initial_string -> The initial string to set
 * @return The string
 **/
char *string_new(const char *initial_string);

/**
 * @brief Adds a string with a cutoff of a given length
 * @param self -> The string to use
 * @param other -> The string to add
 * @param len -> The length of characters to add
 */
#define string_addn(self, other, len)     \
  do {                                    \
    if(self == NULL && other != NULL) {   \
      vector_initialize(self);            \
    }                                     \
    vector_add_n(self, other, (len) + 1); \
    if(other != NULL) {                   \
      string_ignore_last(self, 1);        \
    }                                     \
  } while(0)

/**
 * @brief Adds a string into self
 * @param self -> The string to use
 * @param other -> The string to add
 */
#define string_add(self, other) string_add_(&self, other)
void string_add_(char **self, const char *other);

/**
 * @brief Adds an initialized string into self
 * @param self -> The string to use
 * @param other -> The string to add
 */
#define string_addi(self, other) string_addi_(&self, other)
void string_addi_(char **self, const char *other);

/**
 * @brief Adds a formatted string into the builder
 * @param self -> A pointer to the string to add to
 * @param f -> The format string to use
 * @param ... -> The rest of the arguments
 */
void string_addf(char **self, const char *f, ...);

/**
 * @brief The length of the string contained in the builder
 * @param self -> The string to use
 * @return The current length of the string
 **/
size_t string_size(const char *self);

/**
 * @brief Signed length
 * @param self -> The string to use
 * @return The current length of the string as a signed integer
 */
size_t string_size_signed(char *self);

/**
 * @brief Remove data from the end of the builder
 * @param self -> The string to use
 * @param len -> The new length , anything after this length is removed
 **/
void string_shorten(char *self, size_t len);

/**
 * @brief Remove data from the beginning of the builder
 * @param self -> The string to use
 * @param len -> The length to remove
 **/
void string_skip_first(char *self, size_t len);

/**
 * @brief Ignores the last `len` characters of the string
 * @param self -> The string to use
 * @param len -> The length to ignore
 **/
void string_ignore_last(char *self, size_t len);

/**
 * @brief Clear the builder
 * @param self -> The string to use
 **/
void string_delete(char *self);

/**
 * @brief Removes a character at a given position
 * @param self -> The string to use
 * @param pos -> The position from which to remove
 */
void string_remove(char *self, size_t pos);

/**
 * @brief Checks if the char pointers of the two strings passed are the same
 * @param self -> The first string
 * @param other -> The second string
 * @return A boolean signaling if the strings are equal
 **/
bool string_equals(char *self, const char *other);

/**
 * @brief Frees the memory of the string
 * @param self -> The string to free
 */
#define string_free(self) string_free_(&self)
void string_free_(char **self);

#endif
