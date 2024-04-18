#include "registers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int hash(const char* abiName)
{
    unsigned int hashVal = 0;
    for (; *abiName; )
    {
    hashVal = (hashVal << 5) + *abiName++;
    }
    return hashVal % REGISTER_COUNT;

}

void setBit(Register *REGISTER, unsigned int INDEX, const Bit *BIT)
{
    if (INDEX >= REGISTER_SIZE || INDEX < 0)
    {
        perror("Error: Index out of bounds to set bit\nOperation: setBit");
        exit(EXIT_FAILURE);
    }
    REGISTER->bits[INDEX] = *BIT;
}

RegisterFile* initializeRegisters()
{
    RegisterFile *registerFile = (RegisterFile*)malloc(sizeof(RegisterFile));
    if (registerFile == NULL)
    {
        perror("Error allocating memory for registers\nOperation: initialising");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (i < REGISTER_COUNT)
    {
    int j = 0;
    
    while (j < REGISTER_SIZE)
    {
        registerFile->registers[i].bits[j].value = 0;
        ++j;
    }

    int k = 0;
    
    while (k < 5)
    {
        registerFile->registers[i].address[k].value = (i >> (4 - k)) & 1;
        ++k;
    }

    registerFile->registers[i].abi = strdup(abi[i]);

    ++i;
    }


    return registerFile;
}

void deallocateRegisters(RegisterFile *REGISTER_FILE)
{
    free(REGISTER_FILE);
}

Register* getRegister(RegisterFile *REGISTER_FILE, const char* ABI)
{
    unsigned int index = hash(ABI);
    Register* current = &REGISTER_FILE->registers[index];
   for (; current != NULL; )
    {
    if (strcmp(current->abi, ABI) == 0)
    {
        return current;
    }
    index = (index + 1) % REGISTER_COUNT;
    current = &REGISTER_FILE->registers[index];
    }
return NULL;

}

void printRegisterFile(const RegisterFile *REGISTER_FILE)
{
    for (int i = 0; i < REGISTER_COUNT; ++i)
    {
        printRegister(&REGISTER_FILE->registers[i]);
        printf("\n");
    }
}

const Bit* getAddress(RegisterFile *REGISTER_FILE, const char* ABI)
{
    return getRegister(REGISTER_FILE, ABI)->address;
}

void setRegisterValue(Register *REGISTER, const Bit BITS[REGISTER_SIZE])
{
    for (int i = 0; i < REGISTER_SIZE; ++i)
    {
        REGISTER->bits[i].value = BITS[i].value;
    }
}



void printRegister(const Register *REGISTER)
{
    printf("ABI:  %s", REGISTER->abi);
    printf(" , Address: ");
    for (int i = 0; i < 5; ++i)
    {
        printf("%d", REGISTER->address[i].value);
    }
    printf(" , Value: ");
    for (int i = 0; i < REGISTER_SIZE; ++i)
    {
        printf("%d", REGISTER->bits[i].value);
    }
    printf("\n");
}

Register* getRegisterByAddress(RegisterFile* REGISTER_FILE, Bit ADDRESS[REGISTER_ADDRESS_SIZE])
{
    char index = toDecimal(ADDRESS, 0, REGISTER_ADDRESS_SIZE - 1, false);
    return &REGISTER_FILE->registers[index];
}



Register* getRegisterByIndex(RegisterFile* REGISTER_FILE, char index)
{
    return &REGISTER_FILE->registers[index];
}


static const char* abi[REGISTER_COUNT] = {
    "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1", 
    "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "s2", "s3", 
    "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};