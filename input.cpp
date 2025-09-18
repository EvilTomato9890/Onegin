#include "structers.h"
#include "input.h"
#include "asserts.h"
#include "logger.h"


#include <stdio.h>
#include <math.h>
#include <string.h>

const size_t STANDART_CALLOC_SIZE = 120;
const float GROW_FACTOR = 2;
 
/**
 * @brief Функция, подсчитывающая число строк в файле.
 * @param [in] curr_file Файл, представленный в виде массива символов.
 * 
 * Функция проходиться по файлу и подсчитывает количество символов '\\n', обозначающих конец строки,
 * тем самым подсчитывая количество самих строк в файле.
 * @return Возвращает количество строк в файле.
*/
int calculate_num_of_strings(const char* curr_file) { 
    LOGGER_INFO("Calculating num of strings started");
    HARD_ASSERT(curr_file != nullptr, "File not found");

    size_t num_of_strings = 0;
    size_t file_len = (int)strlen(curr_file);
    for (size_t i = 0; i < file_len; i++) {
        if (curr_file[i] == '\n') {
            num_of_strings++;
        }
    }
    LOGGER_INFO("Calculating num of strings ended");
    return num_of_strings;
}

/**
 * @brief Функция, считывающая в буффер файл по переданному названию
 * @param [in] file_name Название файла, который требуется считать в буффер.
 * 
 * Функция считает длинну файла, выделяет буффер соотвествующего размера и записывает в него весь файл.
 * 
 * @return Возвращает считанный файл в формате строки
*/
char* read_file_into_buffer(char *file_name) { 
    LOGGER_INFO("Reading file started");
    FILE *curr_file = fopen(file_name, "r");
    HARD_ASSERT(curr_file != nullptr, "File not found");

    char *buffer = 0;
    fseek (curr_file, 0, SEEK_END);
    long int length = ftell(curr_file);
    fseek (curr_file, 0, SEEK_SET);

    LOGGER_DEBUG("Memory allocation started");
    buffer = (char*)calloc(length + 1, sizeof(*file_name)); 
    if(buffer == nullptr) {
        LOGGER_ERROR("Memory allocation failed");
        HARD_ASSERT(false, "Memory allocation failed");
    }
    LOGGER_DEBUG("Memry allocation succes, taken %ld bytes", (long)((length + 1) * sizeof(char)));
    buffer[length] = '\0';
    fread(buffer, 1, length, curr_file);
    fclose(curr_file);
    LOGGER_INFO("File closed, buffer returned");
    return buffer;
}

size_t count_string_and_prepare_buffer(char* buff) {
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

size_t get_string_from_buffer(char** string_ptr, char** buff) {
    HARD_ASSERT(buff != nullptr, "Buff is nullptr");

    *string_ptr = *buff;
    size_t string_len = 0;
    while(**buff != '\0') {
        (*buff)++;
        string_len++;
    }
    (*buff)++;

    return string_len;
}

string_data** input_parsing(char* buff, size_t* strings_num_return) {
    LOGGER_DEBUG("input_parsing started");
    if (buff == nullptr) LOGGER_WARNING("Buff is nullptr");
    
    size_t strings_num = count_string_and_prepare_buffer(buff);
    string_data** strings = (string_data**)calloc(strings_num, sizeof(string_data*));
    for(size_t i = 0; i < strings_num; i++) {
        strings[i] = (string_data*)calloc(1, sizeof(string_data));
        strings[i]->len = get_string_from_buffer(&(strings[i]->str), &buff);    
    }
    *strings_num_return = strings_num;
    return strings;
}


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
