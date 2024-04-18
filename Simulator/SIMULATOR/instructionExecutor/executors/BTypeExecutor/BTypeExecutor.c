#include "BTypeExecutor.h"
#include <stdio.h>
#include <stdlib.h>

bTypeExecutor* initialiseBTypeExecutor(Memory* MEMORY_MANAGER, RegisterFile* REGISTER_FILE, unsigned short* PROGRAM_COUNTER)
{
    bTypeExecutor* executor = (bTypeExecutor*)malloc(sizeof(bTypeExecutor));
    executor->memoryManager = MEMORY_MANAGER;
    executor->registerFile = REGISTER_FILE;
    executor->programCounter = PROGRAM_COUNTER;
    return executor;
}

void destroyBTypeExecutor(bTypeExecutor* EXECUTOR)
{
    free(EXECUTOR);
}

void branch(bTypeExecutor *EXECUTOR, bool CONDITION, short IMMEDIATE)
{
    if (CONDITION)
    {
        *EXECUTOR->programCounter += IMMEDIATE;
    }
    else
    {
        *EXECUTOR->programCounter += 4;
    }
}


void executeBTypeInstruction(bTypeExecutor *EXECUTOR, Bit *Instruction)
{
    short rs1 = toDecimal(Instruction, RS1_START, RS1_END, false);
    short rs2 = toDecimal(Instruction, RS2_START, RS2_END, false);
    short immediate = (toDecimal(Instruction, FIRST_HALF_IMMEDIATE_START, FIRST_HALF_IMMEDIATE_END, true) << FIRST_HALF_IMMEDIATE_SIZE) + toDecimal(Instruction, SECOND_HALF_IMMEDIATE_START, SECOND_HALF_IMMEDIATE_END, true);
    char funct3 = toDecimal(Instruction, FUNCT3_START, FUNCT3_END, false);
    short rs1Value = toDecimal(EXECUTOR->registerFile->registers[rs1].bits, 0, REGISTER_SIZE, true);
    short rs2Value = toDecimal(EXECUTOR->registerFile->registers[rs2].bits, 0, REGISTER_SIZE, true);
    short rs1ValueUnsigned = toDecimal(EXECUTOR->registerFile->registers[rs1].bits, 0, REGISTER_SIZE, false);
    short rs2ValueUnsigned = toDecimal(EXECUTOR->registerFile->registers[rs2].bits, 0, REGISTER_SIZE, false);

    if (funct3 == BEQ)
{
    branch(EXECUTOR, rs1Value == rs2Value, immediate);
}
else if (funct3 == BNE)
{
    branch(EXECUTOR, rs1Value != rs2Value, immediate);
}
else if (funct3 == BLT)
{
    branch(EXECUTOR, rs1Value < rs2Value, immediate);
}
else if (funct3 == BGE)
{
    branch(EXECUTOR, rs1Value >= rs2Value, immediate);
}
else if (funct3 == BLTU)
{
    branch(EXECUTOR, rs1ValueUnsigned < rs2ValueUnsigned, immediate);
}
else if (funct3 == BGEU)
{
    branch(EXECUTOR, rs1ValueUnsigned >= rs2ValueUnsigned, immediate);
}
else
{
    perror("Error: unknown funct3");
    exit(EXIT_FAILURE);
}

}


