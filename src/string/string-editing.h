#ifndef __EDSA_STRING_EDITING_H_
#define __EDSA_STRING_EDITING_H_

#include <stddef.h> /* ptrdiff_t */

/**
 * @brief Splits a string to a spesific delimeter
 * @param self -> The string to split
 * @param delimeter -> The char delimeter
 * @return A vector with the string tokens
 **/
char **string_split(char *self, const char delimeter);

/**
 * @brief Get a substring of our current string without modifying the original
 * @param self -> The string builder we are using
 * @param from_position -> The point where we start our substring
 * @param to_position -> The point where we end our substring
 * @return A substring of a copy of the original string
 **/
char *
string_substring(char *self, ptrdiff_t from_position, ptrdiff_t to_position);

/**
 * @brief Removes all instances of `_` underscores
 * @param self -> The string to use
 */
char *string_remove_underscores(char *self);

#endif
