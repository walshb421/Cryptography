#include <stdio.h>
#include <string.h>

#include "./basics/hex2base64.h"

int main(int argc, char* argv[]) {
    if (\
        (argc == 1) || \
        (argc == 2 && argv[1][0] == '1') || \
        (argc == 3 && (argv[1][0] == '1' && argv[2][0] == '1'))
    ) {
        printf(" ============ Running Set 1 ============ \n");
        printf("Challenge 1: Convert hex to base64 \n");

        const char* hex_string = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
        const char* base64_string = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
        char* result;

        result = hex2base64(hex_string);

        if(!strcmp(base64_string, result)) {
            printf("\e[92m Challenge 1 Passed!\e[0m \n");
        }
        else {
            printf("\e[91m Challenge 1 Failed! \e[0m \n");
            printf("%s\n", result);
            printf("is different than the expected: ");
            printf("%s\n", base64_string);

        }

        printf(" ======================================= \n");

    }

    return 0;
}