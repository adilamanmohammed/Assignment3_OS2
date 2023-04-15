#include<stdio.h>
#include "library.h"

int a,b,c,d;

int main()
{

printf("enter option:\n");
scanf("%d",&d);
printf("enter funtion 1 0r 2:\n");
scanf("%d %d",&a,&b);

if(d==1)
sum(a,b);
else
sub(a,b);

return 0;
}
