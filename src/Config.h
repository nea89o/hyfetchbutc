#ifndef HYFETCHBUTC_CONFIG_H
#define HYFETCHBUTC_CONFIG_H

typedef struct Option {
    char *name;
    struct Option *next;
} Option;

typedef struct HyConfig {
    char *api_key;
    Option *options;
} HyConfig;

HyConfig *load_config(char *path);

#endif //HYFETCHBUTC_CONFIG_H
