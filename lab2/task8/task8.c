#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Stack {
    int maxSize;
    int top;
    char *items;
};

struct StackDouble {
    int maxSize;
    int top;
    double *items;
};

struct Stack *newStack(int capacity) {
    struct Stack *ptr = (struct Stack*) malloc(sizeof(struct Stack));

    ptr->maxSize = capacity;
    ptr->top = -1;
    ptr->items = (char*) malloc(sizeof(int) *capacity);
    
    return ptr;
}

struct StackDouble *newStackDouble(int capacity) {
    struct StackDouble *ptrDouble = (struct StackDouble*) malloc(sizeof(struct StackDouble));

    ptrDouble->maxSize = capacity;
    ptrDouble->top = -1;
    ptrDouble->items = (double*) malloc(sizeof(int) *capacity);
    
    return ptrDouble;
}

int isEmpty(struct Stack *ptr) {
    return ptr->top == -1;
}

int isEmptyDouble(struct StackDouble *ptrDouble) {
    return ptrDouble->top == -1;
}

int isFull(struct Stack *ptr) {
    return ptr->top == ptr->maxSize - 1;
}

int isFullDouble(struct StackDouble *ptrDouble) {
    return ptrDouble->top == ptrDouble->maxSize - 1;
}

int push(struct Stack *ptr, char x) {
    if (isFull(ptr)) {
        printf("Overflow\n");
        return 1;
    }

    ptr->items[++ptr->top] = x;
}

int pushDouble(struct StackDouble *ptrDouble, double x) {
    if (isFullDouble(ptrDouble)) {
        printf("Overflow\n");
        return 1;
    }

    ptrDouble->items[++ptrDouble->top] = x;
}

int pop(struct Stack *ptr) {
    if(isEmpty(ptr)) {
        printf("Underflow\n");
        return 1;
    }

    return ptr->items[ptr->top--];
}

int popDouble(struct StackDouble *ptrDouble) {
    if(isEmptyDouble(ptrDouble)) {
        printf("Underflow\n");
        return 1;
    }

    return ptrDouble->items[ptrDouble->top--];
}

int peek(struct Stack *ptr) {
     if(!isEmpty(ptr)) {
        return ptr->items[ptr->top];
    } else {
        return 1;
    }
}

int GetPiority(char oper) {
    switch (oper)
    {
        case '(': return 0;
        case ')': return 1;
        case '+': return 2;
        case '-': return 3;
        case '*': return 4;
        case '/': return 4;
        default: return 5;
    }
}

double calculate(char *str, int count) {
    double result = 0;
    struct StackDouble *nums = newStackDouble(count);

    for (int i = 0; i < strlen(str); i++) {
    
        if(isdigit(str[i])) {
            
            int indexStart = i;
            while (str[i] != ' ' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '('|| str[i] == ')') {
                i++;
                if (i == count) break;
            }
            int indexEnd = i;

            char num[indexEnd-indexStart];
            int indexNum = 0;
            for (int j = indexStart; j < indexEnd; j++) {
                num[indexNum] = str[j];
                indexNum++;
            }
            pushDouble(nums, atof(num));
            i--;
        
        } else if (str[i] != ' ' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '('|| str[i] == ')') {
            double a = popDouble(nums);
            double b = popDouble(nums);

            switch (str[i]) {
                case '+': result = b + a; break;
                case '-': result = b - a; break;
                case '*': result = b * a; break;
                case '/': result = b / a; break;
            }

            pushDouble(nums, result);
        }

    }
    return result;
}

char *GetExpression(char *str, int count) {
    char *output = (char*) malloc(count *sizeof(char));
    struct Stack *oper = newStack(count);
    int indexNum = 0;

    for (int i = 0; i < strlen(str); i++) {

        if (str[i] == ' ' || str[i] == '=') {
            continue;
        }

        if(isdigit(str[i])) {
            
            int indexStart = i;
            while (str[i] != ' ' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '(' || str[i] == ')') {
                i++;
                if (i == count) break;
            }
            int indexEnd = i;

            char num[indexEnd - indexStart];
            
            for (int j = indexStart; j < indexEnd; j++) {
                output[indexNum] = str[j];
                indexNum++;
            }

            output[indexNum] = ' '; 
            indexNum++;
            i--;
        }

        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '('|| str[i] == ')') {

            if (str[i] == '(') {
                push(oper, str[i]);
            } else if (str[i] == ')') {
                char ch = pop(oper);

                while (ch != '(') {
                    output[indexNum] = ch;
                    indexNum++;
                    output[indexNum] = ' ';
                    indexNum++;
                    ch = pop(oper);
                }

            } else {
                if (!isEmpty(oper)) {
                    if (GetPiority(str[i]) <= GetPiority(peek(oper))) {
                        output[indexNum] = pop(oper);
                        indexNum++;
                        output[indexNum] = ' ';
                        indexNum++;
                    } 
                }
                push(oper, str[i]);
            }
        }
    }

    while (!isEmpty(oper)) {
        output[indexNum] = pop(oper);
        indexNum++;
        output[indexNum] = ' ';
        indexNum++;
    }

    return output;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
		printf("Error, try again\n");
		return 1;
	}

    FILE *inputFile;
    inputFile = fopen(argv[1], "r");
     if (inputFile == NULL) {
        printf("Can`t open file\n");
        return 1;
    }

    char str[100];
    fgets(str, sizeof(str), inputFile);

    int count = 0;
    for (int i = 0; str[i] != '\n' && str[i] != '\0'; i++) {
        count++;
    }

    fclose(inputFile);

    printf("Answer = %f", calculate(GetExpression(str, count), count));
    return 0;
}