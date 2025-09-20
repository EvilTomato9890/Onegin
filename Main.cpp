#include "asserts.h"
#include "structers.h"
#include "input.h"
#include "logger.h"
#include "output.h"

#include <stdio.h>
#include <stdlib.h>

void file_processing(const char* file_name);


const int ALPHABET_SIZE = 33;

int main() {
    logger_initialize_stream(NULL);
    LOGGER_DEBUG("Main started");

    printf("Введите имя файла:\n");
    char file_name[100] = {};
    scanf("%99s", file_name); //TODO: ЗАменить на fgets

    file_processing(file_name); //TODO: Добавить argv
    logger_close();
}

void file_processing(const char* file_name) {
    char* file_buff = read_file_into_buffer(file_name);
    HARD_ASSERT(file_buff != nullptr, "File is missing"); // он отключится!!! todo TODO ToDo tOdO
    LOGGER_DEBUG("File is readed correctly");
    //Если некорректный файл, то дать еще шанс на ввод.
    size_t strings_num = 0;
    string_data** arr = input_parsing(file_buff, &strings_num); //Parse to string data 
        // init_string_data
    LOGGER_DEBUG("Parsing ended. Num of strings = %u", strings_num);

    sort_and_print(arr, file_buff, strings_num, sizeof(string_data*));

    // destruct_string_data
    for(size_t i = 0; i < strings_num; i++) {
        free(arr[i]);
    }
    free(arr);
    arr = NULL; //Доп. уязвимость спсоб обращенич к массиву
    LOGGER_DEBUG("Arr cleared");
    free(file_buff);
    LOGGER_DEBUG("Buffer cleared");
    LOGGER_INFO("Programm ended");
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

