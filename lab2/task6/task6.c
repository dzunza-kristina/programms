#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int maxSize;
    int top;
    int *items;
};

struct Stack *newStack(int capacity) {
    struct Stack *ptr = (struct Stack*) malloc(sizeof(struct Stack));

    ptr->maxSize = capacity;
    ptr->top = -1;
    ptr->items = (int*) malloc(sizeof(int) *capacity);
    
    return ptr;
}

int isEmpty(struct Stack *ptr) {
    return ptr->top == -1;
}

int isFull(struct Stack *ptr) {
    return ptr->top == ptr->maxSize - 1;
}

int push(struct Stack *ptr, int x) {
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

int main () {
    struct Stack *stack = newStack(10);
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);

    printf("%d\n", peek(stack));
    pop(stack);

    
    printf("%d\n", peek(stack));
    pop(stack);
    
    printf("%d\n", peek(stack));
    pop(stack);

    push(stack, 1);

    if (isEmpty(stack)) {
        printf("The stack is empty");
    }
    else {
        printf("The stack is not empty");
    }

    return 0;
}