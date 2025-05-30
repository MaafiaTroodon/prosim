#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    DOOP, BLOCK, LOOP, END, HALT
} PrimitiveType;

typedef struct {
    PrimitiveType type;
    int value;
} Instruction;

typedef struct {
    int start_index;
    int remaining;
} LoopFrame;

#define MAX_INSTRUCTIONS 10000
#define MAX_LOOP_DEPTH   100

Instruction program[MAX_INSTRUCTIONS];
LoopFrame loop_stack[MAX_LOOP_DEPTH];
int loop_top = -1;

int clock_time = 0;
int doop_count = 0, doop_time = 0;
int block_count = 0, block_time = 0;

PrimitiveType get_type(char *word) {
    if (strcmp(word, "DOOP") == 0) return DOOP;
    if (strcmp(word, "BLOCK") == 0) return BLOCK;
    if (strcmp(word, "LOOP") == 0) return LOOP;
    if (strcmp(word, "END") == 0) return END;
    if (strcmp(word, "HALT") == 0) return HALT;
    fprintf(stderr, "Unknown primitive: %s\n", word);
    exit(1);
}

void push_loop(int start, int times) {
    if (loop_top >= MAX_LOOP_DEPTH - 1) {
        fprintf(stderr, "Loop stack overflow\n");
        exit(1);
    }
    loop_top++;
    loop_stack[loop_top].start_index = start;
    loop_stack[loop_top].remaining = times;
}

int main() {
    char name[20];
    int num_primitives;

    // Read program name and number of primitives
    scanf("%s %d", name, &num_primitives);

    // Read all instructions
    for (int i = 0; i < num_primitives; i++) {
        char instr[10];
        scanf("%s", instr);
        program[i].type = get_type(instr);

        if (program[i].type == DOOP || program[i].type == BLOCK || program[i].type == LOOP) {
            scanf("%d", &program[i].value);
        } else {
            program[i].value = 0;
        }
    }

    int ip = 0;
    while (ip < num_primitives) {
        Instruction current = program[ip];

        switch (current.type) {
            case DOOP:
                printf("%05d: DOOP\n", clock_time);
                clock_time += current.value;
                doop_count++;
                doop_time += current.value;
                ip++;
                break;
            case BLOCK:
                printf("%05d: BLOCK\n", clock_time);
                clock_time += current.value;
                block_count++;
                block_time += current.value;
                ip++;
                break;
            case LOOP:
                push_loop(ip + 1, current.value);
                ip++;
                break;
            case END: {
                if (loop_top < 0) {
                    fprintf(stderr, "Unmatched END\n");
                    exit(1);
                }
                LoopFrame frame = loop_stack[loop_top--];
                frame.remaining--;
                if (frame.remaining > 0) {
                    push_loop(frame.start_index, frame.remaining);
                    ip = frame.start_index;
                } else {
                    ip++;
                }
                break;
            }
            case HALT:
                printf("%05d: HALT\n", clock_time);
                ip = num_primitives; // Terminate
                break;
        }
    }

    // Final stats
    printf("\n");
    printf("DOOP count : %d\n", doop_count);
    printf("DOOP time  : %d\n", doop_time);
    printf("BLOCK count: %d\n", block_count);
    printf("BLOCK time : %d\n", block_time);

    return 0;
}
