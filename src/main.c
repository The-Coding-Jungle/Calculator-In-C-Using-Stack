#include "modules/evaluate.h"

#define MAX_EXPRESSION_LENGTH 100

void makeLower(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
        i++;
    }
}

int main() {
    char expression[MAX_EXPRESSION_LENGTH];

    while (true){
        printf("Enter an expression: ");
        scanf("%s", expression);

        makeLower(expression);
        // Making the expression lowercase to compare commands easily.

        if (strcmp(expression, "exit") == 0) {
            break;
        }

        if (strcmp(expression, "clear") == 0) {
            #if defined(_WIN32) || defined(__CYGWIN__)
                system("cls");
            #else 
                system("clear");
            #endif
            continue;
        }

        printf("%s\n", evaluate(expression));
    }
    

    return 0;
}