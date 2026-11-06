#include "error_codes.h"

const char* error_code_to_string(ErrorCode code) {
    switch (code) {
        case ErrorCode::OK:              return "OK";
        case ErrorCode::FILE_NOT_FOUND:  return "File not found";
        case ErrorCode::BAD_FORMAT:      return "Bad file format";
        case ErrorCode::OUT_OF_MEMORY:   return "Out of memory";
        case ErrorCode::INVALID_SIZE:    return "Invalid map size";
    }
    return "Unknown error";
}