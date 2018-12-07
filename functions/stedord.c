#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100
int has_fw_reference(char**);

int main(void){
    int flag;
    char **temp; 
    temp = (char**)calloc(SIZE,sizeof(char*));
    flag = has_fw_reference(temp);

}

int has_fw_reference(char** temp){
    int i = 0, k = 0, fw_flag = 0;
    char fw_ref_words[SIZE][SIZE] ={"her","Her","Saadan", "saadan","Saa", "saa",
    "Derfor", "derfor","Denne","denne","Diise","disse"};

    /* First loop: checks the first characters of each letter
       if true, checks the whole word 
       First [] == pointer to the string
       Second [] == pointer to char in string*/
    for (i = 0; i < sizeof(temp); i++){
        if(temp[i][0] == fw_ref_words[i][0]){
            if(strcmp(temp[i],fw_ref_words[i]) == 0){
                fw_flag = 1;
            }
        }
    }

    return fw_flag;
}