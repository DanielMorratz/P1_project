/*#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>

#define MAX_SIZE 50

int has_all_caps(char title[MAX_SIZE][MAX_SIZE], const int size);

int main(int argc, char const *argv[])
{
    char a[3][4] = {  
        {"Hej"} ,
        {"med"} ,
        {"DIG"}
    };

    printf("%d", has_all_caps(a));

    return 0;
}*/

/* -------------------------------------------------------------- */
int has_all_caps(char title[MAX_SIZE][MAX_SIZE], const int size);

int has_all_caps(char title[MAX_SIZE][MAX_SIZE], const int size)
{
    for(int i = 0; i < size; i++)
    {
        if(isupper(title[i][0]) && isupper(title[i][1]))
        {
            return 1;
        }
    }
    return 0;
}