#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED

#include "structers.h"

size_t print_arr(/*const*/string_data** arr, size_t strings_num, FILE* output_file);
void sort_and_print(string_data** arr, char* buff, size_t strings_num, size_t elem_size);

#endif

/*

text_by_lines: print_text, read_text, sort_text(enum)
						            	  |
			------------------------------+
			|
			V
my_sort: bubble_sort, qsort, 

*/