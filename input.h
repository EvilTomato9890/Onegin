#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED
#include "structers.h"

char* read_file_into_buffer(const char *file_name);

ssize_t getline_from_buffer(char **lineptr, size_t *size_of_buffer, char* buff);

string_data** input_parsing(char* buffer, size_t* strings_num_return);
#endif