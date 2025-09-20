#include "structers.h"
#include "asserts.h"
#include "sorting.h"
#include "logger.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
static const int MAXSIZE = 512;

typedef int(*function_ptr)(const void*, const void*);

void swap(void* obj1, void* obj2, size_t size) {
	HARD_ASSERT(obj1 != nullptr, "Obj1 is nullptr");
	HARD_ASSERT(obj2 != nullptr, "Obj2 is nullptr");
	//Стоит ли делать изначальное объявление temp[512]
	void* temp = calloc(1, size);
	HARD_ASSERT(temp != nullptr, "Temp is nullptr");
	memcpy(temp, obj1, size);
	memcpy(obj1, obj2, size);
	memcpy(obj2, temp, size);
	free(temp);

	// 1000% переписать

	// stdint.h <-> stdtypes.h
	// uint64_t, uint32_t, uint16_t, uint8_t
	// 64 byte -> 8x8
	// 68 byte -> 8x8 + 1x4
	// 71 byte -> 8x8 + 1x4 + 1x2 + 1x1
	// size = 1000111 = 1 + 2 + 4 + 64
	// x1 = size & 1

	// x = (x / 2) * 2 + 1 // int
	// x = x | 1           // 

	// x2 = size & 2
	// x4 = size & 4
	// x8 = size >> 3

	// K&R switch case (возможно быстрее) проваливающийся
}

int cmp_for_string_data(const void* a, const void* b) {
	HARD_ASSERT(a != nullptr, "A is nullptr");
	HARD_ASSERT(b != nullptr, "B is nullptr");
	string_data* str_data1 = *((string_data**)a);
	string_data* str_data2 = *((string_data**)b);

	size_t len1 = str_data1->len;
	size_t len2 = str_data2->len;
	char* str1 = str_data1->str;
	char* str2 = str_data2->str;

	size_t str1_index = 0;
	size_t str2_index = 0;

	
	while(str1_index < len1 && !isalpha(str1[str1_index])) {
		str1_index++;
	}
	while(str2_index < len2 && !isalpha(str2[str2_index])) {
		str2_index++;
	}


	while(str1_index < len1 && str2_index < len2) {
		if(tolower(str1[str1_index]) > tolower(str2[str2_index])) {
			return 1;
		} else if(tolower(str1[str1_index]) < tolower(str2[str2_index])) { //TODO: Можно просто вычесть
			return -1;
		}
		str1_index++;
		str2_index++;
		while(str1_index < len1 && !isalpha(str1[str1_index])) {
			str1_index++;
		}
		while(str2_index < len2 && !isalpha(str2[str2_index])) {
			str2_index++;
		}
	}

	if(str1_index == len1 && str2_index == len2) return 0;
	if(str1_index == len1) return -1;
	if(str2_index == len2) return 1;
	return 0;
}

int reverse_cmp_for_string_data(const void* a, const void* b) {
	HARD_ASSERT(a != nullptr, "A is nullptr");
	HARD_ASSERT(b != nullptr, "B is nullptr");
	string_data* str_data1 = *((string_data**)a);
	string_data* str_data2 = *((string_data**)b);

	size_t len1 = str_data1->len;
	size_t len2 = str_data2->len;
	char* str1 = str_data1->str;
	char* str2 = str_data2->str;

	size_t str1_index = 0;
	size_t str2_index = 0;

	
	while(str1_index < len1 && !isalpha(str1[len1 - str1_index - 1])) {
		str1_index++;
	}
	while(str2_index < len2 && !isalpha(str2[len2 - str2_index - 1])) {
		str2_index++;
	}


	while(str1_index < len1 && str2_index < len2) {
		if(tolower(str1[len1 - str1_index - 1]) > tolower(str2[len2 - str2_index - 1])) {
			return 1;
		} else if(tolower(str1[len1 - str1_index - 1]) < tolower(str2[len2 - str2_index - 1])) {
			return -1;
		}
		str1_index++;
		str2_index++;
		while(str1_index < len1 && !isalpha(str1[len1 - str1_index - 1])) {
			str1_index++;
		}
		while(str2_index < len2 && !isalpha(str2[len2 - str2_index - 1])) {
			str2_index++;
		}
	}

	if(str1_index == len1 && str2_index == len2) return 0;
	if(str1_index == len1) return -1;
	if(str2_index == len2) return 1;
	return 0;
}


void bubble_sort_for_string_data(void* target_arr, 
								 size_t elements_num, size_t base) {
	bubble_sort(target_arr, elements_num, base, &cmp_for_string_data);
}

void qsort_for_string_data(void* target_arr, 
						   size_t elements_num, size_t base) {
	LOGGER_DEBUG("Qsort started");
	qsort(target_arr, elements_num, base, &cmp_for_string_data);
}

void qsort_from_back_for_string_data(void* target_arr, 
						   size_t elements_num, size_t base) {
	LOGGER_DEBUG("Qsort from back started");
	qsort(target_arr, elements_num, base, &reverse_cmp_for_string_data);
}
void bubble_sort(void* target_arr, 
				 size_t elements_num, size_t base, 
				 function_ptr cmp) {
	LOGGER_DEBUG("Bubble_sort started");
	HARD_ASSERT(target_arr != nullptr, "target_arr is nullptr");
	for(size_t i = 0; i < elements_num; i++) {
		for(size_t j = 0; j < elements_num - i - 1; j++) {
			void* curr = (char*)target_arr + j * base;
			void* next = (char*)target_arr + (j + 1) * base;
			if ((*cmp)(curr, next) > 0) {
				swap(curr, next, base);
			}
		}
	}
}

