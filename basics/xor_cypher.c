#include "basics.h"

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


char* xor_cypher(const char* hex_string) {

    // From Wikipedia (Plus Space Placement from prompt)
    const char* scoring = "ETAOIN SHRDLCUMWFGYPBVKJXQZ";
   

    // Variables Relating to the best message
    int highest = 0;
    size_t nchars = strlen(hex_string)/2;
    char *winner = malloc(nchars + 1);
    winner[nchars] = '\0'; 


    int i;
    for(i = 32; i < 127; i++) {
        int score = 0;
        char *contender = malloc(nchars + 1);

        int j;
        for(j = 0; j < nchars; j++) {
            char crypt = hex2byte(&hex_string[j << 1]);
            char key = i;
            char cypher = crypt ^ key;
            
            if(cypher < ' ' || cypher > '~' ) break;

            score += score_char_english(cypher);
            if(score < -50) break;
            contender[j] = cypher;

        }

        if(score > highest) {
            highest = score;
            strcpy(winner, contender);
        }

        free(contender);

    }
    
    printf("Highest Scoring Message:\n %s\n", winner);
    return (char*) winner;
            
}