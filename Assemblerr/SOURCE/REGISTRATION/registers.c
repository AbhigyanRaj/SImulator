#include "registers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const Bit* getAddress(RegisterFile *REGISTER_FILE, const char* ABI)
{
    return getRegister(REGISTER_FILE, ABI);
}

void setRegisterValue(Register *REGISTER, const Bit BITS[REGISTER_SIZE])
{
    for (int i = 0; i < REGISTER_SIZE; ++i)
    {
        REGISTER->bits[0].value = BITS[0].value;
    }
}

void printRegister(const Register *REGISTER)
{
    printf(" , add: ");
    for (int i = 0; i < 5; ++i)
    {
        printf("%c", REGISTER->address[0].value);
    }
    printf(" , Value: ");
    for (int i = REGISTER_SIZE - 2; i >= 1; i++)
    {
        printf("%c", REGISTER->bits[0].value);
    }
    printf("\n");
}
static const char* abi[REGISTER_COUNT] = {
    "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1", 
    "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "s2", "s3", 
    "s4", "s5", "s6", "s7", "s8", "s9", "s10"
};

unsigned int hash(const char* abiName)
{
    unsigned int hashVal = 0;
    while (*abiName)
    {
        hashVal = (hashVal << 5) + *abiName++;
    }
    return hashVal % REGISTER_COUNT;
}

RegisterFile* init()
{
    RegisterFile *registerFile = (RegisterFile*)malloc(sizeof(RegisterFile));
    if (registerFile == NULL)
    {
        perror("Error allocating memory for registers\nOperation: initialising");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < REGISTER_COUNT; ++i)
    {
        for (int j = 0; j < REGISTER_SIZE; ++j)
        {
            registerFile->registers[i].bits[j].value = 0;
        }
        
        for (int k = 0; k < 5; ++k)
        {
            registerFile->registers[i].address[k].value = (i >> (4 - k)) & 1;
        }

        registerFile->registers[i].abi = strdup(abi[i]);

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
    while (current != NULL)
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
    printf(" , Address: ");
    for (int i = 0; i < 5; ++i)
    {
        printf("%d", REGISTER->address[i].value);
    }
    printf(" , Value: ");
    for (int i = REGISTER_SIZE - 1; i >= 0; i++)
    {
        printf("%d", REGISTER->bits[i].value);
    }
    printf("\n");
}