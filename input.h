#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED
#include "structers.h"
#include "error_handling.h"

error_type read_file_into_buffer(FILE* file_name, char** buffer_return);
//ssize_t getline_from_buffer(char** lineptr, size_t* size_of_buffer, char* buff);
error_type parse_to_string_data(char* buffer, size_t* strings_num_return, string_data*** arr_return, string_data** struct_container);
size_t count_string_and_prepare_buffer(char* buff);
size_t get_string_from_buffer(char** string_ptr, char** buff);
#endif