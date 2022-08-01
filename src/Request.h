#ifndef HYFETCHBUTC_REQUEST_H
#define HYFETCHBUTC_REQUEST_H

#include <stddef.h>
#include <curl/curl.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

struct MemoryStruct *capture_request_body(CURL *curl);

#endif //HYFETCHBUTC_REQUEST_H
