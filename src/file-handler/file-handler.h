#ifndef __EDSA_FILE_HANDLER_H_
#define __EDSA_FILE_HANDLER_H_

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

#endif
