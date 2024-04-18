#include <stdio.h>
#include <stdlib.h>
#include "bit.h"

// CREATING GATES FOR BINARY NUMBERS
Bit AND(const Bit* BIT_1, const Bit* BIT_2)
{
    Bit result;
    result.value = BIT_1->value & BIT_2->value;
    return result;
}
Bit OR(const Bit* BIT_1, const Bit *BIT_2)
{
    Bit result;
    result.value = BIT_1->value | BIT_2->value;
    return result;
}
Bit XOR(const Bit* BIT_1, const Bit* BIT_2)
{
    Bit result;
    result.value = BIT_1->value ^ BIT_2->value;
    return result;
}
Bit NAND(const Bit *BIT_1, const Bit *BIT_2)
{
    Bit result;
    result.value = !(BIT_1->value & BIT_2->value);
    return result;
}
Bit NOR(const Bit *BIT_1, const Bit *BIT_2)
{
    Bit result;
    result.value = !(BIT_1->value | BIT_2->value);
    return result;
}
Bit NOT(const Bit *BIT)
{
    Bit result;
    result.value = !BIT->value;
    return result;
}
Bit* bitwiseOR(const Bit* BIT_ARRAY_1, const Bit* BIT_ARRAY_2, unsigned char SIZE)
{

    if (SIZE > 32 || SIZE < 1)
    {
        perror("Invalid List");
        exit(EXIT_FAILURE);
    }
    Bit* result = createBitArray(SIZE);
    unsigned char i = 0;
    while (i < SIZE)
    {
    result[i] = OR(&BIT_ARRAY_1[i], &BIT_ARRAY_2[i]);
    ++i;
    }

    return result;
}
Bit* bitwiseAND(const Bit* BIT_ARRAY_1, const Bit* BIT_ARRAY_2, unsigned char SIZE)
{
    if (SIZE > 32 || SIZE < 1)
    {
        perror("Invalid List");
        exit(EXIT_FAILURE);
    }
    Bit* result = createBitArray(SIZE);
    unsigned char i = 0;
    while (i < SIZE)
    {
        result[i] = AND(&BIT_ARRAY_1[i], &BIT_ARRAY_2[i]);
        ++i;
    }
    return result;
}
Bit* bitwiseXOR(const Bit* BIT_ARRAY_1, const Bit* BIT_ARRAY_2, unsigned char SIZE) 
{
    if (SIZE > 32 || SIZE < 1)
    {
        perror("Invalid List");
        exit(EXIT_FAILURE);
    }
    Bit* result = createBitArray(SIZE);
    unsigned char i = 0;
    while (i < SIZE) 
    {
        result[i] = XOR(&BIT_ARRAY_1[i], &BIT_ARRAY_2[i]);
        ++i;
    }
    return result;
}
Bit* bitwiseNOT(const Bit* BIT_ARRAY, unsigned char SIZE) 
{
    if (SIZE > 32 || SIZE < 1)
    {
        perror("Invalid List");
        exit(EXIT_FAILURE);
    }
    Bit* result = createBitArray(SIZE);
    unsigned char i = 0;
    while (i < SIZE) 
    {
        result[i] = NOT(&BIT_ARRAY[i]);
        ++i;
    }

    return result;
}

// PERFORMING CALCULATIONS : SUBTRACTION,ADDITION,MULTIPLICATION

Bit* SUB(Bit* BIT_ARRAY_1, Bit* BIT_ARRAY_2, unsigned char INPUT_ARRAY_SIZE, unsigned char OUTPUT_ARRAY_SIZE) {
    if (INPUT_ARRAY_SIZE > 32 || OUTPUT_ARRAY_SIZE < 1)
    {
        perror("Invalid List");
        exit(EXIT_FAILURE);
    }
    if (OUTPUT_ARRAY_SIZE > 32 || OUTPUT_ARRAY_SIZE < 1)
    {
        perror("Invalid List");
    }
    Bit* result = createBitArray(OUTPUT_ARRAY_SIZE);
    Bit borrow;
    borrow.value = 0;

    unsigned char i = 0;
    while (i < INPUT_ARRAY_SIZE) 
    {
        Bit temp = XOR(&BIT_ARRAY_1[i], &BIT_ARRAY_2[i]);
        result[i] = XOR(&temp, &borrow);
        Bit temp1 = NOT(&temp);
        Bit temp2 = AND(&temp1, &borrow);
        temp1 = NOT(&BIT_ARRAY_1[i]);
        temp1 = AND(&temp1, &BIT_ARRAY_2[i]);
        borrow = OR(&temp2, &temp1);
        ++i;
    }
    result[OUTPUT_ARRAY_SIZE - 1] = borrow;

    return result;
}
Bit* ADD(Bit* BIT_ARRAY_1, Bit* BIT_ARRAY_2, unsigned char INPUT_ARRAY_SIZE, unsigned char OUTPUT_ARRAY_SIZE)
{
    if (INPUT_ARRAY_SIZE > 32 || OUTPUT_ARRAY_SIZE < 1)
    {
        perror("Invalid List");
        exit(EXIT_FAILURE);
    }
    if (OUTPUT_ARRAY_SIZE > 32 || OUTPUT_ARRAY_SIZE < 1)
    {
        perror("Invalid List");
    }
    Bit* result = createBitArray(OUTPUT_ARRAY_SIZE);
    Bit carry;
    carry.value = 0;
    unsigned char i = 0;
    while (i < INPUT_ARRAY_SIZE) 
    {
        Bit temp = XOR(&BIT_ARRAY_1[i], &BIT_ARRAY_2[i]);
        result[i] = XOR(&temp, &carry);
        Bit temp1 = AND(&temp, &carry);
        Bit temp2 = AND(&BIT_ARRAY_1[i], &BIT_ARRAY_2[i]);
        carry = OR(&temp1, &temp2);
        ++i;
    }
    result[OUTPUT_ARRAY_SIZE - 1] = carry;

    return result;
}
Bit* MUL(Bit* BIT_ARRAY_1, Bit* BIT_ARRAY_2, unsigned char INPUT_ARRAY_SIZE, unsigned char OUTPUT_ARRAY_SIZE) {
    if (INPUT_ARRAY_SIZE > 32 || OUTPUT_ARRAY_SIZE < 1)
    {
        perror("Invalid List");
        exit(EXIT_FAILURE);
    }
    if (OUTPUT_ARRAY_SIZE > 32 || OUTPUT_ARRAY_SIZE < 1)
    {
        perror("Invalid List");
    }
    Bit* result = createBitArray(OUTPUT_ARRAY_SIZE);

    unsigned char i = 0;
    while (i < INPUT_ARRAY_SIZE) 
    {
        Bit multiplierBit = BIT_ARRAY_2[i];
        Bit* tempResult = createBitArray(OUTPUT_ARRAY_SIZE);
        unsigned char j = 0;
        while (j < INPUT_ARRAY_SIZE) 
        {
            Bit temp = AND(&BIT_ARRAY_1[j], &multiplierBit);
            tempResult[j] = temp;
            ++j;
        }
        unsigned char k = OUTPUT_ARRAY_SIZE - 1;
        while (k > i) 
        {
            tempResult[k] = tempResult[k - i];
            --k;
        }
        result = ADD(result, tempResult, OUTPUT_ARRAY_SIZE, OUTPUT_ARRAY_SIZE);

        free(tempResult);
        ++i;
    }
    return result;
}

