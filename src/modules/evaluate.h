#include "stack.h"
#include <math.h>
#include <string.h>

#define ANSWER_STRING_LENGTH 100

const char VALID_OPERATORS[] = {'+', '-', '*', '/', '^'};
const int NUMBER_OF_OPERATORS = sizeof (VALID_OPERATORS) / sizeof (char);

int getPriority(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

double solve(char op, double a, double b) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '^':
            return pow(a, b);
        default:
            return 0;
    }
}

char* removeSpaces(char* expression, int* newLen) {
    int len = strlen(expression);
    int i = 0;
    int j = 0;
    char* newExpression = (char*) malloc(sizeof (char) * len);
    while (i < len) {
        if (expression[i] != ' ' && expression[i] != '\t' && expression[i] != '\n') {
            newExpression[j] = expression[i];
            j++;
        }
        i++;
    }
    *newLen = j;
    return newExpression;
}

int parseDouble(char* expression, int len, int i, double* result) {
    int j = i;
    int k = 0;
    char* number = (char*) malloc(sizeof (char) * ANSWER_STRING_LENGTH);
    while (j < len && (expression[j] >= '0' && expression[j] <= '9' || expression[j] == '.')) {
        number[k] = expression[j];
        k++;
        j++;
    }

    number[k] = '\0';
    *result = atof(number); // Parses the string to a double
    return j;
}

bool isValidOperator(char c) {
    for (int i = 0; i < NUMBER_OF_OPERATORS; i++) {
        if (c == VALID_OPERATORS[i]) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Evaluates an infix expression.
 * 
 * Assumptions:
 * 1. Arugments are of double type.
 * 2. Spaces are allowed but will be ignored.
 * 
 * Rules:
 * 1. We will use a stack to store the operators and one for operands.
 * 2. '(' will be pushed to the stack.
 * 3. If we see ')' then we evaluate till '('.
 * 4. In case, operator at top of the stack has higher priority than the current operator, then evaluate.
 * 5. Else, push.
 * 6. If stack is empty, push the operator. 
 * 7. If operand is encountered, push to the stack.
 * 8. Operators will be single letter chars.
 * 9. INVALID_EXPRESSION will be returned if the expression is invalid.
 * 
 * @param expression 
 * @return char* 
 */
char* evaluate(char* expression) {
    int len;
    expression = removeSpaces(expression, &len);
    // We remove all the spaces from the expression firstly because is easier without them.

    stackChar* operators = initStackChar();
    stackDouble* operands = initStackDouble();

    int i = 0;

    while (i < len) {
        if ('0' <= expression[i] && expression[i] <= '9') {
            double val = 0;
            i = parseDouble(expression, len, i, &val);
            pushDouble(operands, val);
            continue;
        } else if (expression[i] == '(') {
            pushChar(operators, expression[i]);
        } else if (expression[i] == ')') {
            while (topChar(operators) != '(') {
                double a = popDouble(operands);
                double b = popDouble(operands);
                double c = 0;
                char op = popChar(operators);
                c = solve(op, a, b);
                pushDouble(operands, c);
            }
            popChar(operators);
        } else if (expression[i] == '-') {
            if (i == 0 || !('0' <= expression[i - 1] && expression[i] <= '9')) {
                // This is negative number.
                double val;
                i++;
                i = parseDouble(expression, len, i + 1, &val);
                pushDouble(operands, -1 * val);
                continue;
            } else {
                // '-' is an operator.
                while (!isEmptyChar(operators) && getPriority(topChar(operators)) >= getPriority(expression[i])) {
                    double a = popDouble(operands);
                    double b = popDouble(operands);
                    double c = 0;
                    char op = popChar(operators);
                    c = solve(op, a, b);
                    pushDouble(operands, c);
                }
                pushChar(operators, expression[i]);
            }
        } else if (isValidOperator(expression[i])) {
            while (!isEmptyChar(operators) && getPriority(topChar(operators)) >= getPriority(expression[i])) {
                double a = popDouble(operands);
                double b = popDouble(operands);
                double c = 0;
                char op = popChar(operators);
                c = solve(op, a, b);
                pushDouble(operands, c);
            }
            pushChar(operators, expression[i]);
        } else {
            return "INVALID_EXPRESSION";
        }
        i++;
    }

    while (!isEmptyChar(operators)) {
        double a = popDouble(operands);
        double b = popDouble(operands);
        double c = 0;
        char op = popChar(operators);
        c = solve(op, a, b);
        pushDouble(operands, c);
    }

    double ans = popDouble(operands);

    free(operands);
    free(operators);

    char *ansStr = (char*) malloc(sizeof (char) * ANSWER_STRING_LENGTH);
    sprintf(ansStr, "%lf", ans);
    return ansStr;
}