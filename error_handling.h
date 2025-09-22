#ifndef ERROR_HANDLING_H_INCLUDED
#define ERROR_HANDLING_H_INCLUDED

#include "logger.h"

enum error_type {
    OPEN_FILE_ERROR,
    READ_FILE_ERROR,
    MEMORY_ALLOC_ERROR,
    NO_ERROR
};

#define CHECK_ERROR(test, error, code) \
    do { \
        if(!(test)) { \
            LOGGER_ERROR("Error %s occured by %s", #error, #test); \
            code \
        } \
    } while(0)

#endif