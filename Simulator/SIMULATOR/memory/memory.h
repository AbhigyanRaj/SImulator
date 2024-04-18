#ifndef MEMORY_H

#include "../register/registers.h"

#define MEMORY_H
#define PROGRAM_MEMORY 64
#define STACK_MEMORY 32
#define DATA_MEMORY 32
#define MEMORY_SIZE STACK_MEMORY+PROGRAM_MEMORY+DATA_MEMORY
#define MEMORY_CELL_SIZE 32
#define ADDRESS_SIZE 7
#define PROGRAM_ADDRESS_START 0
#define PROGRAM_ADDRESS_END PROGRAM_ADDRESS_START + PROGRAM_MEMORY
#define STACK_ADDRESS_START PROGRAM_ADDRESS_END
#define STACK_ADDRESS_END  STACK_ADDRESS_START + STACK_MEMORY
#define DATA_ADDRESS_START STACK_ADDRESS_END
#define DATA_ADDRESS_END DATA_ADDRESS_START + DATA_MEMORY

typedef struct
{
    Bit address[ADDRESS_SIZE];
    Bit bits[MEMORY_CELL_SIZE];
} MemoryCell;

typedef struct
{
    MemoryCell programMemory[PROGRAM_MEMORY];
    MemoryCell stackMemory[STACK_MEMORY];
    MemoryCell dataMemory[DATA_MEMORY];
    Register* stackPointer;
} Memory;

Memory* allocateMemory(Register* STACK_POINTER);

void deallocateMemory(Memory* MEMORY);

static bool isAddressInRange(const Bit ADDRESS[ADDRESS_SIZE], int start, int end);

int calculateMemoryIndex(const Bit ADDRESS[ADDRESS_SIZE]);

MemoryCell* getProgramMemory(Memory* MEMORY);

MemoryCell* getMemoryCell(Memory* MEMORY, const Bit ADDRESS[ADDRESS_SIZE]);

void printMemoryCell(const MemoryCell *MEMORYCELL);

MemoryCell* getStackMemory(Memory* MEMORY);

void printStackMemory(const Memory* MEMORY);

void decreaseStackPointer(Memory* MEMORY);

void increaseStackPointer(Memory* MEMORY);

void pushStackMemory(Memory* MEMORY, const Register* REGISTER);

Bit* popStackMemory(Memory* MEMORY);

MemoryCell* getDataMemory(Memory* MEMORY);

void printDataMemory(const Memory* MEMORY);

void setDataMemoryCell(Memory* MEMORY, const Bit ADDRESS[ADDRESS_SIZE], const Bit VALUE[MEMORY_CELL_SIZE]);

void setDataMemoryCellByIndex(Memory* MEMORY, int INDEX, const Bit VALUE[MEMORY_CELL_SIZE]);

void loadBinaryToProgramMemory(Memory* MEMORY, const char* RELATIVE_FILE_PATH);

void printProgramMemory(const Memory* MEMORY);
#endif