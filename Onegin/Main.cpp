#include "asserts.h"
#include "structers.h"
#include "input.h"
#include "logger.h"


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
    printf("%s\n", file_buff);

    size_t strings_num = calculate_num_of_strings(file_buff);
    string_data* arr = input_parsing(file_buff, strings_num);
    LOGGER_DEBUG("Parsing ended");

    for(size_t i = 0; i < strings_num; i++) {
    	free(arr[i].str);
    	LOGGER_WARNING("Освобождаю %d ячейку памяти", i);
    }
    free(arr);
    free(file_buff);

}