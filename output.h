#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED

#include "structers.h"
size_t print_arr(string_data** arr, size_t strings_num, FILE* output_file);
void sort_and_print(string_data** arr, char* buff, size_t strings_num, size_t elem_size);

#endif