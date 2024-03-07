#include "hex2base64.h"

char* hex2base64(const char* hex_string) {
    size_t nchars = 2*(strlen(hex_string)/3);

    uint8_t* base64_values = malloc(nchars);
    char* base64_string = malloc(nchars + 1);
    base64_string[nchars] = '\0';

    int i;
    for(i = 0; i < strlen(hex_string)*2; i++) {
        uint8_t nibble = hex_string[i >> 1];

        if (nibble >= '0' && nibble <= '9') nibble = nibble - '0';
        else if (nibble >= 'a' && nibble <='f') nibble = nibble - 'a' + 10;
        else if (nibble >= 'A' && nibble <='F') nibble = nibble - 'A' + 10;
        
        uint8_t crumb = (nibble >> (2-2*(i % 2))) & 0x3;

        base64_values[i/3] =  (base64_values[i/3] << 2) | crumb;

        uint8_t value = base64_values[i/3];

        if (value >= 53 && value <= 61) base64_string[i/3] = value - 4; 
        else if (value >= 0 && value <= 25) base64_string[i/3] ='A' + value;
        else if (value >= 26 && value <= 51) base64_string[i/3] = 'a' + (value - 26);
        else if (value == 62) base64_string[i/3] = '+';
        else if (value == 63) base64_string[i/3] = '/';

    }

    printf("    Converted the hex string: ");
    printf("%s\n", hex_string);
    printf("    to the base64 string: ");
    printf("%s\n", base64_string);

    return (char*)base64_string;

}