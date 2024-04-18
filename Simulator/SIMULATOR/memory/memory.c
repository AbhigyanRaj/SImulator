#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memory.h"

Memory* allocateMemory(Register* STACK_POINTER)
{
    Memory* memory = (Memory*)malloc(sizeof(Memory));
    if (memory == NULL)
    {
        perror("Error in memory alloation");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (i < PROGRAM_MEMORY)
    {
    int j = 0;
    while (j < MEMORY_CELL_SIZE)
    {
        memory->programMemory[i].bits[j].value = 0;
        ++j;
    }

    int k = ADDRESS_SIZE - 1;
    while (k >= 0)
    {
        memory->programMemory[i].address[k].value = ((i + PROGRAM_ADDRESS_START) >> (ADDRESS_SIZE - k - 1)) & 1;
        --k;
    }

    ++i;
}
   int i = 0;
while (i < STACK_MEMORY)
{
    int j = 0;
    while (j < MEMORY_CELL_SIZE)
    {
        memory->stackMemory[i].bits[j].value = 0;
        ++j;
    }
    int k = 0;
    while (k < ADDRESS_SIZE)
    {
        memory->stackMemory[i].address[k].value = ((i + STACK_ADDRESS_START) >> (ADDRESS_SIZE - k - 1)) & 1;
        ++k;
    }
    ++i;
}
    int i = 0;
    while (i < DATA_MEMORY)
    {
    int j = 0;
    while (j < MEMORY_CELL_SIZE)
    {
        memory->dataMemory[i].bits[j].value = 0;
        ++j;
    }

    int k = 0;
    while (k < ADDRESS_SIZE)
    {
        memory->dataMemory[i].address[k].value = ((i + DATA_ADDRESS_START) >> (ADDRESS_SIZE - k - 1)) & 1;
        ++k;
    }

    ++i;
    }
    memory->stackPointer = STACK_POINTER;
    Bit stackPointerAddress[REGISTER_SIZE];
    for (int i = 0; i < REGISTER_SIZE-ADDRESS_SIZE; ++i)
    {
        stackPointerAddress[i].value = 0;
    }
    for (int i = REGISTER_SIZE-ADDRESS_SIZE; i < REGISTER_SIZE; ++i)
    {
        stackPointerAddress[i].value = memory->stackMemory[0].address[i-(REGISTER_SIZE-ADDRESS_SIZE)].value;
    }
    setRegisterValue(memory->stackPointer, stackPointerAddress);
    return memory;
}
MemoryCell* getDataMemory(Memory* MEMORY)
{
    return MEMORY->dataMemory;
}
MemoryCell* getProgramMemory(Memory* MEMORY)
{
    return MEMORY->programMemory;
}
MemoryCell* getStackMemory(Memory* MEMORY)
{
    return MEMORY->stackMemory;
}

void printMemoryCell(const MemoryCell* MEMORYCELL)
{
    printf("Address: ");
    int i = 0;
    while (i < ADDRESS_SIZE)
    {
    printf("%d", MEMORYCELL->address[i].value);
    ++i;
    }
    printf(" , Value: ");

    i = 0;
    while (i < MEMORY_CELL_SIZE)
    {
    printf("%d", MEMORYCELL->bits[i].value);
    ++i;
    }

}
void printProgramMemory(const Memory* MEMORY)
{
    printf("\nProgram Memory:\n");
    int i = 0;
    while (i < PROGRAM_MEMORY)
    {
    printMemoryCell(&MEMORY->programMemory[i]);
    printf("\n");
    ++i;
    }

} 
void printStackMemory(const Memory* MEMORY)
{
    printf("\nStack Memory:\n");
    int i = 0;
    while (i < STACK_MEMORY)
    {
    printMemoryCell(&MEMORY->stackMemory[i]);
    printf("\n");
    ++i;
    }
}
void printDataMemory(const Memory* MEMORY)
{
    printf("\nMemory:\n");
    int i = 0;
    while (i < DATA_MEMORY)
    {
    printMemoryCell(&MEMORY->dataMemory[i]);
    printf("\n");
    ++i;
    }

}
void setDataMemoryCell(Memory* MEMORY, const Bit ADDRESS[ADDRESS_SIZE], const Bit* VALUE)
{
    if (!isAddressInRange(ADDRESS, DATA_ADDRESS_START, DATA_ADDRESS_END))
    {
        perror("Invalid");
        exit(EXIT_FAILURE);
    }

    MemoryCell* dataMemoryCell = getMemoryCell(MEMORY, ADDRESS);

    for (int i = 0; i < MEMORY_CELL_SIZE; ++i)
    {
        dataMemoryCell->bits[i].value = VALUE[i].value;
    }
}
void decreaseStackPointer(Memory* MEMORY)
{
    
    if (toDecimal(MEMORY->stackPointer->bits, 0, REGISTER_SIZE, false) <= STACK_ADDRESS_START)
    {
        perror("Stack has very less number of elements");
        exit(EXIT_FAILURE);
    }

    decrementBitArray(MEMORY->stackPointer->bits, REGISTER_SIZE);
}

void increaseStackPointer(Memory* MEMORY)
{
   
    if (toDecimal(MEMORY->stackPointer->bits, 0, REGISTER_SIZE, false) > STACK_ADDRESS_END)
    {
        perror("Stack has very less number of elements!");
        exit(EXIT_FAILURE);
    }

    incrementBitArray(MEMORY->stackPointer->bits, REGISTER_SIZE);
}
static bool isAddressInRange(const Bit ADDRESS[ADDRESS_SIZE], int start, int end)
{
    int i = 0;
    while (i < ADDRESS_SIZE)
   {
    if (ADDRESS[i].value != ((start >> (ADDRESS_SIZE - 1 - i)) & 1))
    {
        return 0; 
    }
    ++i;
   }
return 1;
}

int calculateMemoryIndex(const Bit ADDRESS[ADDRESS_SIZE])
{
  

    int index = toDecimal(ADDRESS, 0, REGISTER_SIZE, false);
    if (index >= PROGRAM_MEMORY)
    {
        index = index % ADDRESS_SIZE;
    }
   
    return index - 1; 
}

MemoryCell* getMemoryCell(Memory* MEMORY, const Bit ADDRESS[ADDRESS_SIZE])
{
    if (isAddressInRange(ADDRESS, PROGRAM_ADDRESS_START, PROGRAM_ADDRESS_END))
    {
        return &MEMORY->programMemory[calculateMemoryIndex(ADDRESS)];
    }
    if (isAddressInRange(ADDRESS, STACK_ADDRESS_START, STACK_ADDRESS_END))
    {
        return &MEMORY->stackMemory[calculateMemoryIndex(ADDRESS)];
    } 
    if (isAddressInRange(ADDRESS, DATA_ADDRESS_START, DATA_ADDRESS_END))
    {
        return &MEMORY->dataMemory[calculateMemoryIndex(ADDRESS)];
    }

    return NULL;
}

void pushStackMemory(Memory* MEMORY, const Register* REGISTER)
{
    if (toDecimal(MEMORY->stackPointer->bits, 0, REGISTER_SIZE, false) > STACK_ADDRESS_END)
    {
        perror("Stack has very less number of elements");
        exit(EXIT_FAILURE);
    }

    MemoryCell* stackTopCell = getMemoryCell(MEMORY, MEMORY->stackPointer->bits);
    int index = calculateMemoryIndex(MEMORY->stackPointer->bits);
    int i = 0;
    while (i < MEMORY_CELL_SIZE)
    {
    MEMORY->stackMemory[index].bits[i].value = REGISTER->bits[i].value;
    ++i;
}
    increaseStackPointer(MEMORY);
}

Bit* popStackMemory(Memory* MEMORY)
{
    if (toDecimal(MEMORY->stackPointer->bits, 0, REGISTER_SIZE, false) <= STACK_ADDRESS_START)
    {
        perror("Stack has very less number of elements");
        exit(EXIT_FAILURE);
    }

    decreaseStackPointer(MEMORY);
    MemoryCell* stackTopCell = getMemoryCell(MEMORY, MEMORY->stackPointer->bits);
    int index = calculateMemoryIndex(MEMORY->stackPointer->bits);
    for (int i = 0; i < MEMORY_CELL_SIZE; ++i)
    {
        MEMORY->stackMemory[index].bits[i].value = 0;
    }
    return stackTopCell->bits;
}

void loadBinaryToProgramMemory(Memory* MEMORY, const char* RELATIVE_FILE_PATH)
{
    FILE* file = fopen(RELATIVE_FILE_PATH, "r");

    if (file == NULL)
    {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    char line[MEMORY_CELL_SIZE + 1]; 


    int i = 0; 
    for (; fgets(line, sizeof(line), file) != NULL && i < PROGRAM_MEMORY; ++i)
    {
        if (strlen(line) <= 1)
        {
            continue;
        }
        int j = 0;
        while (j < MEMORY_CELL_SIZE && line[j] != '\n')
        {
            switch(line[j])
            {
                case '0':
                    MEMORY->programMemory[i].bits[j].value = 0;
                    break;
                case '1':
                    MEMORY->programMemory[i].bits[j].value = 1;
                    break;
                default:
                    printf("Found an invalid character '%c' in the file\n", line[j]);
                    exit(EXIT_FAILURE);
            }
            ++j;
        }
    }
    fclose(file);
    printf("operation successful\n");
}
void setDataMemoryCellByIndex(Memory *MEMORY, int INDEX, const Bit *VALUE)
{
    if (INDEX < 0 || INDEX >= DATA_MEMORY)
    {
        perror("Invalidity\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (i < MEMORY_CELL_SIZE)
    {
        MEMORY->dataMemory[INDEX].bits[i].value = VALUE[i].value;
        ++i;
    }
}
void deallocateMemory(Memory* MEMORY)
{
    free(MEMORY);
}