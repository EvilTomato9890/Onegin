#include "structers.h"
#include "input.h"
#include "asserts.h"
#include "logger.h"
#include "error_handling.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

const size_t STANDART_CALLOC_SIZE = 120;
const float GROW_FACTOR = 2;
const int ALPHABET_SIZE = 33;
/**
 * @brief Функция, считывающая в буффер файл по переданному названию
 * @param [in] file_name Название файла, который требуется считать в буффер.
 * 
 * Функция считает длинну файла, выделяет буффер соотвествующего размера и записывает в него весь файл.
 * 
 * @return Возвращает считанный файл в формате строки
*/

error_type get_file_size(FILE* curr_file, size_t* length) {
    LOGGER_DEBUG("get_file_size started");
    HARD_ASSERT(curr_file != nullptr, "File not found");
    HARD_ASSERT(length != nullptr, "Return ptr is nullptr");

    int fseek_error = fseek(curr_file, 0, SEEK_END);
    CHECK_ERROR(fseek_error == 0,  
        LOGGER_ERROR("Fseek droped"); \
        return PROCESSING_FILE_ERROR;
    );
    *length = ftell(curr_file);
    fseek_error = fseek(curr_file, 0, SEEK_SET);
    CHECK_ERROR(fseek_error == 0,
        LOGGER_ERROR("Fseek droped");
        return PROCESSING_FILE_ERROR;
    );
    return NO_ERROR;
}

// get_error(status) return const char* -> print 
error_type read_file_into_buffer(FILE* curr_file, char** buffer_return) { 
    LOGGER_INFO("Reading file started");
    HARD_ASSERT(curr_file != nullptr, "File not found");
    HARD_ASSERT(buffer_return != nullptr, "Return ptr is nullptr");
    error_type error = NO_ERROR;

    size_t length = 0;
    error = get_file_size(curr_file, &length);
    CHECK_ERROR(error == NO_ERROR, 
        return PROCESSING_FILE_ERROR;
    );
    LOGGER_INFO("Filesize - %llu", length);
    // Быстрее stat

    char* buffer = (char*)calloc(length + 1, sizeof(char));
    CHECK_ERROR(buffer != nullptr, 
        LOGGER_ERROR("Memory allocation failed");
        return MEMORY_ALLOC_ERROR;
    );
    LOGGER_DEBUG("Memory allocation succes, taken %ld bytes", (long)((length + 1) * sizeof(char)));

    buffer[length] = '\0';
    size_t symbols = fread(buffer, sizeof(buffer[0]), length, curr_file);
    CHECK_ERROR(length > symbols, 
        LOGGER_ERROR("Failed to read file");
        free(buffer);
        return READ_FILE_ERROR;
    );

    LOGGER_INFO("Buffer returned");
    *buffer_return = buffer;
    return error;
}

size_t count_string_and_prepare_buffer(char* buff) {
    LOGGER_DEBUG("count_string_and_prepare_buffer started");
    HARD_ASSERT(buff != nullptr, "Buff is nullptr");
    
    size_t strings_num = 0;
    size_t index = 0;
    size_t buff_len = 0;

    while(buff[index] != '\0') {
        if(buff[index] == '\n') {
            strings_num++;
            buff[index] = '\0';
        }
        index++;
        buff_len++;
    }

    if (buff_len <= 1) LOGGER_WARNING("Very small size of buffer");
    return strings_num;
}
/*
size_t* count_string_and_prepare_buffer_bred(char* buff) {
    LOGGER_DEBUG("Prepare_buffer started");
    HARD_ASSERT(buff != nullptr, "Buff is nullptr");
    
    size_t strings_num = 0;
    size_t buff_len = strlen(buff);
    if (buff_len <= 1) LOGGER_WARNING("Very small size of buffer");

    for(size_t i = 0; i < buff_len; i++) {
        if(buff[i] == '\n') {
            strings_num++;
            buff[i] = '\0';
        }
    }
    return strings_num;
}
*/

