#include "proxy_parse.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

typedef struct cache_element cache_element;

struct cache_element {
    char *data;
    int len;
    char* url;
    time_t lru_time_track;
    cache_element *next;
};

cach
