#include "basics.h"

char* fixed_xor(const char *h1, const char *h2) {
    size_t nchars = strlen(h1);
    char* result = malloc(nchars + 1);
    result[nchars] = '\0';

    int i;
    for(i = 0; i < nchars; i++) {
        result[i] = nibble2hex( hex2nibble(h1[i]) ^ hex2nibble(h2[i]));   
    }

    printf("    Hex String 1: %s\n", h1);
    printf("    Hex String 2: %s\n", h2);
    printf("    Result: %s\n", result);


    return (char*)result;
}