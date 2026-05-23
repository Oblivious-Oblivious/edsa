#ifndef __EDSA_FILE_HANDLER_H_
#define __EDSA_FILE_HANDLER_H_

#include "../boolean/boolean.h"
#include "../string/string.h"

#include <stdio.h> /* FILE */

/**
 * @brief File handler for making file read operations more intuitive
 * @param fd -> The current file descriptor
 * @param filepath -> The name of the file to read from
 */
typedef struct EdsaFileHandler {
  FILE *fd;
  const char *filepath;
} EdsaFileHandler;

/**
 * @brief Initializes a file_handler
 * @param self -> The file_handler to initialize
 */
void file_handler_init(EdsaFileHandler *self);

/**
 * @brief Open a file in read mode
 * @param name -> The path to open
 * @param mode -> The mode to open the file in
 * @return a boolean signaling if the opening was successful
 */
bool file_handler_open(
  EdsaFileHandler *self, const char *name, const char *mode
);

/**
 * @brief Reads a file into a string
 * @param filepath -> The path to the file to read
 * @return a string containing the file contents
 */
char *file_handler_read(const char *filepath);

/**
 * @brief Write a string in the file
 * @param filename -> The name of the file to write to
 * @param str -> The string to write
 */
void file_handler_write(const char *filename, const char *str);

/**
 * @brief Writes a line in the file (with `\n`)
 * @param filename -> The name of the file to write to
 * @param line -> The line to write
 */
void file_handler_write_line(const char *filename, const char *line);

/**
 * @brief Attempts to close the buffers to avoid memory overflows
 * @param self -> The file_handler to close
 * @return a boolean signaling if closing was successful
 */
void file_handler_close(EdsaFileHandler *self);

/**
 * @brief Deinitializes a file_handler
 * @param self -> The file_handler to deinit
 */
void file_handler_deinit(EdsaFileHandler *self);

#endif
