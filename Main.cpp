#include "asserts.h"
#include "structers.h"
#include "input.h"
#include "logger.h"
#include "output.h"
#include "sorting.h"
#include "error_handling.h"

#include <stdio.h>
#include <stdlib.h>

error_type file_processing(const char* file_name);


const int ALPHABET_SIZE = 33;
const int FILE_MAX_LEN = 100;
int main() {
    error_type error = NO_ERROR;
    logger_initialize_stream(NULL);
    LOGGER_DEBUG("Main started");

    printf("Введите имя файла:\n");
    char file_name[100] = {};
    scanf("%99s", file_name); //TODO: ЗАменить на fgets

    error = file_processing(file_name); //TODO: Добавить argv
    logger_close();
    return error;
}

error_type file_processing(const char* file_name) {
    error_type error = NO_ERROR;

    FILE* curr_file = fopen(file_name, "r");
    CHECK_ERROR(curr_file != nullptr, OPEN_FILE_ERROR, 
        return OPEN_FILE_ERROR;
    );
    LOGGER_DEBUG("File %s opened succesfully", file_name);

    char* file_buff = 0;
    error = read_file_into_buffer(curr_file, &file_buff);
    CHECK_ERROR(file_buff != nullptr, READ_FILE_ERROR, 
        return READ_FILE_ERROR;
    );      
    fclose(curr_file);
    LOGGER_DEBUG("File is readed correctly");

    //Если некорректный файл, то дать еще шанс на ввод.

    size_t strings_num = 0;
    string_data** arr = {};
    string_data* struct_container = {};
    error = parse_to_string_data(file_buff, &strings_num, &arr, &struct_container); 
    if (error != NO_ERROR) return error;
    LOGGER_DEBUG("Parsing ended. Num of strings = %u", strings_num);

    FILE* output_file = fopen("Onegin_output", "w");
    CHECK_ERROR(output_file != nullptr, OPEN_FILE_ERROR,
        return OPEN_FILE_ERROR;
    );

    bubble_sort_for_string_data(arr, strings_num, sizeof(arr[0]));
	fprintf(output_file, "\n______________________________FORWARD CUSTOM SORTED ONEGIN____________________________\n\n");
    print_arr(arr, strings_num, output_file);

    qsort_for_string_data(arr, strings_num, sizeof(arr[0]));
    fprintf(output_file, "\n_________________________________FORWARD QSORT ONEGIN_________________________________\n\n");
	print_arr(arr, strings_num, output_file);

	qsort_from_back_for_string_data(arr, strings_num, sizeof(arr[0]));
    fprintf(output_file, "\n________________________________QSORT FROM BACK ONEGIN________________________________\n\n");
	print_arr(arr, strings_num, output_file);

	print_original(output_file, strings_num, &file_buff);
    fclose(output_file);

    // destruct_string_data
    free(struct_container);
    LOGGER_DEBUG("String_data cleared");

    free(arr);
    arr = NULL;     //Доп. уязвимость спсоб обращенич к массиву
    LOGGER_DEBUG("Arr cleared");

    free(file_buff);
    LOGGER_DEBUG("Buffer cleared");
    LOGGER_INFO("Programm ended");
    return error;
}


/*
void file_processing_bred(const char* file_name) {
    char* file_buff = read_file_into_buffer(file_name);
    HARD_ASSERT(file_buff != nullptr, "File is missing");
    LOGGER_DEBUG("File is readed correctly");

    size_t strings_num[ALPHABET_SIZE] = {};
    arr_of_ptr_to_str* arr = input_parsing_bred(file_buff, &strings_num);
    LOGGER_DEBUG("Parsing ended. Num of strings = %u", strings_num);


    sort_and_print(arr, file_buff, strings_num, sizeof(string_data*));

    for(size_t i = 0; i < strings_num; i++) {
        free(arr[i]);
    }
    free(arr);
    LOGGER_DEBUG("Arr cleared");
    free(file_buff);
    LOGGER_DEBUG("Buffer cleared");
    LOGGER_INFO("Programm ended");
}*/

