#include "Config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_option(HyConfig *config, char *line) {
    size_t l = strlen(line);
    printf("Processing line %s\n", line);
    if (strstr(line, "api_key ") == line) {
        config->api_key = (char *) malloc(l - 8);
        strcpy(config->api_key, line + 8);
    } else if (strstr(line, "option ")) {
        Option *option = (Option *) malloc(sizeof(Option));
        option->name = malloc(l - 7);
        strcpy(option->name, line + 7);

        if (config->options == NULL) {
            config->options = option;
        } else {
            Option *head = config->options;
            while (head->next != NULL) {
                head = head->next;
            }
            head->next = option;
        }
    } else {
        printf("Unknown line %s\n", line);
    }
}

void strip_newline(char *line) {
    char *end = strchr(line, '\n');
    if (end != NULL) {
        *end = '\0';
    }
}

HyConfig *load_config(char *path) {
    FILE *handle = fopen(path, "r");
    if (handle == NULL) return NULL;

    HyConfig *config = malloc(sizeof(HyConfig));
    config->api_key = NULL;
    config->options = NULL;
    char *line;
    size_t linelen;
    while ((linelen = getline(&line, &linelen, handle)) != -1) {
        strip_newline(line);
        parse_option(config, line);
    }
    if (line != NULL) {
        free(line);
    }
    fclose(handle);
    return config;
}
