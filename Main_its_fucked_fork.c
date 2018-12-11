#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 30
#define TRUE 1
#define FALSE 0
#define AMOUNT_OF_PRONOUNS 7*2
#define PROB_CB_CAPS 0.075
#define PROB_NOTCB_CAPS 0.1
#define PROB_CB_SYM 0.1125
#define PROB_NOTCB_SYM 0
#define PROB_CB_QUOTE 0.525
#define PROB_NOTCB_QUOTE 0.175
#define PROB_CB_FORWARD 0.15
#define PROB_NOTCB_FORWARD 0
#define THRESHOLD 65
#define AMOUNT_OF_FLAGS 4
#define AMOUNT_OF_FEATURES 4

enum flag { has_fw = 0, has_cite = 1, has_caps = 2, has_sp_sym = 3 };
    
enum probability { cb_stedord = 0, cb_quotes = 1, cb_caps = 2, cb_eq_marks = 3, notcb_stedord = 4, notcb_caps = 5, notcb_quotes = 6, notcb_eq_marks = 7 };

/*prototypes*/
int get_title (char [MAX_SIZE][MAX_SIZE], FILE *);
void print_array (char [MAX_SIZE][MAX_SIZE], const int );
int has_fw_reference(char[MAX_SIZE][MAX_SIZE], const int);
int has_citation(char [MAX_SIZE][MAX_SIZE], const int );
int has_all_caps(char [MAX_SIZE][MAX_SIZE], const int );
int has_special_sym (char[MAX_SIZE][MAX_SIZE], const int);
double get_score(int [], double[]);
void write_to_txt (FILE *, char [MAX_SIZE][MAX_SIZE], const int , const double);
void getf1_score(const int , const int , const int , const int);

