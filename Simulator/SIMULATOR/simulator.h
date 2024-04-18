#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "instructionExecutor/executorManager/executorManager.h"

#define PROGRAM_COUNTER_SCALE_FACTOR 4

Simulator* initializeSimulator();

void loadProgram(Simulator* SIMULATOR, const char* BINARY_FILE_PATH);

void printRegisters(const Simulator* SIMULATOR);

void printMemory(const Simulator* SIMULATOR);

void runSimulation(Simulator* SIMULATOR);

void deinitializeSimulator(Simulator* SIMULATOR);


typedef struct {
    Memory* memoryManager;
    RegisterFile* registerFile;
    const char* binaryFilePath;
    unsigned short* programCounter;
    ExecutorManager* executionManager;
} Simulator;


#endif 



