#include <stdio.h>
#include <string.h>

#include "./basics/hex2base64.h"
#include "./basics/fixed_xor.h"

int main(int argc, char* argv[]) {
    if (\
        (argc == 1) || \
        (argc > 1 && argv[1][0] == '1') \
    ) {
         printf(" ============ Running Set 1 ============ \n");
    }
    if (\
        (argc == 1) || \
        (argc == 2 && argv[1][0] == '1') || \
        (argc == 3 && (argv[1][0] == '1' && argv[2][0] == '1'))
    ) {
        printf("Challenge 1: Convert hex to base64 \n");

        const char* hex_string = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
        const char* base64_string = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
        char* result;

        result = hex2base64(hex_string);

        if(!strcmp(base64_string, result)) {
            printf("\e[92mChallenge 1 Passed!\e[0m \n");
        }
        else {
            printf("\e[91mChallenge 1 Failed! \e[0m \n");
            printf("%s\n", result);
            printf("is different than the expected: ");
            printf("%s\n", base64_string);

        }


    }

    if (\
        (argc == 1) || \
        (argc == 2 && argv[1][0] == '1') || \
        (argc == 3 && (argv[1][0] == '1' && argv[2][0] == '2'))
    ) {
        printf("Challenge 2: Fixed XOR \n");

        const char* hex_string1 = "1c0111001f010100061a024b53535009181c";
        const char* hex_string2 = "686974207468652062756c6c277320657965";


        const char* expected = "746865206b696420646f6e277420706c6179";
        char* actual;

        actual = fixed_xor(hex_string1, hex_string2);

        if(!strcmp(expected, actual)) {
            printf("\e[92mChallenge 2 Passed!\e[0m \n");
        }
        else {
            printf("\e[91mChallenge 2 Failed! \e[0m \n");
            printf("%s\n", actual);
            printf("is different than the expected: ");
            printf("%s\n", expected);

        }


    }

    if (\
        (argc == 1) || \
        (argc > 1 && argv[1][0] == '1') \
    ) {
         printf(" ======================================= \n");
    }

    return 0;
}