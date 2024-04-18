#include <stdio.h>
#include <stdlib.h>

int main()
{
    RegisterFile *registerFile = init();

    printRegisterFile(registerFile);

    const char *testABIs[] = {"zero", "s0", "a3"};

    Register *reg = getRegister(registerFile, "zero");
    Bit newBits[REGISTER_SIZE];
    for (int i = 0; i < REGISTER_SIZE; ++i)
    {
        newBits[i].value = rand() % 2;
    }
    setRegisterValue(reg, newBits);

    printRegister(reg);


    printf("Testing getAddress function:\n");
    for (int i = 0; i < sizeof(testABIs) / sizeof(testABIs[0]); ++i)
    {
        const char *abi = testABIs[i];
        const Bit *address = getAddress(registerFile, abi);
        printf("Successfully get address of register %s\n", abi);
        printf("Address: ");
        for (int i = 0; i < 5; ++i)
        {
            printf("%d", address[i].value);
        }
        printf("\n");
    }

    printf("Testing setBit function:\n");
    

    printRegisterFile(registerFile); 

    deallocateRegisters(registerFile);
    return 0;
}
