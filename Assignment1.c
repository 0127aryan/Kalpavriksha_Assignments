
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>  

#define MAX_LEN 100

int calculate(int a, int b, char op);
int evaluate(const char *expression);

int main() {
    char expression[MAX_LEN];

    printf("Enter a mathematical expression (e.g., 3 + 5 * 2): ");
    fgets(expression, sizeof(expression), stdin);
    
    expression[strcspn(expression, "\n")] = 0;

    int result = evaluate(expression);
    if (result == INT_MIN) {
        printf("Error: Division by zero.\n");
    } else {
        printf("Result: %d\n", result);
    }

    return 0;
}

int evaluate(const char *expression) {
    int result = 0;
    char op = '+'; 
    int currentNumber = 0;

    for (int i = 0; expression[i]; i++) {
        if (isdigit(expression[i])) {
            currentNumber = currentNumber * 10 + (expression[i] - '0');
        } else if (strchr("+-*/", expression[i])) {
            result = calculate(result, currentNumber, op);
            op = expression[i]; 
            currentNumber = 0; 
        }
    }
    
    result = calculate(result, currentNumber, op);

    return result;
}

int calculate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) return INT_MIN; 
            return a / b;
        default: return a; 
    }
}