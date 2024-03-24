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


int score_char_english(const char letter) {
    const char* rank = "ETAOIN SHRDLCUMWFGYPBVKJXQZ"; // From Wikipedia
    int score = 0;
    if(letter > ' ' && letter < 'A' ) { 
        // If this were smarter it would score based on least frequent characters too
        return -1; 
    }
    else { 
        int value = strlen(rank);
        int k;
        for(k = 0; k < value; k++) {
            if(letter == rank[k]) {
                return (value - k);
                break;
            }
        }

    }
}

int score_string_english(const char* string) {

}