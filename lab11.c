#include<stdio.h>
int  main()
{
union Data {
int n;
char a[4];
}data;
data.n = 1;
if(data.a[0]==0)
{
printf("big indian");
}
else
{
printf("little indian");
}
}

