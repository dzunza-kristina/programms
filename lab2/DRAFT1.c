#include <stdio.h>
#include <string.h>

struct companies{
    char name[50];
    int cost;
    int n_workers;
};

int exist_company(char *s, struct companies *company){
    if(strcmp(s, company->name) == 0)
        return 1;
    else
        return 0;
}

int main(void){
    struct companies my_company = {"pltm", 350, 2};
    if(exist_company("pltm", &my_company))
        printf("yes");
    else(printf("no"));
    return 0;
}