#ifndef EXECUTOR_MANAGER
#define EXECUTOR_MANAGER
typedef struct
{
    Memory* memoryManager;
    RegisterFile* registerFile;
    unsigned short* programCounter;
    rTypeExecutor* rTypeExecutor;
    iTypeExecutor* iTypeExecutor;
    sTypeExecutor* sTypeExecutor;
    bTypeExecutor* bTypeExecutor;
    uTypeExecutor* uTypeExecutor;
    jTypeExecutor* jTypeExecutor;
} ExecutorManager;

#define I_TYPE_LW 3
#define OPCODE_START 0
#define R_TYPE 51
#define INSTRUCTION_SIZE 32
#define I_TYPE_DEFAULT 19
#define OPCODE_END 6
#define I_TYPE_JUMP 103
#define B_TYPE 99
#define U_TYPE_1 55
#define S_TYPE 35
#define J_TYPE 111
#define U_TYPE_2 23
#define HALT 0

#include "../executors/RTypeExecutor/RTypeExecutor.h"
#include "../executors/JTypeExecutor/JTypeExecutor.h"
#include "../executors/BTypeExecutor/BTypeExecutor.h"
#include "../executors/UTypeExecutor/UTypeExecutor.h"
#include "../executors/ITypeExecutor/ITypeExecutor.h"
#include "../executors/STypeExecutor/STypeExecutor.h"
#include "../../memory/memory.h"

void destroyExecutorManager(ExecutorManager* EXECUTION_MANAGER);
void findAndExecute(ExecutorManager* EXECUTION_MANAGER, Bit INSTRUCTION[INSTRUCTION_SIZE]);
ExecutorManager* initializeExecutorManager(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* PROGRAM_COUNTER);
#endif
