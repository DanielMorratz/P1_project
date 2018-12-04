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
int has_citation(char [MAX_SIZE][MAX_SIZE], const int );


int main (void) {
   int has_fw = 0, has_cite = 0;
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
   has_cite = has_citation(title,size);
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
   "Derfor", "derfor","Denne","denne","Disse","disse","dette","Dette"};

    /* First loop: checks the first characters of each letter
      if true, checks the whole word 
      First [] == pointer to the string
      Second [] == pointer to char in string*/
   for (i = 0; i < size; i++){
      for(j = 0; j < AMOUNT_OF_PRONOUNS; j++) {
         if(strcmp(title[i],fw_ref_words[j]) == 0){
            fw_flag = 1;
         }  else if (title[i][0] == '"' || title[i][0] == '\'') {
               if(strcmp(title[i]+1,fw_ref_words[j]) == 0){
                  fw_flag = 1;
               }
         }
      }
   }

    return fw_flag;
}
int has_citation(char title[MAX_SIZE][MAX_SIZE], const int size){
   int c_flag = FALSE;
    int i = 0;
    for(i = 0; i < size; i++){
        if(title[i][0] == '"'|| title[i][0] == '\''){
            c_flag = TRUE;
        }
    }

    return c_flag;
}



/* debug function */
void print_array (char title[MAX_SIZE][MAX_SIZE], const int size) {
   int i = 0;
   for(i = 0; i < size;i++) {
      
      printf("%s ",title[i]);
      
   }
   printf("\n");
   return;
}