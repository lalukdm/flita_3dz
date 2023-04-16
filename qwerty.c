#include <stdio.h>
#include <stdlib.h>

int main() {
    char expr[100]; // array to store expression
    fgets(expr, 100, stdin); // read input from user
    
    int i = 0; // counter for expression
    int num_stack[100]; // array to store numbers
    char op_stack[100]; // array to store operators
    int num_top = -1; // index of top of num_stack
    int op_top = -1; // index of top of op_stack
    
    while (expr[i] != '\0') {
        if (expr[i] >= '0' && expr[i] <= '9') {
            // if the current character is a digit, read the entire number
            int num = 0;
            while (expr[i] >= '0' && expr[i] <= '9') {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            num_stack[++num_top] = num;
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            // if the current character is an operator, push it onto the op_stack
            op_stack[++op_top] = expr[i];
            i++;
        }
        else if (expr[i] == ' ') {
            // ignore whitespace
            i++;
        }
        else {
            // if the current character is not a digit, operator, or whitespace, print an error message and exit
            printf("Invalid character: %c\n", expr[i]);
            exit(1);
        }
    }
    
    // evaluate the expression
    while (op_top >= 0) {
        char op = op_stack[op_top--];
        int num2 = num_stack[num_top--];
        int num1 = num_stack[num_top--];
        int result;
        switch (op) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                result = num1 / num2;
                break;
        }
        num_stack[++num_top] = result;
    }
    
    // print the result
    printf("%d\n", num_stack[num_top]);
    
    return 0;
}