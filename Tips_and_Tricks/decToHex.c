#include <stdio.h>

void decToHex(unsigned long int decimal) {
    char hex[50];
  
    sprintf(hex, "%lX", decimal);

    printf("Decimal: %lu\n", decimal);
    printf("Hexadecimal: %s\n", hex);
}

int main() {
    unsigned long int decimalValue = 12345; 

    decToHex(decimalValue);

    return 0;
}
