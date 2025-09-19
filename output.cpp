#include <stdio.h>
#include "structers.h"
#include "logger.h"
#include "asserts.h"
#include "output.h"
#include "sorting.h"


size_t print_arr(string_data** arr, size_t strings_num, FILE* output_file) {
	LOGGER_DEBUG("print_arr started");
	HARD_ASSERT(arr != nullptr, "Arr is nullptr");
	HARD_ASSERT(output_file != nullptr, "output_file is nullptr");
	size_t symbols_cnt = 0;
	for(size_t i = 0; i < strings_num; i++) {
		if(arr[i]->len != 1) {
			symbols_cnt += fprintf(output_file, "%s\n", arr[i]->str);
		}
	}
	return symbols_cnt;
}

void sort_and_print(string_data** arr, char* buff, size_t strings_num, size_t elem_size) {
	LOGGER_DEBUG("sort_and_print started");
	if(strings_num <= 2) LOGGER_WARNING("Small size of array: %lu", strings_num);

	if(arr == nullptr) {
		LOGGER_WARNING("Arr is nullptr");
		return;
	}

	FILE* output_file = fopen("Onegin_output", "w");
	HARD_ASSERT(output_file != nullptr, "File Onegin_output not found");

	bubble_sort_for_string_data(arr, strings_num, elem_size);
	fprintf(output_file, "\n______________________________FORWARD CUSTOM SORTED ONEGIN____________________________\n\n");
    print_arr(arr, strings_num, output_file);

    qsort_for_string_data(arr, strings_num, elem_size);
    fprintf(output_file, "\n_________________________________FORWARD QSORT ONEGIN_________________________________\n\n");
	print_arr(arr, strings_num, output_file);

	qsort_from_back_for_string_data(arr, strings_num, elem_size);
    fprintf(output_file, "\n________________________________QSORT FROM BACK ONEGIN________________________________\n\n");
	print_arr(arr, strings_num, output_file);

	fprintf(output_file, "\n______________________________________NORMAL ONEGIN___________________________________\n\n");
	for(size_t i = 0; i < strings_num; i++) {
		size_t symbols = fprintf(output_file, "%s\n", buff);
		buff += symbols;
	}
    fclose(output_file);
}