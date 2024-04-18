#include <stdio.h>

int main() {
    RegisterFile *registerFile = init();

    for (int i = 0; i < 32; ++i) {
        printf("Register %d: ", i);
        for (int j = 31; j >= 0; --j) {
            printf("%d", registerFile->registers[i].bits[j].value);
        }
        printf("\n");
    }

    deallocateRegisters(registerFile);

    return 0;
}

