#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_REGISTERS 16

typedef struct {
    int list[MAX_REGISTERS];
} Registers;

typedef struct {
    Registers *registers;
    int program_counter;
} Program;

typedef enum Opcode {
    PUSH, // PUSH <reg> <value>
    PRINT, // PRINT <reg>

    ADD, // ADD <reg1> <reg2>
    SUB, // SUB <reg1> <reg2>
    MUL, // MUL <reg1> <reg2>
    DIV, // DIV <reg1> <reg2>

    JMP, // JMP <adress>
    JZ, // JZ <reg> <adress> reg == 0
    JNZ, // JNZ <reg> <adress> reg != 0
    JG, // JG <reg> <adress> reg > 0
    JGE, // JGE <reg> <adress> reg >= 0
    JL, // JL <reg> <adress> reg < 0
    JLE, // JLE <reg> <adress> reg <= 0
} Opcode;

Program *init_program() {
    Program *program = (Program *)malloc(sizeof(Program));

    program->registers = (Registers *)malloc(sizeof(Registers));
    memset(program->registers->list, 0, sizeof(program->registers->list));

    program->program_counter = 0;

    return program;
}

int get_reg_num(char *str) {
    int len = strlen(str);
    char *nums = malloc(len);
    strcpy(nums, str + 1);
    int result = atoi(nums);
    free(nums);
    return result;
}

int opcode_arg_num(char *opcode) {
    if (strcmp(opcode, "PUSH") == 0\
    || strcmp(opcode, "ADD") == 0 || strcmp(opcode, "SUB") == 0\
    || strcmp(opcode, "MUL") == 0 || strcmp(opcode, "DIV") == 0) {
        return 2;
    }
    else if (strcmp(opcode, "PRINT") == 0) {
        return 1;
    }
    
    return 0;
}

Opcode get_opcode(char *str) {
    if (strcmp(str, "PUSH") == 0) return PUSH;
    else if (strcmp(str, "ADD") == 0) return ADD;
    else if (strcmp(str, "SUB") == 0) return SUB;
    else if (strcmp(str, "MUL") == 0) return MUL;
    else if (strcmp(str, "DIV") == 0) return DIV;
    else if (strcmp(str, "PRINT") == 0) return PRINT;
    
    printf("Err Get Opcode: Unkown Opcode");
    exit(1);
}

void exec_instruct(Program *program, Opcode instruct, char **args) {
    switch (instruct) {
        case PUSH: {
            int reg_num = get_reg_num(args[0]);
            int value = atoi(args[1]);
            program->registers->list[reg_num] = value;
        }; break;
        case ADD: {
            int reg_1 = get_reg_num(args[0]);
            int reg_2 = get_reg_num(args[1]);
            program->registers->list[reg_1] += program->registers->list[reg_2];
        }; break;
        case SUB: {
            int reg_1 = get_reg_num(args[0]);
            int reg_2 = get_reg_num(args[1]);
            program->registers->list[reg_1] -= program->registers->list[reg_2];
        }; break;
        case MUL: {
            int reg_1 = get_reg_num(args[0]);
            int reg_2 = get_reg_num(args[1]);
            program->registers->list[reg_1] *= program->registers->list[reg_2];
        }; break;
        case DIV: {
            int reg_1 = get_reg_num(args[0]);
            int reg_2 = get_reg_num(args[1]);
            if (program->registers->list[reg_1] == 0 || program->registers->list[reg_2] == 0) {
                printf("Err: Divide zero\n");
                return;
            }
            program->registers->list[reg_1] /= program->registers->list[reg_2];
        }; break;
        case PRINT: {
            int reg_num = get_reg_num(args[0]);
            printf("R%d: %d\n", reg_num, program->registers->list[reg_num]);
        }; break;
        default:
            printf("Err Exec Instruct: Unkown Opcode\n");
            exit(1);
    }
}

void exec_program(Program *program, const char *program_text) {    
    char *tokens_str = malloc(strlen(program_text) + 1);
    if (tokens_str == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    strcpy(tokens_str, program_text);

    char *token = strtok(tokens_str, " ");
    while (token != NULL) {
        char *opcode = token;
        int args_num = opcode_arg_num(token);
        
        char **args = malloc(args_num * sizeof(char *));

        for (int i = 0; i < args_num; i++) {
            token = strtok(NULL, " ");
            args[i] = malloc(strlen(token) + 1);
            strcpy(args[i], token);
        }
        exec_instruct(program, get_opcode(opcode), args);

        token = strtok(NULL, " ");
        free(args);
    }

    free(tokens_str);
}

int main(void) {
    printf("\nINTERPRETER START\n");
    printf("-----------------\n\n");
    Program *program = init_program();
    
    char *text = "\
        PUSH R0 5\
        PRINT R0\
        PRINT R12\
        PUSH R12 10\
        PRINT R12\
        ADD R0 R12\
        PRINT R0\
        PUSH R12 2\
        MUL R0 R12\
        PRINT R0\
        PUSH R12 30\
        PRINT R0\
        PRINT R12\
        DIV R12 R0\
        PRINT R12\
    ";

    exec_program(program, text);

    free(program);
    return 0;
}