#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Stack {
    int maxSize;
    int top;
    double *items;
};

struct Stack *newStack(int capacity) {
    struct Stack *ptr = (struct Stack*) malloc(sizeof(struct Stack));

    ptr->maxSize = capacity;
    ptr->top = -1;
    ptr->items = (double*) malloc(sizeof(int) *capacity);
    
    return ptr;
}

int isEmpty(struct Stack *ptr) {
    return ptr->top == -1;
}

int isFull(struct Stack *ptr) {
    return ptr->top == ptr->maxSize - 1;
}

int push(struct Stack *ptr, double x) {
    if (isFull(ptr)) {
        printf("Overflow\n");
        return 1;
    }

    ptr->items[++ptr->top] = x;
}

int pop(struct Stack *ptr) {
    if(isEmpty(ptr)) {
        printf("Underflow\n");
        return 1;
    }

    return ptr->items[ptr->top--];
}

int peek(struct Stack *ptr) {
     if(!isEmpty(ptr)) {
        return ptr->items[ptr->top];
    } else {
        return 1;
    }
}

double calculate(char *str, int count) {
    double result = 0;
    struct Stack *nums = newStack(count);

    for (int i = 0; i < strlen(str); i++) {
    
        if(isdigit(str[i])) {
            
            int indexStart = i;
            while (str[i] != ' ' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
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
            push(nums, atof(num));
            i--;
        
        } else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
            double a = pop(nums);
            double b = pop(nums);

            switch (str[i]) {
                case '+': result = b + a; break;
                case '-': result = b - a; break;
                case '*': result = b * a; break;
                case '/': result = b / a; break;
            }
            push(nums, result);
        }

    }
    return result;
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

    printf("Answer = %f\n", calculate(str, count));
    return 0;
}