#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 30
#define TRUE 1
#define FALSE 0
#define AMOUNT_OF_PRONOUNS 7*2

/*prototypes*/
int get_title (char [MAX_SIZE][MAX_SIZE], FILE *);
void print_array (char [MAX_SIZE][MAX_SIZE], const int );
int has_fw_reference(char[MAX_SIZE][MAX_SIZE], const int);



int main (void) {
   int has_fw = 0;
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
   has_fw = has_fw_reference(title, size);
   printf("%d\n", has_fw);
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
         exit(EXIT_SUCCESS);
   }
   return size;
}


/* Måske bare brug strcmp hele vejen */
int has_fw_reference(char title[MAX_SIZE][MAX_SIZE], const int size){
   int i = 0, fw_flag = 0, j = 0;
   char fw_ref_words[AMOUNT_OF_PRONOUNS][AMOUNT_OF_PRONOUNS] ={"her","Her","Saadan", "saadan","Saa", "saa",
   "Derfor", "derfor","Denne","denne","Diise","disse"};

    /* First loop: checks the first characters of each letter
      if true, checks the whole word 
      First [] == pointer to the string
      Second [] == pointer to char in string*/
   for (i = 0; i < size; i++){
      for(j = 0; j < AMOUNT_OF_PRONOUNS; j++) {
         if(strcmp(title[i],fw_ref_words[j]) == 0){
            fw_flag = 1;
            
         }  
      }
   }
    

    return fw_flag;
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