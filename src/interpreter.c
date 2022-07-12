#include <stdio.h>
#include <stdlib.h>

// Defining length of variable array
#define INTERPRETER_VARS_LENGTH 30000

// Defining instruction set constants
#define INTERPRETER_INSTRUCTION_FWD '>'
#define INTERPRETER_INSTRUCTION_BWD '<'
#define INTERPRETER_INSTRUCTION_INC '+'
#define INTERPRETER_INSTRUCTION_DEC '-'
#define INTERPRETER_INSTRUCTION_PUT '.'
#define INTERPRETER_INSTRUCTION_GET ','
#define INTERPRETER_INSTRUCTION_WLI '['
#define INTERPRETER_INSTRUCTION_WLO ']'

// Defining runtime constants
#define INTERPRETER_NO_JUMP -1

// Defining interpreter data structure
typedef struct {
    unsigned char vars[INTERPRETER_VARS_LENGTH]; // Variables array
    unsigned char *ptr; // Current variable pointer
    int position; // Current position in the variables array (redundant for readability)
    int *stack; // Stack of jump positions for while loops
    size_t stack_size; // Stack size
} interpreter_t;

// Signature of the function that will run a single instruction
void run_instruction(interpreter_t *interpreter, char instruction, int *index);

// Function that will run the code
void run(char *code) {
    // Starting interpreter
    int i = 0; // Current instruction index
    char ch; // Current instruction character
    interpreter_t interpreter = {
        .vars = {0}, // Initializing variables array with zeros
        .position = 0, // Initializing current position with zero
        .stack = NULL, // Initializing stack with NULL
        .stack_size = 0 // Initializing stack size with zero
    };

    // Initializing the current variable pointer to the beginning of the variables array
    interpreter.ptr = &interpreter.vars[interpreter.position];

    // Running the code instruction by instruction
    while ((ch = code[i]) != '\0') // Checking is the code is not finished
        run_instruction(&interpreter, ch, &i); // Running the current instruction
}

// Function that will run a single instruction
void run_instruction(interpreter_t *interpreter, char instruction, int *index) {
    // Checking instruction
    switch (instruction) {
        // Point to next variable
        case INTERPRETER_INSTRUCTION_FWD:
            // Incrementing current variable pointer by one, wrapping around if out of bounds
            if (interpreter->position == INTERPRETER_VARS_LENGTH - 1) interpreter->position = 0;
            else (interpreter->position)++;
            break;
        // Point to previous variable
        case INTERPRETER_INSTRUCTION_BWD:
            // Incrementing current variable pointer by one, wrapping around if out of bounds
            if (interpreter->position == 0) interpreter->position = INTERPRETER_VARS_LENGTH - 1;
            else (interpreter->position)--;
            break;
        // Increment current variable
        case INTERPRETER_INSTRUCTION_INC:
            // Incrementing current variable by one
            (*interpreter->ptr)++;
            break;
        // Decrement current variable
        case INTERPRETER_INSTRUCTION_DEC:
            // Decrementing current variable by one
            (*interpreter->ptr)--;
            break;
        // Print current variable as an ASCII character
        case INTERPRETER_INSTRUCTION_PUT:
            // Printing current variable as an ASCII character
            putchar(*(interpreter->ptr));
            break;
        // Read an ASCII character and store it in current variable
        case INTERPRETER_INSTRUCTION_GET:
            // Reading an ASCII character and storing it in current variable
            *(interpreter->ptr) = getchar();
            break;
        // Start while loop
        case INTERPRETER_INSTRUCTION_WLI:
            // Allocating memory for stack and assigning the last item to the current instruction index
            interpreter->stack = realloc(interpreter->stack, sizeof(int) * (++(interpreter->stack_size)));
            interpreter->stack[interpreter->stack_size - 1] = *index;
            break;
        // End while loop
        case INTERPRETER_INSTRUCTION_WLO:
            // Checking if the current variable is zero, if so, deleting last item of the stack, otherwise assigning the instruction index to the last item in the stack
            if (*(interpreter->ptr) == 0) interpreter->stack = realloc(interpreter->stack, sizeof(int) * (--(interpreter->stack_size)));
            else *index = interpreter->stack[interpreter->stack_size - 1];
            break;
    }

    // Assigning current variable pointer to the updated position in the variables array
    interpreter->ptr = &(interpreter->vars[interpreter->position]);
    // Incrementing instruction index by one
    (*index)++;
}