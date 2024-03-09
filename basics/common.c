#include "basics.h"

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


uint8_t hex2byte(const char* hex) {
    return (hex2nibble(*hex) << 4) |  hex2nibble(*(hex + 1));
}