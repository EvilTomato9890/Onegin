#ifndef ERROR_HANDLING_H_INCLUDED
#define ERROR_HANDLING_H_INCLUDED

#include "logger.h"

enum error_type {
    NO_ERROR = 0,
    OPEN_FILE_ERROR,
    READ_FILE_ERROR,
    PROCESSING_FILE_ERROR,
    MEMORY_ALLOC_ERROR
};

#define CHECK_ERROR(test, code) \
    do { \
        if(!(test)) { \
            code \
        } \
    } while(0)

#endif