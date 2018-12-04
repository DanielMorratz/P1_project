
#include<stdio.h>
#include<math.h>

int Citation(char array[30][30], int LoA){

    int i = 0;
    for(i = 0; i < LoA; i++){
        if(array[i][1] == '"'){
            return 1;
        }
    }

    return 0;
}
