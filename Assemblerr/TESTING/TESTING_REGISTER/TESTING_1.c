#include <stdio.h>

int main() {

    RegisterFile *registerFile = init();
    
    static const char* abi[REGISTER_COUNT] = {
        "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1", 
        "a0", "a1", "a2", "a3", "s3", 
        "s4", "s5", "s6", "s7", "s8", "s9"
    };

    for (int i = 0; i < REGISTER_COUNT; ++i)
    {
        const char* currentABI = abi[i];
        printf("%s: ", currentABI);

        for (int j = 31; j >=0; --j)
        {
            printf("%d", registerFile->registers[i].bits[j].value);
        }
        printf("\n");
    }

    return 0;
}

