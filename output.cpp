#include <stdio.h>
#include "structers.h"
#include "logger.h"
#include "asserts.h"
#include "output.h"
#include "sorting.h"
void sort_and_print(string_data** arr, size_t strings_num, size_t elem_size) {
	FILE* temp = fopen("Onegin_output", "w");
	fclose(temp);

	FILE* output_file = fopen("Onegin_output", "a");



	fprintf(output_file, "\n______________________________________NORMAL ONEGIN___________________________________\n\n");
	for(size_t i = 0; i < strings_num; i++) {
		fprintf(output_file, "%s\n", arr[i]->str);
	}

	bubble_sort_for_string_data(arr, strings_num, elem_size);
	fprintf(output_file, "\n______________________________FORWARD CUSTOM SORTED ONEGIN____________________________\n\n");
    for(size_t i = 0; i < strings_num; i++) {
    	if(arr[i]->len != 1) {
			fprintf(output_file, "%s\n", arr[i]->str);
		}
	}

    qsort_for_string_data(arr, strings_num, elem_size);
    fprintf(output_file, "\n_________________________________FORWARD QSORT ONEGIN_________________________________\n\n");
	for(size_t i = 0; i < strings_num; i++) {
		if(arr[i]->len != 1) {
			fprintf(output_file, "%s\n", arr[i]->str);
		}
	}

	qsort_from_back_for_string_data(arr, strings_num, elem_size);
    fprintf(output_file, "\n________________________________QSORT FROM BACK ONEGIN_________________________________\n\n");
	for(size_t i = 0; i < strings_num; i++) {
		if(arr[i]->len != 1) {
			fprintf(output_file, "%s\n", arr[i]->str);
		}
	}
    fclose(output_file);
}