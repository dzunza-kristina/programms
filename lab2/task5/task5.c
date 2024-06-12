#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Product {
    char name[100];
    float price;
};

int compareProducts(const void *a, const void *b) {
    const struct Product *productA = (const struct Product *)a;
    const struct Product *productB = (const struct Product *)b;
    return (productA->price > productB->price) - (productA->price < productB->price);
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening the input file.\n");
        return 1;
    }

    int numProducts;
    fscanf(inputFile, "%d", &numProducts);

    struct Product *products = (struct Product *)
    malloc(numProducts * sizeof(struct Product));
    if (products == NULL) {
        printf("Memory allocation error.\n");
        fclose(inputFile);
        return 1;
    }

    for (int i = 0; i < numProducts; i++) {
        fscanf(inputFile, "%s %f", products[i].name, &products[i].price);
    }

    fclose(inputFile);

    qsort(products, numProducts, sizeof(struct Product), compareProducts);

    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error when opening the output file.\n");
        free(products);
        return 1;
    }

    fprintf(outputFile, " Sorted products by price:\n");
    for (int i = 0; i < numProducts; i++) {
        fprintf(outputFile, "%s %.2f\n", products[i].name, products[i].price);
    }

    fclose(outputFile);

    free(products);

    printf("The data has been successfully sorted and written to a file 'output.txt '.\n");

    return 0;
}