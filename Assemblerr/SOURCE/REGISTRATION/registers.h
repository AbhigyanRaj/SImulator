#ifndef REGISTERS_H
#define REGISTERS_H
#include "../../include/bit.h"

#define REGISTER_COUNT 32
#define REGISTER_SIZE 32

typedef struct
{
    Bit bits[32];
    Bit address[5];
    char* abi;
} Register;

typedef struct
{
    Register registers[REGISTER_COUNT];
} RegisterFile;

RegisterFile* init();

void deallocateRegisters(RegisterFile *REGISTER_FILE);

Register* getRegister(RegisterFile *REGISTER_FILE, const char* ABI);

const char* getABI(RegisterFile *REGISTER_FILE, unsigned int index);

const Bit* getAddress(RegisterFile *REGISTER_FILE, const char* ABI);

unsigned int hash(const char* abiName);

void setRegisterValue(Register *REGISTER, const Bit BITS[REGISTER_SIZE]);

void setBit(Register *REGISTER, unsigned int INDEX, const Bit *BIT);

void printRegister(const Register *REGISTER);

void printRegisterFile(const RegisterFile *REGISTER_FILE);

#endif // REGISTERS_H
