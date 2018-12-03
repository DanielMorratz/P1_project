#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 30

void txt_write_to (FILE*, FILE*, char[][MAX_SIZE], const int, const double);


int main(void) {
	
	FILE *cb = fopen("clickbaity.txt", "w");
	FILE *non_cb = fopen("n_clickbaity.txt", "w");

	txt_write_to(cb, non_cb, title, size, points);
	
	fclose(cb);
	fclose(non_cb);
  
	return 0;
}

void txt_write_to (FILE* cb, FILE* non_cb, char title[][MAX_SIZE], const int size, const double points) {
	int i;
	
	for (i = 0; i < size; i++) {
		if (points < 0.5) {
			fprintf(cb, "%s ", title[i]);
		} else {
			fprintf(non_cb, "%s ", title[i]);
		}
	}
}
