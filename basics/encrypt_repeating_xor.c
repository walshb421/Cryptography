#include "basics.h"

char* encrypt_repeating_xor(const char* key, const char* text) {
    size_t nchars = strlen(text) * 2;
    char* crypttext = malloc(nchars);
    crypttext[nchars] = '\0';

    char k;
    char l;
    int i = 0;

    while((l = text[i]) != '\0') {
        k = key[i % 3];
        crypttext[i << 1] = nibble2hex(((l ^ k) & 0xF0) >> 4);
        crypttext[(i << 1) + 1] = nibble2hex((l ^ k) & 0xF);
        
        i++;
    } 
    
    printf("    Encrypted String: %s\n", crypttext);

    return (char*) crypttext;
}