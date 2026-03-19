#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} NumStack;

typedef struct {
    char data[MAX_STACK_SIZE];
    int top;
} OpStack;

void initNumStack(NumStack *stack) {
    stack->top = -1;
}

int isNumStackEmpty(NumStack *stack) {
    return stack->top == -1;
}

int pushNum(NumStack *stack, int num) {
    if (stack->top >= MAX_STACK_SIZE - 1) {
        printf("错误：操作数栈溢出！\n");
        return 0;
    }
    stack->data[++stack->top] = num;
    return 1;
}

int popNum(NumStack *stack, int *num) {
    if (isNumStackEmpty(stack)) {
        printf("错误：操作数栈为空，无法弹栈！\n");
        return 0;
    }
    *num = stack->data[stack->top--];
    return 1;
}

void initOpStack(OpStack *stack) {
    stack->top = -1;
}

int isOpStackEmpty(OpStack *stack) {
    return stack->top == -1;
}

int pushOp(OpStack *stack, char op) {
    if (stack->top >= MAX_STACK_SIZE - 1) {
        printf("错误：运算符栈溢出！\n");
        return 0;
    }
    stack->data[++stack->top] = op;
    return 1;
}

int popOp(OpStack *stack, char *op) {
    if (isOpStackEmpty(stack)) {
        printf("错误：运算符栈为空，无法弹栈！\n");
        return 0;
    }
    *op = stack->data[stack->top--];
    return 1;
}

int getTopOp(OpStack *stack, char *op) {
    if (isOpStackEmpty(stack)) {
        *op = '\0';
        return 0;
    }
    *op = stack->data[stack->top];
    return 1;
}

int getOpPriority(char op) {
    switch (op) {
        case '(': return 0;
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default: return -1;
    }
}

int calculate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                printf("错误：除数为0！\n");
                return 0;
            }
            return a / b;
        default:
            printf("错误：不支持的运算符 %c！\n", op);
            return 0;
    }
}

int parseInteger(const char *expr, int index, int *num) {
    int start = index;
    int is_negative = 0;

    if (expr[index] == '-') {
        is_negative = 1;
        index++;
        if (!isdigit(expr[index])) {
            printf("错误：负号 %c 后无有效数字！\n", expr[start]);
            return -1;
        }
    }

    *num = 0;
    while (isdigit(expr[index])) {
        *num = *num * 10 + (expr[index] - '0');
        index++;
    }

    if (is_negative) {
        *num = -(*num);
    }

    char next_char = expr[index];
    if (!(next_char == '+' || next_char == '-' || next_char == '*' || next_char == '/' || 
          next_char == ')' || next_char == '\0' || isspace(next_char))) {
        printf("错误：非法字符 %c（位置：%d）！\n", next_char, index);
        return -1;
    }

    return index;
}

int solveIntegerExpr(const char *expr, int *result) {
    NumStack num_stack;
    OpStack op_stack;
    initNumStack(&num_stack);
    initOpStack(&op_stack);

    int len = strlen(expr);
    int index = 0;
    char current_op;

    while (index < len) {
        if (isspace(expr[index])) {
            index++;
            continue;
        }

        if (isdigit(expr[index]) || (expr[index] == '-' && (index == 0 || expr[index-1] == '(' || getOpPriority(expr[index-1]) != -1))) {
            int num;
            int next_idx = parseInteger(expr, index, &num);
            if (next_idx == -1) return 0;
            if (!pushNum(&num_stack, num)) return 0;
            index = next_idx;
            continue;
        }

        if (expr[index] == '(') {
            if (!pushOp(&op_stack, '(')) return 0;
            index++;
            continue;
        }

        if (expr[index] == ')') {
            getTopOp(&op_stack, &current_op);
            while (current_op != '(' && current_op != '\0') {
                int b, a, res;
                if (!popNum(&num_stack, &b) || !popNum(&num_stack, &a) || !popOp(&op_stack, &current_op)) {
                    printf("错误：表达式语法错误（操作数/运算符不足）！\n");
                    return 0;
                }
                res = calculate(a, b, current_op);
                if (b == 0 && current_op == '/') return 0;
                if (!pushNum(&num_stack, res)) return 0;
                getTopOp(&op_stack, &current_op);
            }
            if (current_op == '\0') {
                printf("错误：右括号不匹配！\n");
                return 0;
            }
            popOp(&op_stack, &current_op);
            index++;
            continue;
        }

        if (getOpPriority(expr[index]) != -1) {
            while (!isOpStackEmpty(&op_stack)) {
                getTopOp(&op_stack, &current_op);
                if (current_op == '(') break;
                if (getOpPriority(current_op) >= getOpPriority(expr[index])) {
                    int b, a, res;
                    if (!popNum(&num_stack, &b) || !popNum(&num_stack, &a) || !popOp(&op_stack, &current_op)) {
                        printf("错误：表达式语法错误（操作数/运算符不足）！\n");
                        return 0;
                    }
                    res = calculate(a, b, current_op);
                    if (b == 0 && current_op == '/') return 0;
                    if (!pushNum(&num_stack, res)) return 0;
                } else {
                    break;
                }
            }
            if (!pushOp(&op_stack, expr[index])) return 0;
            index++;
            continue;
        }

        printf("错误：非法字符 %c（位置：%d）！\n", expr[index], index);
        return 0;
    }

    while (!isOpStackEmpty(&op_stack)) {
        getTopOp(&op_stack, &current_op);
        if (current_op == '(') {
            printf("错误：左括号不匹配！\n");
            return 0;
        }
        int b, a, res;
        if (!popNum(&num_stack, &b) || !popNum(&num_stack, &a) || !popOp(&op_stack, &current_op)) {
            printf("错误：表达式语法错误（操作数/运算符不足）！\n");
            return 0;
        }
        res = calculate(a, b, current_op);
        if (b == 0 && current_op == '/') return 0;
        if (!pushNum(&num_stack, res)) return 0;
    }

    if (num_stack.top != 0) {
        printf("错误：表达式语法错误（操作数数量异常）！\n");
        return 0;
    }

    *result = num_stack.data[num_stack.top];
    return 1;
}

int main() {
    const char *test_cases[] = {
        "(12+34)*5-6",
        "100-(20+30)*2",
        "((7+8)*2-3)/5",
        "123-(45+6*7)",
        "50/(5+5)*3",
        "10/(2-2)",
        "(12+34*5",
        "12+34)*5",
        "12a+34",
        " -9+(10-2)*4 ",
        NULL
    };

    printf("===== 计算器高级要求测试（有括号、整数） =====\n");
    for (int i = 0; test_cases[i] != NULL; i++) {
        int result;
        printf("\n表达式：%s\n", test_cases[i]);
        if (solveIntegerExpr(test_cases[i], &result)) {
            printf("计算结果：%d\n", result);
        } else {
            printf("计算失败！\n");
        }
    }

    char user_expr[100];
    printf("\n\n请输入整数表达式（支持括号、+-*/）：");
    fgets(user_expr, sizeof(user_expr), stdin);
    user_expr[strcspn(user_expr, "\n")] = '\0';
    int user_result;
    if (solveIntegerExpr(user_expr, &user_result)) {
        printf("您输入的表达式结果：%d\n", user_result);
    } else {
        printf("表达式计算失败！\n");
    }

    return 0;
} 