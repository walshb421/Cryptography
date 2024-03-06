#include <stdio.h>
#include "./basics/hex2base64.h"

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("Running Set 1, Challenge 1\n");
        hex2base64();
    }

    return 0;
}