int main (void) {
    int flags[AMOUNT_OF_FLAGS];
    int false_positive = 0, true_positive = 0, false_negative = 0, true_negative = 0, size = 0, done = 0;
    char title[MAX_SIZE][MAX_SIZE]; 
    double probabilities[AMOUNT_OF_FEATURES*2];
    FILE * input_file = NULL, *cb_file = NULL, *non_cb_file = NULL;
    FILE *training_clickbait = NULL, *training_nonclickbait = NULL;
   

    double score = 0;
    input_file = fopen("overskrifter.txt","r");
    cb_file = fopen("clickbait.txt", "w");
	non_cb_file = fopen("non_clickbait.txt", "w");
    training_clickbait = fopen("training_clickbaitdata.txt","r");
    training_nonclickbait = fopen("training_nonclickbaitdata.txt","r"); 
    /* Lukker programmet hvis filen med overskrifter ikke eksisterer*/
    if (input_file == NULL) {
        printf("ERROR FILE DOES NOT EXIST");
        exit(EXIT_FAILURE);
    }
   
   
    while(!done) {
        size = get_title(title, input_file);
        if(size > 0) {
            /*
            print_array(title,size); */
            flags[has_fw] = has_fw_reference(title, size);
            flags[has_cite] = has_citation(title,size);
            flags[has_caps] = has_all_caps(title,size);
            flags[has_sp_sym] = has_special_sym(title, size);
            
            score = get_score(flags, probabilities);
            /* debug print 
            printf("Og resultatet er %lf\n", score);*/
            if(score > THRESHOLD) {
                if (strcmp(title[0], "clickbait") == 0 ) {
                    true_positive++;
                } else {
                    false_positive++;
                }
                write_to_txt(cb_file, title, size, score);
            } else {
                if (strcmp(title[0], "clickbait") == 0 ) {
                    false_negative++;
                } else {
                    true_negative++;
                }
                write_to_txt(non_cb_file, title, size, score);
            }
        } else { 
            done = 1;  
    }
    fclose(input_file);
    fclose(cb_file);
	fclose(non_cb_file);
    getf1_score(true_positive, false_positive, true_negative, false_negative);
    return 0;
}

/* Indlæster en oerskrift ind i et string array*/
int get_title (char title[MAX_SIZE][MAX_SIZE], FILE *file) {
    char string[MAX_SIZE];
    int done = 0, size = 0;
    if (fscanf(file," %*[^<]s ") != EOF) {
      
        fscanf(file," %s ",string);
        if (strcmp(string, "<title>") == 0) {
            while (!done) {
                fscanf(file," %s ",string); 
            
                if (strcmp(string,"<\\title>")== 0) {
                    done = 1;
               
                } else {
                    strcpy(title[size],string);
                    size++;
               
                }
         
            }
        }
    } else {
        printf("END OF FILE REACHED\n");
        return 0;
   }
   return size;
}


/* Tjekker om et af ordene fra vores ordliste af stedord, er i sætningen */
int has_fw_reference(char title[MAX_SIZE][MAX_SIZE], const int size){
    int i = 0, fw_flag = FALSE, j = 0;
    char fw_ref_words[AMOUNT_OF_PRONOUNS][AMOUNT_OF_PRONOUNS] ={"her","Her","Saadan", "saadan","Saa", "saa",
    "Derfor", "derfor","Denne","denne","Disse","disse","dette","Dette"};

    /* First loop: checks the first characters of each letter
      if true, checks the whole word 
      First [] == pointer to the string
      Second [] == pointer to char in string*/
    for (i = 0; i < size; i++){
        for(j = 0; j < AMOUNT_OF_PRONOUNS; j++) {
            if(strcmp(title[i],fw_ref_words[j]) == 0){
                fw_flag = TRUE;
            }  else if (title[i][0] == '"' || title[i][0] == '\'') {
                if(strcmp(title[i]+1,fw_ref_words[j]) == 0){
                    fw_flag = TRUE;
                }
            }
        }
    }
    return fw_flag;
}

/* tjekker om der er et citat i sætningen */
int has_citation(char title[MAX_SIZE][MAX_SIZE], const int size){
    int cite_flag = FALSE;
    int i = 0;
    for(i = 0; i < size-1; i++){
        if(title[i][0] == '"'|| title[i][0] == '\'' || title[i][strlen(title[i])-1] == ':'){
            cite_flag = TRUE;
        }
    }

    return cite_flag;
}

/* Tjekker om de 2 første bogstaver af et ord er store, hvilket betyder at hele ordet er i all caps, eller at journalisten ikke kan stave */
int has_all_caps(char title[MAX_SIZE][MAX_SIZE], const int size){
    int i = 0, caps_flag = FALSE;
    for( i = 0; i < size; i++){
        if((isupper(title[i][0]) && isupper(title[i][1])) || (isupper(title[i][1]) && isupper(title[i][2]))) {
            caps_flag = TRUE;
        }
    }
    return caps_flag;
}

/* tjekker om et ord slutter på ! eller ?*/
int has_special_sym (char title[MAX_SIZE][MAX_SIZE], const int size) {
	int i = 0, special_flag = FALSE;
	for (i = 0; i < size; i++) {
        if (title[i][strlen(title[i])-1] == '!' || title[i][strlen(title[i])-1] == '?') {
			special_flag = TRUE;
		}
	}
	return special_flag;
}

double get_score(int flags[], double probabilities[]) {
    
    double bayes_score, is_cb, isnot_cb;
    /* Hvis en feature ikke er fundet er sandsynligheden 1-feature*/
    int i = 0;
    
    probabilities[notcb_stedord] = PROB_NOTCB_FORWARD;
    probabilities[notcb_eq_marks] = PROB_NOTCB_SYM;
    probabilities[notcb_quotes] = PROB_NOTCB_QUOTE;
    probabilities[notcb_caps] = PROB_NOTCB_CAPS;
    probabilities[cb_stedord] = PROB_CB_FORWARD; 
    probabilities[cb_eq_marks] = PROB_CB_SYM;
    probabilities[cb_quotes] = PROB_CB_QUOTE;
    probabilities[cb_caps] = PROB_CB_CAPS;
    
    
    
    
    for (i = 0; i < AMOUNT_OF_FEATURES;i++) {
        if (flags[i] == 0) {
            probabilities[i] = 1-probabilities[i];
            probabilities[i+AMOUNT_OF_FEATURES] = 1-probabilities[i+AMOUNT_OF_FEATURES];
        }
    }

    is_cb = (probabilities[cb_stedord] * probabilities[cb_eq_marks] * probabilities[cb_quotes] * probabilities[cb_caps]);
    isnot_cb = (probabilities[notcb_stedord] * probabilities[notcb_eq_marks] * probabilities[notcb_quotes] * probabilities[notcb_caps]);
    
    bayes_score = is_cb/(is_cb+isnot_cb)*100;
    
    /* debug print*/
    /*printf("is_cb = %lf\nisnot_cb = %lf\n", is_cb, isnot_cb); */
    return bayes_score;
}


/* Skriver en sætning ind i den respektive fil */
void write_to_txt (FILE *file, char title[MAX_SIZE][MAX_SIZE], const int size, const double score) {
	int i = 0;
	
	for (i = 0; i < size; i++) {
        fprintf(file, "%s ", title[i]);
	}
    fprintf(file,"\" Score %.0lf\"\n",score);
}



/* Beregner recall, precision og f1 score ud fra positiver og negativer */
void getf1_score(const int true_positives, const int false_positives, const int true_negatives, const int false_negatives){
    double f1 = 0, recall = 0, precision = 0;

    precision = (double) true_positives/(false_positives + true_positives);
    recall =(double) true_positives/(false_positives + true_negatives);    
    f1 = 2*(recall * precision)/(recall + precision);
    printf("true positives: %d\t false positives: %d\t, true_negatives: %d\t false_negatives: %d\n",true_positives, false_positives,true_negatives, false_negatives);
    printf(" Recall: %lf precision: %lf\n F1 score: %lf\n", recall, precision, f1);

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