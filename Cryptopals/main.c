#include <stdio.h>
#include <string.h>

#include "basics/basics.h"

int main(int argc, char* argv[]) {
    if (\
        (argc == 1) || \
        (argc > 1 && argv[1][0] == '1') \
    ) {
         printf(" ============ Running Set 1 ============ \n");
    
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
            (argc == 2 && argv[1][0] == '1') || \
            (argc == 3 && (argv[1][0] == '1' && argv[2][0] == '3'))
        ) {
            printf("Challenge 3: Single Byte Xor Cypher \n");

            const char* hex_string = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
            const char* expected = "Cooking MC's like a pound of bacon";
            const char* actual = xor_cypher(hex_string);

            if(!strcmp(expected, actual)) {
                printf("\e[92mChallenge 3 Passed!\e[0m \n");
            }
            else {
                printf("\e[91mChallenge 3 Failed! \e[0m \n");
                printf("%s\n", actual);
                printf("is different than the expected: ");
                printf("%s\n", expected);

            }

        }

        if (\
            (argc == 1) || \
            (argc == 2 && argv[1][0] == '1') || \
            (argc == 3 && (argv[1][0] == '1' && argv[2][0] == '4'))
        ) {
            printf("Challenge 4: Detect single-character XOR \n");

            const char* cyphertext_file = "./basics/cyphertext1.txt";
            const char* expected = "Now that the party is jumping";
            const char* actual = detect_char_xor(cyphertext_file);

            if(!strcmp(expected, actual)) {
                printf("\e[92mChallenge 4 Passed!\e[0m \n");
            }
            else {
                printf("\e[91mChallenge 4 Failed! \e[0m \n");
                printf("%s\n", actual);
                printf("is different than the expected: ");
                printf("%s\n", expected);

            }

        }

        if (\
            (argc == 1) || \
            (argc == 2 && argv[1][0] == '1') || \
            (argc == 3 && (argv[1][0] == '1' && argv[2][0] == '5'))
        ) {
            printf("Challenge 5: Implement repeating-key XOR \n");
            const char* key = "ICE";
            const char* text = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";

            const char* expected = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
            const char* actual = encrypt_repeating_xor(key, text);

            if(!strcmp(expected, actual)) {
                printf("\e[92mChallenge 5 Passed!\e[0m \n");
            }
            else {
                printf("\e[91mChallenge 5 Failed! \e[0m \n");
                printf("%s\n", actual);
                printf("is different than the expected: ");
                printf("%s\n", expected);

            }


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