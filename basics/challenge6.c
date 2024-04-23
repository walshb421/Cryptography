#include "basics.h"


int hamming(const char* string1, const char* string2, int nchars) {
    
    int nbits = nchars * 8;
    int hamming = 0;

    int i;
    for(i = 0; i < nbits; i++) {
        hamming += \
            ((string1[i / 8] >> (i % 8)) & 0x1) \
            != ((string2[i / 8] >> (i % 8)) & 0x1);
    }

    return hamming;
}

int guess_keysize(const char *file) {
    FILE* source = fopen(file, "r");
    char* cyphertext = malloc(sizeof(char) * 200);
    int i;

    for(i = 0; i < 3; i++ ) {
        fgets(cyphertext + i*60, 62, source);
    }

    fclose(source);

    int best_keysize = 0;
    int lowest_normalized_hamming = 0xFFFFFF;

    for(i = 2; i <= 40; i++) {
        int total = 0;
    
        total += hamming(cyphertext, cyphertext + i, i);
        total += hamming(cyphertext, cyphertext + 2*i, i);
        total += hamming(cyphertext, cyphertext + 3*i, i);
        total += hamming(cyphertext + i, cyphertext + 2*i, i);
        total += hamming(cyphertext + i, cyphertext + 3*i, i);
        total += hamming(cyphertext + 2*i, cyphertext + 3*i, i);
        
        if ( (total/6)/i < lowest_normalized_hamming ) {
            best_keysize = i;
            lowest_normalized_hamming = (total/6)/i;
        }
        
    }
    
    free(cyphertext);

    return best_keysize;
}


char guess_char_xor(const char* cyphertext) {
    char key;

    // Variables Relating to the best message
    int highest = 0;
    size_t nchars = strlen(cyphertext);
        int i;
    for(i = 32; i < 127; i++) {
        int score = 0;

        int j;
        for(j = 0; j < nchars; j++) {
            char crypt = cyphertext[j];
            char cypher = crypt ^ i;
            
            if(cypher < ' ' || cypher > '~' ) break;

            score += score_char_english(cypher);
            if(score < -50) break;

        }

        if(score > highest) {
            key = i;
            highest = score;
        }

    }

    return key;

}

char* decrypt_repeating_xor(const char* key, const char* text) {
    size_t nchars = strlen(text);

    char* crypttext = malloc(nchars + 1);
    crypttext[nchars] = '\0';

    char k;
    char l;
    int i;
    for(i = 0; i < nchars; i++) {
       k = key[i % 3]; 
       l = text[i];
       crypttext[i] = l ^ k;
    }

    
    printf("Decrypted String: %s\n", crypttext);

    return (char*) crypttext;
}

void break_vigenere_cypher(const char* src_file, const char* dest_file) {

    int keysize = guess_keysize(src_file);
    printf("%d\n", keysize);
    char* key = malloc(sizeof(char)*keysize);
    FILE* source = fopen(src_file, "r");
    char* cyphertext = malloc(sizeof(char) * 4096);
    int* indeces = malloc(sizeof(int) * keysize);
    char** bytes = malloc(sizeof(char*) * keysize);

    int i;
    for( i = 0 ; i < keysize ; i++) {
        indeces[i] = 0;
        bytes[i] = malloc(sizeof(char)*2048);
    }

    int count = 0;
    while(!feof(source) && count < 50) {
        cyphertext[count] = fgetc(source);
        bytes[count % keysize][indeces[count % keysize]] = cyphertext[count];
        indeces[count % keysize]++;
        count++;
    }
    cyphertext[count] = '\0';
   
    for( i = 0 ; i < keysize ; i++) {
        bytes[i][indeces[i]] = '\0';
        key[i] = guess_char_xor(bytes[i]);
    }
    key[keysize] = '\0';

    char* decrypted_key = decrypt_repeating_xor(key, cyphertext);
    //vigenere("./basics/cyphertext2.txt", decrypted_key);
    fclose(source);
    free(cyphertext);

    free(key);
    free(indeces);
    for( i = 0 ; i < keysize ; i++) {
        free(bytes[i]);
    }
    free(bytes);
}