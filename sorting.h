#ifndef SORTING_H_INCLUDED
#define SORTING_H_INCLUDED

typedef int(*function_ptr)(const void*, const void*);


int cmp_for_string_data(const void* a, const void* b);


void swap(void* obj1, void* obj2, size_t size);

void bubble_sort_for_int(void* target_arr, 
				  size_t elements_num, size_t element_size);

void bubble_sort(void* target_arr, 
				  size_t elements_num, size_t element_size, 
				  function_ptr cmp);

void bubble_sort_for_string_data(void* target_arr, 
								 size_t elements_num, size_t base);

void qsort_for_string_data(void* target_arr, 
						   size_t elements_num, size_t base);

void qsort_from_back_for_string_data(void* target_arr, 
						   size_t elements_num, size_t base);
#endif