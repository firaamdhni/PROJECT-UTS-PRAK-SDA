#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Struktur stack
typedef struct {
    char items[MAX][MAX];
    int top;
} Stack;

// Fungsi Stack
void initialize(Stack *s) { s->top = -1; }
int isEmpty(Stack *s) { return s->top == -1; }
void push(Stack *s, char *item) { if (s->top < MAX - 1) strcpy(s->items[++(s->top)], item); }
char* pop(Stack *s) { return isEmpty(s) ? "" : s->items[(s->top)--]; }
char* peek(Stack *s) { return isEmpty(s) ? "" : s->items[s->top]; }

// Cek apakah karakter adalah operator
int isOperator(char c) { return (c == '+' || c == '-' || c == '*' || c == '/'); }

// Cek prioritas operator
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Cek apakah ekspresi infix valid
int isValidInfix(char *exp) {
    int operand = 0, operator = 0, len = strlen(exp);
    for (int i = 0; i < len; i++) {
        if (isalnum(exp[i])) operand++;
        else if (isOperator(exp[i])) operator++;
    }
    return (operand > operator); // Operand harus lebih banyak atau sama
}
