#include <stdio.h>

int main()
{
    //sample comment1
    int i=0;
    char c='a';
    i=i+1;
    float x= x*i/2;

    for(int j=0;j<10;j++)
    {
        if(x!=0)
            printf("hello world %f %a\n",x,c);
        else
        {
            x=(int)x^1;
        }
    }
}