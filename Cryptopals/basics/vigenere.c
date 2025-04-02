#include "basics.h"

void vigenere(const char* filename, const char* key) {
    FILE* file = fopen(filename, "r");
    int keylen = strlen(key);
    char* buffer = malloc(sizeof(char)* 72);
    int count = 0;
    while (!feof(file)) {
        buffer[count++] = fgetc(file) ^ key[count % keylen];
        if(count == 71) {
            buffer[count] = '\0';
            printf("%s\n", buffer);
            count = 0;
        }
    }
    free(buffer);
}