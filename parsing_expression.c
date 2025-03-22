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

// Fungsi konversi ekspresi
void reverseString(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

void infixToPostfix(char *exp, char *result) {
    Stack s;
    initialize(&s);
    int k = 0;
    for (int i = 0; exp[i]; i++) {
        if (isalnum(exp[i])) result[k++] = exp[i];
        else if (exp[i] == '(') push(&s, "(");
        else if (exp[i] == ')') {
            while (!isEmpty(&s) && strcmp(peek(&s), "(") != 0) result[k++] = pop(&s)[0];
            pop(&s);
        } else {
            while (!isEmpty(&s) && precedence(peek(&s)[0]) >= precedence(exp[i])) result[k++] = pop(&s)[0];
            char temp[2] = {exp[i], '\0'};
            push(&s, temp);
        }
    }
    while (!isEmpty(&s)) result[k++] = pop(&s)[0];
    result[k] = '\0';
}

void postfixToInfix(char *exp, char *result) {
    Stack s;
    initialize(&s);
    for (int i = 0; exp[i]; i++) {
        if (isalnum(exp[i])) {
            char operand[2] = {exp[i], '\0'};
            push(&s, operand);
        } else {
            char op2[MAX], op1[MAX], temp[MAX];
            strcpy(op2, pop(&s));
            strcpy(op1, pop(&s));
            sprintf(temp, "(%s%c%s)", op1, exp[i], op2);
            push(&s, temp);
        }
    }
    strcpy(result, pop(&s));
}

void infixToPrefix(char *exp, char *result) {
    reverseString(exp);
    for (int i = 0; exp[i]; i++) {
        if (exp[i] == '(') exp[i] = ')';
        else if (exp[i] == ')') exp[i] = '(';
    }
    infixToPostfix(exp, result);
    reverseString(result);
}

void prefixToInfix(char *exp, char *result) {
    Stack s;
    initialize(&s);
    reverseString(exp);
    for (int i = 0; exp[i]; i++) {
        if (isalnum(exp[i])) {
            char operand[2] = {exp[i], '\0'};
            push(&s, operand);
        } else {
            char op1[MAX], op2[MAX], temp[MAX];
            strcpy(op1, pop(&s));
            strcpy(op2, pop(&s));
            sprintf(temp, "(%s%c%s)", op1, exp[i], op2);
            push(&s, temp);
        }
    }
    strcpy(result, pop(&s));
}

void prefixToPostfix(char *exp, char *result) {
    char temp[MAX];
    prefixToInfix(exp, temp);
    infixToPostfix(temp, result);
}

void postfixToPrefix(char *exp, char *result) {
    char temp[MAX];
    postfixToInfix(exp, temp);
    infixToPrefix(temp, result);
}

// Fungsi untuk menangani konversi berdasarkan pilihan
void handleConversion(int choice, char *expression, char *result) {
    if (choice == 1) {
        if (!isValidInfix(expression)) {
            printf("Ekspresi yang Anda masukkan salah, masukkan kembali!\n");
            return;
        }
        infixToPostfix(expression, result);
    } else if (choice == 2) {
        postfixToInfix(expression, result);
    } else if (choice == 3) {
        if (!isValidInfix(expression)) {
            printf("Ekspresi yang Anda masukkan salah, masukkan kembali!\n");
            return;
        }
        infixToPrefix(expression, result);
    } else if (choice == 4) {
        prefixToInfix(expression, result);
    } else if (choice == 5) {
        prefixToPostfix(expression, result);
    } else if (choice == 6) {
        postfixToPrefix(expression, result);
    }
    printf("Hasil: %s\n", result);
}

// Menu utama program
void menu() {
    char expression[MAX], result[MAX];
    int choice;

    while (1) {
        printf("\nKonversi Ekspresi Aritmatika\n");
        printf("1. Infix ke Postfix\n");
        printf("2. Postfix ke Infix\n");
        printf("3. Infix ke Prefix\n");
        printf("4. Prefix ke Infix\n");
        printf("5. Prefix ke Postfix\n");
        printf("6. Postfix ke Prefix\n");
        printf("7. Keluar\n");
        printf("Pilihan: ");

        if (scanf("%d", &choice) != 1) {
            printf("Menu yang Anda pilih tidak valid, coba lagi.\n");
            while (getchar() != '\n');  // Membersihkan buffer input
            continue;
        }

        if (choice == 7) break;
        if (choice < 1 || choice > 6) {
            printf("Menu yang Anda pilih tidak terdaftar, coba lagi.\n");
            continue;
        }

        getchar();
        printf("Masukkan ekspresi: ");
        fgets(expression, MAX, stdin);
        expression[strcspn(expression, "\n")] = 0;

        handleConversion(choice, expression, result);
    }
}

int main() {
    menu();
    return 0;
}
