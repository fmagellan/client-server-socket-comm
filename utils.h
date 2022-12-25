#include <stdio.h>
#define SPORT 50051
#define PRINTF(...) \
    printf(__VA_ARGS__); \
    printf("\n")

#define EXIT(...) PRINTF(__VA_ARGS__); \
    return 0
    