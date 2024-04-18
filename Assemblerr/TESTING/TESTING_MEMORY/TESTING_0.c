#include <stdio.h>
#include "../../src/memory/memory.h"

int main()
{
    Memory* memory = allocateMemory();

    if (memory == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Testing memory allocation: Pass\n");

    printProgramMemory(memory);
    printStackMemory(memory);
    printDataMemory(memory);

 

    deallocateMemory(memory);

    return 0;
}
