#include <stdio.h>
#include <stdlib.h>
#include "../../include/bit.h"

void testConversionFunctions() {
    int decimalValue = 42;
    unsigned short size = 8;
    Bit* bitArray = toUnsignedBitArray(decimalValue, size);
    printf("Converted to unsigned bit array: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", bitArray[i].value);
    }
    printf("\n");

    int signedDecimalValue = -42;
    Bit* signedBitArray = toSignedBitArray(signedDecimalValue, size);
    printf("Converted to signed bit array: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", signedBitArray[i].value);
    }
    printf("\n");

    int convertedDecimal = toDecimal(bitArray, size, 0);
    printf("Converted to decimal (unsigned): %d\n", convertedDecimal);

    int convertedSignedDecimal = toDecimal(signedBitArray, size, 1);
    printf("Converted to decimal (signed): %d\n", convertedSignedDecimal);

    free(bitArray);
    free(signedBitArray);
}

int main() {
    testConversionFunctions();

    return 0;
}
