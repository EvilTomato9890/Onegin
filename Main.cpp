#include "asserts.h"
#include "structers.h"
#include "input.h"
#include "logger.h"
#include "output.h"

#include <stdio.h>
#include <stdlib.h>


int main() {
	logger_initialize_stream(NULL);
	LOGGER_DEBUG("Main started");

	printf("Введите имя файла:\n");
    char file_name[100] = {};
    scanf("%99s", file_name); 
    
    char* file_buff = read_file_into_buffer(file_name);
    HARD_ASSERT(file_buff != nullptr, "File is missing");
    LOGGER_DEBUG("File is readed correctly");

    size_t strings_num = 0;
    string_data** arr = input_parsing(file_buff, &strings_num);
    LOGGER_DEBUG("Parsing ended. Num of strings = %u", strings_num);


    sort_and_print(arr, strings_num, sizeof(string_data*));

    for(size_t i = 0; i < strings_num; i++) {
        free(arr[i]);
    }
    free(arr);
    LOGGER_DEBUG("Arr cleared");
    free(file_buff);
    LOGGER_DEBUG("Buffer cleared");
    LOGGER_INFO("Programm ended");

}
