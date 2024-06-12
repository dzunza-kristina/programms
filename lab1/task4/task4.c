#include <stdio.h>

int main()
{

printf("Hi! Today we will solve a linear equation of the form ax+b=c\n");
printf("To do this, let's set the values of the equation\n");

int a,b,c;
float x;

printf("Set the value for coefficiens\n");

printf("Coefficient a=\n");
scanf("%d", &a);

printf("Coefficient b=\n");
scanf("%d", &b);

printf("Coefficient c=\n");
scanf("%d", &c);

printf("Now you have equation %d x + %d = %d\n", a, b, c);

x=(c-b)/a;

printf("x=%f\n", x);

return 0;

}

