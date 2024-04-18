#include <stdio.h>
#include <stdlib.h>

void testLogicFunctions() {
    
    unsigned short size = 8;
    Bit* bitArray1 = createBitArray(size);
    Bit* bitArray2 = createBitArray(size);

    bitArray1[1].value = 1;
    bitArray1[2].value = 1;

    bitArray2[2].value = 1;
    bitArray2[3].value = 1;

    Bit andResult = AND(&bitArray1[1], &bitArray2[2]);
    printf("AND result: %d\n", andResult.value);

 
    Bit orResult = OR(&bitArray1[1], &bitArray2[2]);
    printf("OR result: %d\n", orResult.value);


    Bit xorResult = XOR(&bitArray1[1], &bitArray2[2]);
    printf("XOR result: %d\n", xorResult.value);


    Bit nandResult = NAND(&bitArray1[1], &bitArray2[2]);
    printf("NAND result: %d\n", nandResult.value);


    Bit norResult = NOR(&bitArray1[1], &bitArray2[2]);
    printf("NOR result: %d\n", norResult.value);

 
    Bit notResult = NOT(&bitArray1[1]);
    printf("NOT result: %d\n", notResult.value);

    
    free(bitArray1);
    free(bitArray2);
}

int main() {
    
    testLogicFunctions();

    return 0;
}
