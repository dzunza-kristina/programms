#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(float array[], int size) {
    float temp;
    for (int i = 0; i < size; i++){
        for (int j = 0; j <size; j++){
            if (array[j] < array[i]){
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

int main(){

    int size;
    printf("Enter the array size\n");
    scanf("%d", &size);

    int max_value;
    printf("Enter the max value\n");
    scanf("%d", &max_value);

    int min_value;
    printf("Enter the min value\n");
    scanf("%d", &min_value);

    float array[size];
    srand(time(NULL));
    for (int i=0; i < size; i++){
        array[i] = (float) rand() / RAND_MAX *(max_value - min_value) + min_value;
        printf("%f\n", array[i]);
    }

    FILE *output_file;
    output_file = fopen("file1", "w");
    if (output_file == NULL){
        printf("Error, can't create file\n");
        return 1;
    }

    sort(array, size);
    for (int i = 0; i < size; i++){
        fprintf(output_file, "%f ", array[i]);
    }
}