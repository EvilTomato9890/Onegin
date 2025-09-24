#include <stdio.h>
#include "structers.h"
#include "logger.h"
#include "asserts.h"
#include "output.h"
#include "sorting.h"


size_t print_arr(const string_data *const *const arr, const size_t strings_num, FILE* output_file) {
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

size_t print_original(FILE* output_file, const size_t strings_num, char** buff) {
	LOGGER_DEBUG("print_original started");
	HARD_ASSERT(output_file != nullptr, "Output_file is nullptr");
	HARD_ASSERT(buff != nullptr, "Buff is nullptr");
	HARD_ASSERT(*buff != nullptr, "Output_file is nullptr");

	char* temp_buff = *buff;
	fprintf(output_file, "\n______________________________________NORMAL ONEGIN___________________________________\n\n");
	for(size_t i = 0; i < strings_num; i++) {
		size_t symbols = fprintf(output_file, "%s\n", *buff);
		*buff += symbols;
	}
	size_t symbols_cnt = *buff - temp_buff;
	*buff = temp_buff;
	return symbols_cnt;
}