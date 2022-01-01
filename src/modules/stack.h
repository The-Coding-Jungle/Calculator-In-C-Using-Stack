#include <stdlib.h>
#include <stdio.h>

#define LOG_DEBUG_STACK 0

// This file will be used for logging.
const char* logFileName = "data/log.txt";

typedef enum { 
    false, 
    true 
} bool;

typedef struct {
    char* arr;
    int size, tos;
} stackChar;

stackChar* initStackChar() {
    stackChar* s = (stackChar*) malloc(sizeof(stackChar));
    s->arr = (char*)malloc(sizeof(char));
    s->size = 1;
    s->tos = -1;
    return s;
}

void displayStackChar(stackChar* s) {
    printf("Stack is: ");
    for (int i = 0; i <= s->tos; i++) {
        printf("%c ", s->arr[i]);
    }
    printf("\n");
}

void pushChar(stackChar* s, char x) {
    // If the stack is full, double the size of the stack.
    if (s->tos == s->size - 1) {
        s->size *= 2;
        s->arr = (char*)realloc(s->arr, s->size * sizeof(char));
    }

    #if LOG_DEBUG_STACK
        FILE* logFile = fopen(logFileName, "a");
        fprintf(logFile, "Pushing %c onto stack.\n", x);
        fclose(logFile);
    #endif

    s->arr[++s->tos] = x;
    #if LOG_DEBUG_STACK
        displayStackChar(s);
    #endif
}

char popChar(stackChar* s) {
    if (s->tos == -1) {
        FILE* f = fopen(logFileName, "a");
        fprintf(f, "Stack is empty so cannot pop. Returning a garbage value.\n");
        fclose(f);
        return -1;
    }

    #if LOG_DEBUG_STACK
        FILE* logFile = fopen(logFileName, "a");
        fprintf(logFile, "Popping %c from stack.\n", s->arr[s->tos]);
        fclose(logFile);
    #endif

    char toReturn = s->arr[s->tos];
    s->tos--;
    return toReturn;
}

char topChar(stackChar* s) {
    if (s->tos == -1) {
        FILE* f = fopen(logFileName, "a");
        fprintf(f, "Stack is empty so cannot top. Returning a garbage value.\n");
        fclose(f);
        return -1;
    }

    #if LOG_DEBUG_STACK
        FILE* logFile = fopen(logFileName, "a");
        fprintf(logFile, "Top of stack is %c.\n", s->arr[s->tos]);
        fclose(logFile);
    #endif

    return s->arr[s->tos];
}

bool isEmptyChar(stackChar* s) {
    return s->tos == -1;
}

void freeStackChar(stackChar* s) {
    free(s->arr);
    free(s);
}

typedef struct {
    double* arr;
    int size, tos;
} stackDouble;

stackDouble* initStackDouble() {
    stackDouble* s = (stackDouble*) malloc(sizeof(stackDouble));
    s->arr = (double*)malloc(sizeof(double));
    s->size = 1;
    s->tos = -1;
    return s;
}

void displayStackDouble(stackDouble* s) {
    if (s->tos == -1) {
        FILE* f = fopen(logFileName, "a");
        fprintf(f, "Stack is empty.\n");
        fclose(f);
        return;
    }

    #if LOG_DEBUG_STACK
        FILE* f = fopen(logFileName, "a");  
        fprintf(f, "Stack: ");
        for (int i = 0; i <= s->tos; i++) {
            fprintf(f, "%lf ", s->arr[i]);
        }
        fprintf(f, "\n");
        fclose(f);
    #endif
}

void pushDouble(stackDouble* s, double x) {
    // If the stack is full, double the size of the stack.
    if (s->tos == s->size - 1) {
        s->size *= 2;
        s->arr = (double*)realloc(s->arr, s->size * sizeof(double));
    }

    #if LOG_DEBUG_STACK
        FILE* logFile = fopen(logFileName, "a");
        fprintf(logFile, "Pushing %f onto stack.\n", x);
        displayStackDouble(s);
        fclose(logFile);
    #endif

    s->arr[++(s->tos)] = x;
}

double popDouble(stackDouble* s) {
    if (s->tos == -1) {
        FILE* f = fopen(logFileName, "a");
        fprintf(f, "Stack is empty so cannot pop. Returning a garbage value.\n");
        fclose(f);
        return -1;
    }

    #if LOG_DEBUG_STACK
        FILE* logFile = fopen(logFileName, "a");
        fprintf(logFile, "Popping %f from stack.\n", s->arr[s->tos]);
        displayStackDouble(s);
        fclose(logFile);
    #endif

    return s->arr[s->tos--];
}

double topDouble(stackDouble* s) {
    if (s->tos == -1) {
        FILE* f = fopen(logFileName, "a");
        fprintf(f, "Stack is empty so cannot top. Returning a garbage value.\n");
        fclose(f);
        return -1;
    }

    #if LOG_DEBUG_STACK
        FILE* logFile = fopen(logFileName, "a");
        fprintf(logFile, "Top of stack is %f.\n", s->arr[s->tos]);
        displayStackDouble(s);
        fclose(logFile);
    #endif

    return s->arr[s->tos];
}

bool isEmptyDouble(stackDouble* s) {
    return s->tos == -1;
}

void freeStackDouble(stackDouble* s) {
    free(s->arr);
    free(s);
}