
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 30
#define EXIT_SUCCES 1
int get_title (char [MAX_SIZE][MAX_SIZE], FILE *);
void print_array (char [MAX_SIZE][MAX_SIZE], const int );

int main (void) {
   
   char title[MAX_SIZE][MAX_SIZE];
   int size = 0;
   FILE * file = NULL; 
   
   file = fopen("overskrifter.txt","r");
   if (file == NULL) {
      printf("ERROR FILE DOES NOT EXIST");
      exit(EXIT_FAILURE);
   }
   
   
   while(1) {
   size = get_title(title, file);
   print_array(title,size);
   }
   
   return 0;
}

int get_title (char title[MAX_SIZE][MAX_SIZE], FILE *file) {
   char string[MAX_SIZE];
   int done = 0, size = 0;
   
   if (fscanf(file," %*[^<]s ") != EOF) {
      
      fscanf(file," %s ",string);
      if (strcmp(string, "<Title>") == 0) {
         while (!done) {
            fscanf(file," %s ",string); 
            
            if (strcmp(string,"<\\Title>")== 0) {
               done = 1;
               
            } else {
               strcpy(title[size],string);
               size++;
               
            }
         
         }
      }
   } else {
         printf("END OF FILE REACHED");
         exit(EXIT_SUCCES);
   }
   return size;
}
/* debug function */
void print_array (char array[MAX_SIZE][MAX_SIZE], const int size) {
   int i = 0;
   for(i = 0; i < size;i++) {
      
      printf("%s ",array[i]);
      
   }
   printf("\n");
   return;
}