// INCREMENTING AND DECREMENTING IN LIST

void incrementBitArray(Bit* BIT_ARRAY, unsigned char SIZE)
{
    if (SIZE > 32 || SIZE < 1)
    {
        perror("Invalid List");
        exit(EXIT_FAILURE);
    }
    int i = SIZE - 1;
    while (i >= 0) 
    {
        if (BIT_ARRAY[i].value == 0) 
        {
            BIT_ARRAY[i].value = 1;
            break;
        } 
        else 
        {
            BIT_ARRAY[i].value = 0;
        }
        --i;
    }
}

void decrementBitArray(Bit* BIT_ARRAY, unsigned char SIZE)
{
    if (SIZE > 32 || SIZE < 1)
    {
        perror("Invalid List");
        exit(EXIT_FAILURE);
    }
    int i = SIZE - 1;
    while (i >= 0) 
    {
        if (BIT_ARRAY[i].value == 1) 
        {
            BIT_ARRAY[i].value = 0;
            break;
        } 
        else 
        {
            BIT_ARRAY[i].value = 1;
        }
        --i;
    }

}
// HANDLING SIGNS OF NUMBERS

Bit* toUnsignedBitArray(int decimal, unsigned char SIZE)
{
    if (SIZE > 32 || SIZE < 1)
    {
        perror("Invalid List");
        exit(EXIT_FAILURE);
    }
    Bit* bitArray = createBitArray(SIZE);
    int i = SIZE - 1;
    while (i >= 0) 
    {
        bitArray[i].value = decimal % 2;
        decimal /= 2;
        --i;
    }
    return bitArray;
}

Bit* toSignedBitArray(int decimal, unsigned char SIZE)
{
    if (SIZE > 32 || SIZE < 1)
    {
        perror("Invalid List");
        exit(EXIT_FAILURE);
    }

    Bit* bitArray = createBitArray(SIZE);

    if (decimal < 0)
    {
        Bit* absBitArray = toUnsignedBitArray(-decimal, SIZE);

        int i = 0;
    while (i < SIZE)
    {
        absBitArray[i].value = !absBitArray[i].value;
        ++i;
    }
        incrementBitArray(absBitArray, SIZE);

        int i = 0;
    while (i < SIZE)
    {
        bitArray[i].value = absBitArray[i].value;
        ++i;
    }
        free(absBitArray);
    }
    else 
    {
        int i = SIZE - 1;
        while (i >= 0)
        {
            bitArray[i].value = decimal % 2;
            decimal /= 2;
            --i;
        }
    }
    return bitArray;
}

int toDecimal(const Bit* BIT_ARRAY, unsigned char ARRAY_START, unsigned char ARRAY_END, bool IS_SIGNED)
{
    int decimal = 0;

    int i = ARRAY_START;
    while (i < ARRAY_END)
    {
        decimal = (decimal << 1) | BIT_ARRAY[i].value;
        ++i;
    }
    if (IS_SIGNED && BIT_ARRAY[0].value == 1)
    {
        decimal -= (1 << (ARRAY_END-ARRAY_START));
    }
    return decimal;
}

short signExtend(const Bit* BIT_ARRAY, unsigned char SIZE)
{
    if (SIZE > 32 || SIZE < 1)
    {
        perror("Invalid List");
        exit(EXIT_FAILURE);
    }
    Bit temporary[32];
    int i = 0;
    while (i < SIZE)
    {
        temporary[32 - SIZE + i] = BIT_ARRAY[i];
        ++i;
    }
    int i = 0;
    while (i < 32 - SIZE)
    {
        temporary[i].value = BIT_ARRAY[0].value;
        ++i;
    }
    return toDecimal(temporary, 0, 32, true);
}
