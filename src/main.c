#include <cjson/cJSON.h>
#include <stdio.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include "Request.h"
#include "Config.h"

int main() {
    puts("Hello, World");
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *curl = curl_easy_init();

    HyConfig *conf = load_config("example.conf");
    if (conf == NULL) {
        puts("no config");
        return 4;
    }
    printf("Api-Key: '%s'\n", conf->api_key);
    for (Option *ptr = conf->options; ptr; ptr = ptr->next) {
        printf("Option: '%s'\n", ptr->name);
    }

    if (!curl) {
        puts("Failed to initialize curl");
        return 2;
    }

    curl_easy_setopt(curl, CURLOPT_URL, "https://api.hypixel.net/resources/skyblock/items");

    struct MemoryStruct *response_body = capture_request_body(curl);


    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        return 3;
    }

    cJSON *resp = cJSON_ParseWithLength(response_body->memory, response_body->size);

    if (!cJSON_IsObject(resp)) {
        printf("Hypixel returned non object");
        return 1;
    }

    cJSON *lastUpdated = cJSON_GetObjectItemCaseSensitive(resp, "lastUpdated");
    printf("Last updated: %f", cJSON_GetNumberValue(lastUpdated));

    curl_global_cleanup();
    return 0;
}
