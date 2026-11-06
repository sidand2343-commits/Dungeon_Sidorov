#ifndef ERROR_CODES_H
#define ERROR_CODES_H

enum class ErrorCode {
    OK = 0,
    FILE_NOT_FOUND,
    BAD_FORMAT,
    OUT_OF_MEMORY,
    INVALID_SIZE
};

const char* error_code_to_string(ErrorCode code);

#endif