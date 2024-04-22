#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//후위식 계산 프로그램
#define MAX_STACK_SIZE 10

typedef int element;
typedef struct Stacktype {
    //element deta[];
    element* data;
    int capacity;
    int top;
} StackType;
// create : 이미 만들었음, StackType의 변수를 선언하면 만들어짐
// delete : 할수 없음
//init
void init(StackType* sptr, int ofs) {
    sptr->data = (element*)malloc(sizeof(element) * ofs);
    sptr->top = -1;
    sptr->capacity = ofs;
}
//is_full
int is_full(StackType* sptr) {
    return sptr->top == sptr->capacity - 1;
}
//is_empty
int is_empty(StackType* sptr) {
    return sptr->top == -1;
}
//push
void push(StackType* sptr, element item) {
    if (is_full(sptr)) {
        fprintf(stderr, "Stack is full\n");
        return;
    }
    sptr->data[++sptr->top] = item;
}

element pop(StackType* sptr) {
    if (is_empty(sptr)) {
        fprintf(stderr, "Stack is empty\n");
        return -1; 
    }
    return sptr->data[sptr->top--];
}

element peek(StackType* sptr) {
    if (is_empty(sptr)) {
        fprintf(stderr, "Stack is empty\n");
        return -1; 
    }
    return sptr->data[sptr->top];
}
//계산
int eval(char expr[]) {
    int len;
    StackType s;
    init(&s, MAX_STACK_SIZE);

    len = strlen(expr);
    for (int i = 0; i < len; i++) {
        int ch = expr[i];
        int value;
        int op1, op2;

        if ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '/')) {
            op1 = pop(&s);
            op2 = pop(&s);
            switch (ch) {
            case '+': push(&s, op2 + op1); break;
            case '-': push(&s, op2 - op1); break;
            case '*': push(&s, op2 * op1); break;
            case '/':
                if (op1 == 0) {
                    fprintf(stderr, "Division by zero\n");
                    return -1; // 에러
                }
                push(&s, op2 / op1);
                break;
            default: break;
            }
        }
        else if ((ch >= '0') && (ch <= '9')) {
            value = ch - '0';
            push(&s, value);
        }
    }
    int result = pop(&s);
    free(s.data); 
    return result;
}

int main() {
    char expression[MAX_STACK_SIZE * 2]; 
    int result;

    printf("postfix Expression: ");
    fgets(expression, sizeof(expression), stdin);

    result = eval(expression);
    if (result != -1) {
        printf("Result: %d\n", result);
    }

    return 0;
}
