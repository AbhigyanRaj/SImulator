#define INSTRUCTIONS_H

#include "../register/registers.h"

struct InstructionType
{
  R_TYPE,
  I_TYPE,
  S_TYPE,
  B_TYPE,
  U_TYPE,
  J_TYPE,
  COMMENT
};

typedef struct 
{
  char *name;
  InstructionType type;
  Bit bits[7];
} Opcode;
struct Label
{
  char *name;
  bool isPresent;
};

typedef struct 
{
  Opcode opcode;
  Register *registers;
  Label label;
  Immediate *immediates;
  unsigned int position;
  Bit funct7[7];
    unsigned short elementCount[7];
} Instruction;

struct InputFile
{
    Instruction *instructions;
    unsigned int size;

};



char *readFile(const char *RELATIVE_FILE_PATH);

Instruction *assignInstruction(int *ASSEMBLY_CODE);

void writeFile(InputFile *INPUT);
