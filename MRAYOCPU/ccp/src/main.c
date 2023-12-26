#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_LINE_LENGTH 256
#define MAX_REGISTERS 10

typedef struct {
    char name[16];
    uint8_t id;
} RegisterMapping;

typedef struct {
    char mnemonic[16];
    uint8_t opcode;
    int numOperands;
    int flagOperandIndex;  // Index of the operand used for flag assignment (-1 if not applicable)
} InstructionMapping;

InstructionMapping instructionMap[] = {
    {"ADD", 0x10, 3, -1},
    {"SUB", 0x20, 3, -1},
    {"INC", 0x30, 2, -1},
    {"DEC", 0x40, 2, -1},
    {"AND", 0x50, 3, -1},
    {"OR", 0x60, 3, -1},
    {"XOR", 0x70, 3, -1},
    {"MOV", 0x80, 4, 1},  // Assuming operand1 is used for flag assignment
    {"DISPLAY", 0x90, 2, 0},  // Assuming operand0 is used for flag assignment
    // Add more instructions and their opcode mappings
};

RegisterMapping registerMap[] = {
    {"ZERO", 0},
    {"r1", 1},
    {"r2", 2},
    {"r3", 3},
    {"r4", 4},
    {"r5", 5},
    {"r6", 6},
    {"r7", 7},
    {"r8", 8},
    {"r9", 9},
    {"r10", 10},
};

uint8_t getRegisterId(char* reg) {
    int numRegisters = sizeof(registerMap) / sizeof(RegisterMapping);
    for (int i = 0; i < numRegisters; i++) {
        if (strcmp(reg, registerMap[i].name) == 0) {
            return registerMap[i].id;
        }
    }
    return (uint8_t)-1;  // Invalid register
}

int main() {
    char line[MAX_LINE_LENGTH];
    char mnemonic[16], operand1[16], operand2[16], destination[16];
    uint8_t opcode, flag;
    uint8_t operand1Id, operand2Id, destinationId;

    while (fgets(line, sizeof(line), stdin) != NULL) {
        // Parse the assembly instruction
        if (sscanf(line, "%s , %s %s, %s", mnemonic, operand1, operand2, destination) != 4) {
            printf("Error: Invalid assembly instruction format\n");
            continue;
        }

        // Lookup the opcode and number of operands for the given mnemonic
        opcode = 0;  // Default opcode
        int numInstructions = sizeof(instructionMap) / sizeof(InstructionMapping);
        int i;
        for (i = 0; i < numInstructions; i++) {
            if (strcmp(mnemonic, instructionMap[i].mnemonic) == 0) {
                opcode = instructionMap[i].opcode;
                break;
            }
        }

        // Get the register IDs for the operands and destination
        operand1Id = getRegisterId(operand1);
        operand2Id = getRegisterId(operand2);
        destinationId = getRegisterId(destination);

        // Validate register IDs
        if (operand1Id == (uint8_t)-1 || operand2Id == (uint8_t)-1 || destinationId == (uint8_t)-1) {
            printf("Error: Invalid register\n");
            continue;
        }

        // Assign flag value if applicable
        if (instructionMap[i].flagOperandIndex >= 0 && instructionMap[i].flagOperandIndex < instructionMap[i].numOperands) {
            // Get the flag operand ID
            uint8_t flagOperandId;
            switch (instructionMap[i].flagOperandIndex) {
                case 0:
                    flagOperandId = operand1Id;
                    break;
                case 1:
                    flagOperandId = operand2Id;
                    break;
                // Add more cases for additional flag operand indices
            }

            // Assign flag value based on the flag operand ID
            flag = (flagOperandId > MAX_REGISTERS) ? 1 : 0;
        } else {
            flag = 0;  // Default flag value
        }

        // Generate machine code
        uint32_t machineCode = (opcode << 28) | (flag << 24) | (operand1Id << 16) | (operand2Id << 8) | destinationId;

        // Print the machine code
        printf("%08X\n", machineCode);
    }

    return 0;
}

