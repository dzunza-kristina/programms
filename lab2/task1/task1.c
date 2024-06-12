#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
Написать программу, которая генерирует массив из псевдослучайных целых чисел и выводит его в консоль.*/
int main() {
    srand(time(NULL));

    int size;
    printf("Enter the array size\n");
    scanf("%d", &size);

    int array[size];
    for (int i = 0; i < size; i++) {
        array[i] = rand()%100;
        printf("%d\t", array[i]);
    }
    
    return 0;
}