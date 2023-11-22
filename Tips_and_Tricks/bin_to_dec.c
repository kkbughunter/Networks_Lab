#include <stdio.h>
#include <stdlib.h>

int main() {
    char binaryString[] = "111"; 
    
    int decimal = strtol(binaryString, NULL, 2);

    printf("Binary: %s\nDecimal: %d\n", binaryString, decimal);

    return 0;
}
