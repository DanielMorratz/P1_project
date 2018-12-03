#include <stdio.h>
#include <string.h>

#define MAX_SIZE 30
#define TRUE 1
#define FALSE 0

int has_special_sym (char[][MAX_SIZE], const int);

int main(void)
{

	has_special_sym (array, 3)
	
	return 0;
}

int has_special_sym (char title[][MAX_SIZE], const int size) {
	int i, special_flag = FALSE;
	for (i = 0; i < size; i++) {
		if (title[i][strlen(title[i])-1] == '!' || title[i][strlen(title[i])-1] == '?') {
			special_flag = TRUE;
		}
	}
	return special_flag;
}
