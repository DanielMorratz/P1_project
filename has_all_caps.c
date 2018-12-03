#include<ctype.h>

int has_all_caps(char **title, int size)
{
    for(int = 0; i < size; i++)
    {
        if(isupper(title[i][0]) && isupper(title[i][1]))
            return 1;
    }
    return 0;
}