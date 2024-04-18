#ifndef MEMORY_H

#define PROGRAM_MEMORY 64
#define STACK_MEMORY 32
#define DATA_MEMORY 32
#define MEMORY_SIZE STACK_MEMORY+PROGRAM_MEMORY+DATA_MEMORY
#define MEMORY_CELL_SIZE 32
#define ADDRESS_SIZE 32
#define STACK_ADDRESS_END  STACK_ADDRESS_START + STACK_MEMORY/8 * 32
#define DATA_ADDRESS_START 1048576
#define DATA_ADDRESS_END DATA_ADDRESS_END + DATA_MEMORY/8 * 32

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

void pushStackMemory(Memory* MEMORY, const Bit BITS[MEMORY_CELL_SIZE]);

Bit* popStackMemory(Memory* MEMORY);

MemoryCell* getDataMemory(Memory* MEMORY);

void printProgramMemory(const Memory* MEMORY);

void printDataMemory(const Memory* MEMORY);

void deallocateMemory(Memory* MEMORY);

MemoryCell* getProgramMemory(Memory* MEMORY);

void printMemoryCell(const MemoryCell* MEMORYCELL);

MemoryCell* getStackMemory(Memory* MEMORY);

void printStackMemory(const Memory* MEMORY);

void decreaseStackPointer(Memory* MEMORY);

void increaseStackPointer(Memory* MEMORY);

#endif 
