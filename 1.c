#include <stdio.h>
#include <string.h>

void rstrip(char* str, int* len) {
    int i = *len - 1;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
        str[i] = '\0';
        i--;
    }
    *len = i + 1;
}

int main() {
    char* expression;
    int size = 100;
    getline(&expression, &size, stdin);
    size = strlen(expression);
    expression[size] = '\0';
    rstrip(expression, &size);
 
    if (strcmp(expression, "exit") == 0) {
        printf("Exiting...\n");
    }

    return 0;
}