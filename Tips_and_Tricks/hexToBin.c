#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hexToBin(char hex[]) {
    unsigned long int dec = strtol(hex, NULL, 16);

    char bin[65]; 
    itoa(dec, bin, 2);

    printf("Hexadecimal: %s\n", hex);
    printf("Binary: %s\n", bin);
}

int main() {
    char hexString[] = "1A3F"; // Example hexadecimal string

    hexToBin(hexString);

    return 0;
}
