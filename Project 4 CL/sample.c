#include <stdio.h>

int add(int a,int b)
{
    return a+b;
}

int main()
{
    //sample comment1
    int i=0;
    float x = 10.09;
    i+=1+201;
    char c='a';
    x=x*i/2;

    for(int j=0;j<=10;j++)
    {
        if(x!=0)
            printf("hello world %f %a\n",x,c);
        else
        {
            x=(int)x+1;
        }
    }

    int sum = add(i,5);
    printf("Another print satement");
}