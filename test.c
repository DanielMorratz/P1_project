#include <stdio.h>



int main (void) {
   char test = 0;
   
   printf("get input\n");
   scanf("%c", &test);
   if (test == -122 ) {
      test = 'a';
   }
   printf("%d %c \n",test, test); 
   return(0);
}