#include "fixed_xor.h"

uint8_t hex2nibble(char hex) {
    uint8_t nibble = hex;

    if (nibble >= '0' && nibble <= '9') nibble = nibble - '0';
    else if (nibble >= 'a' && nibble <='f') nibble = nibble - 'a' + 10;
    else if (nibble >= 'A' && nibble <='F') nibble = nibble - 'A' + 10;

    return nibble & 0xF;
}

char nibble2hex(uint8_t nibble) {
    char hex = nibble;

    if (hex >= 0 && hex <= 9) hex = '0' + hex;
    else if (hex >= 10 && hex <= 15) hex = 'a' + (hex - 10);

    return hex;
}


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