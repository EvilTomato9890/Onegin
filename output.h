#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED

#include "structers.h"

size_t print_arr(const string_data *const *const arr, const size_t strings_num, FILE* output_file);
size_t print_original(FILE* output_file, const size_t strings_num, char** buff);
#endif

/*

text_by_lines: print_text, read_text, sort_text(enum)
						            	  |
			------------------------------+
			|
			V
my_sort: bubble_sort, qsort, 

*/