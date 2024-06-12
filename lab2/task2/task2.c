#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
    srand(time(NULL));
    FILE *output_file;
    int size;
    printf("Enter the array size\n");
    scanf("%d", &size);
    
    int array[size];
    for (int i = 0; i < size; i++){
        array[i] = rand()%100;
        printf("%d\t", array [i]);
    }
    
    output_file = fopen("file1", "w");
    if(output_file == NULL){
        printf("Error, can't create file\n");
        return 1;
    }

    for (int i = 0; i < size; i++){
        fprintf(output_file, "%d\t", array[size-i-1]);
    }
    
    fclose(output_file);
    return 0;

}