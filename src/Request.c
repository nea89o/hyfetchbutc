#include "Request.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) userp;

    mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);

    if (mem->memory == NULL) {
        fprintf(stderr, "OOM\n");
        return 0;
    }
    memcpy(mem->memory + mem->size, contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

struct MemoryStruct *capture_request_body(CURL *curl) {
    struct MemoryStruct *chunk = malloc(sizeof(struct MemoryStruct));
    chunk->memory = (char *) malloc(1);
    chunk->size = 0;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) chunk);
    return chunk;
}