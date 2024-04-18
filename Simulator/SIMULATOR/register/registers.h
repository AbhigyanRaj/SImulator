#ifndef REGISTERS_H
#define REGISTERS_H
#include "../../../include/bit/bit.h"

#define REGISTER_COUNT 32
#define REGISTER_SIZE 32
#define REGISTER_ADDRESS_SIZE 5

typedef struct
{
    Bit bits[REGISTER_SIZE];
    Bit address[REGISTER_ADDRESS_SIZE];
    char* abi;
} Register;

typedef struct
{
    Register registers[REGISTER_COUNT];
} RegisterFile;

RegisterFile* initializeRegisters();

void deallocateRegisters(RegisterFile *REGISTER_FILE);

Register* findRegister(RegisterFile *REGISTER_FILE, const char* ABI);

Register* getRegisterByIndex(RegisterFile* REGISTER_FILE, char index);

const char* getABI(RegisterFile *REGISTER_FILE, unsigned int index);

const Bit* getAddress(RegisterFile *REGISTER_FILE, const char* ABI);

unsigned int hash(const char* abiName);

void setRegisterValue(Register *REGISTER, const Bit BITS[REGISTER_SIZE]);

void setBit(Register *REGISTER, unsigned int INDEX, const Bit *BIT);

void printRegister(const Register *REGISTER);

void printRegisterFile(const RegisterFile *REGISTER_FILE);

#endif 
