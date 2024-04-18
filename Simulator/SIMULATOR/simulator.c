#include <stdio.h>
#include <stdlib.h>
#include "simulator.h"
#include "instructionExecutor/executorManager/executorManager.h"


Simulator* initializeSimulator()
{
    Simulator* simulator = (Simulator*) malloc(sizeof(Simulator));
    
    if (simulator == NULL)
    {
        perror("Error: Memory allocation failed for Simulator.\n") ;
        exit(EXIT_FAILURE);
    }
    
    simulator->registerFile = initializeRegisters();
    if (simulator->registerFile == NULL)
    {
        perror("Error: Register File initialization failed.\n");
        free(simulator);
        exit(EXIT_FAILURE);
    }

    simulator->memoryManager = allocateMemory(getRegister(simulator->registerFile, "sp"));
    if (simulator->memoryManager == NULL)
    {
        perror("Error: Memory manager initialization failed.");
        free(simulator->registerFile);
        free(simulator);
        return NULL;
    }

    unsigned short programCounter = 0;
    simulator->programCounter = &programCounter;
    if (simulator->programCounter == NULL)
    {
        perror("Error: Program counter initialization failed.");
        free(simulator->memoryManager);
        free(simulator->registerFile);
        free(simulator);
        return NULL;
    }
    *simulator->programCounter = 0;

    simulator->executionManager = initializeExecutorManager(simulator->memoryManager, simulator->registerFile, simulator->programCounter);
    if (simulator->executionManager == NULL)
    {
        perror("Error: Failed to initialize executor manager");
        free(simulator->memoryManager);
        free(simulator->registerFile);
        free(simulator);
    }

    return simulator;
}


void runSimulation(Simulator *SIMULATOR)
{
   for (; !(*SIMULATOR->programCounter >= PROGRAM_MEMORY); )
{
    Bit* instruction = getMemoryCell(SIMULATOR->memoryManager, SIMULATOR->memoryManager->programMemory[*SIMULATOR->programCounter/PROGRAM_COUNTER_SCALE_FACTOR].bits)->bits;
    findAndExecute(SIMULATOR->executionManager, instruction);
    printRegisters(SIMULATOR);
}

    printMemory(SIMULATOR);
}
