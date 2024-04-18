#include "simulator.h"

int main()
{
    Simulator* a = initializeSimulator("testFile.txt");

    printProgramMemory(a->memoryManager);
}
