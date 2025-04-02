#include "basics.h"


int score_string(const char* string, char* solution) {
   size_t nbytes = strlen(string) + 1;
   char *contender = malloc(nbytes);
   contender[nbytes] = '\0';
   int highest = 0;
   
   char key;
   for(key = 32; key < 127; key++) { 
      int score = 0;
      int i;

      for( i = 0;  i < nbytes; i++ ) {
         char crypt = string[i];
         char cypher = crypt ^ key;
         
         if(cypher < ' ' || cypher > '~' ) break;

         score += score_char_english(cypher);
         if(score < -50) break;
         contender[i] = cypher;
      }

      if(score > highest) {
         highest = score;
         strcpy(solution, contender);
      }

   }
   free(contender);
   return highest;
}


char* hex2ascii(const char* hex_string) {
   size_t nchars = strlen(hex_string)/2;
   char* ascii_string = malloc(nchars);
   ascii_string[nchars] = '\0';

   int i;
   for (i = 0; i < nchars; i++) {
      ascii_string[i] = hex2byte(&hex_string[i << 1]);
   }
   return ascii_string;
}

char* detect_char_xor(const char *filename) {
   char* hex_string = malloc(sizeof(char) * 62);
   FILE* cyphertext_file;

   char* cyphertext;
   char* solution = malloc(sizeof(char) * 62);


   int highest = 0;

   cyphertext_file = fopen(filename, "r");


   while (fgets(hex_string, 62, cyphertext_file) != NULL) {
      char *contender = malloc(strlen(hex_string)/2 + 1);
      cyphertext = hex2ascii(hex_string);
      int score = score_string(cyphertext, contender);
      if (score > highest) {
         highest = score;
         strcpy(solution, contender);
      }
      free(contender);
   }

   fclose(cyphertext_file);
   printf("    Highest Scoring: %s\n", solution);
   return (char*) solution;
}