size_t get_string_from_buffer(char** string_ptr, char** buff) {
    HARD_ASSERT(buff != nullptr, "Buff is nullptr");
    HARD_ASSERT(string_ptr != nullptr, "Buff is nullptr");

    *string_ptr = *buff;
    *buff = strchr(*buff, '\0') + 1;
    return *buff - *string_ptr;
}

error_type parse_to_string_data(char* buff, size_t* strings_num_return, string_data*** arr_return, string_data** struct_container) {
    LOGGER_DEBUG("input_parsing started");
    if (buff == nullptr) LOGGER_WARNING("Buff is nullptr");
    
    error_type error = NO_ERROR;

    size_t strings_num = count_string_and_prepare_buffer(buff);
    string_data** strings = (string_data**)calloc(strings_num, sizeof(string_data*));
    string_data* arr_struct_addreses = (string_data*)calloc(strings_num, sizeof(string_data));
    CHECK_ERROR(strings != nullptr && arr_struct_addreses != nullptr, 
        LOGGER_ERROR("Memory allocation failed");
        free(arr_struct_addreses);
        free(strings);
        return MEMORY_ALLOC_ERROR;
    );

    for(size_t i = 0; i < strings_num; i++) {
        strings[i] = arr_struct_addreses + i;
        strings[i]->len = get_string_from_buffer(&(strings[i]->str), &buff);    
    }

    *struct_container = arr_struct_addreses;
    *strings_num_return = strings_num;
    *arr_return = strings;
    return error;
}
/*
arr_of_ptr_to_str* input_parsing_bred(char* buff, size_t** strings_num_arr) {
    LOGGER_DEBUG("input_parsing started");
    if (buff == nullptr) LOGGER_WARNING("Buff is nullptr");
    
    size_t* strings_num = count_string_and_prepare_buffer(buff);

    arr_of_ptr_to_str arr_of_arr_of_strings[ALPHABET_SIZE] = {};
    for(size_t i = 0; i < ALPHABET_SIZE; i++) {
        arr_of_arr_of_strings[i].arr = (string_data**)calloc(1, sizeof(string_data*))
    }    
}
*/
/*
ssize_t getline_from_buffer(char** lineptr, size_t* size_of_buffer, char* buff) { 
    LOGGER_DEBUG("my_getline started");
    HARD_ASSERT(lineptr != nullptr, "Pointer to string is nullptr");
    HARD_ASSERT(buff != nullptr, "Buff is nullptr");
    HARD_ASSERT(size_of_buffer != nullptr, "size_of_buffer is nullptr");

    int ch = 0;
    size_t curr_size = *size_of_buffer;
    size_t num_chars = 0;
    bool is_malloc_used = false;

    if (*lineptr == nullptr) {
        curr_size = STANDART_CALLOC_SIZE;
        LOGGER_DEBUG("Memory allocation started, trying to malloc %ld bytes", curr_size);
        *lineptr = (char*)calloc(curr_size, sizeof(**lineptr));
        if (*lineptr == nullptr) return -1;
        is_malloc_used = true;
        *size_of_buffer = curr_size;
    }

    char *ptr = *lineptr; //TODO: Изменить нащвание

    while (*(buff++) != '\0') {
        if (num_chars + 1 >= curr_size) { //TODO: Вынести в отдельную функцию
            curr_size *= GROW_FACTOR;
            LOGGER_DEBUG("Memory reallocation started, trying to realloc %ld bytes", curr_size);
            char *new_ptr = (char *)realloc(*lineptr, curr_size); //TODO: Recalloc realize
            if (new_ptr == nullptr) {
                if (is_malloc_used) free(*lineptr);
                return -1;
            }
            *lineptr = new_ptr;
            ptr = *lineptr + num_chars; 
            *size_of_buffer = curr_size;
        }

        *ptr++ = (char)ch;
        num_chars++;

        if (ch == '\n') break; //Для этого
    }

    if (num_chars == 0 && ch == '\0') {
        if (is_malloc_used) free(*lineptr);
        return -1;
    }

    *(--ptr) = '\0'; //С помощью новой функции сделать проверку на выход за границы массивы
    return num_chars;
}
*/