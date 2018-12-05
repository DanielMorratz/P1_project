#include <stdio.h>

void check_for_flag(double*, double*, double*, double*,
double*, double*, double*, double*);
double cb_prob(double, double, double, double);
double notcb_prob(double, double, double, double);
void print_bayes(double, double);

int main(void){
    /* Sandyndligheden for artiklen er clickbait NÅR feature forekommer
    Fastlagt udfra Antal forekomster / Antal_CB_artikler */
    double cb_stedord = 0.80, cb_eq_marks = 0.75, cb_quotes = 1.0, cb_caps = 0.92;
    
    /* Disse variabler fortæller, hvor mange gange forekommer feature i IKKE clickbait artikler (som vi har label't)*/ 
    double notcb_stedord = 0.70, notcb_eq_marks = 0.25, notcb_quotes = 0.6, notcb_caps = 0.08;
    double bayes_score, is_cb, isnot_cb;
 
    /* Hvis en feature ikke er fundet er sandsynligheden 1-feature*/
    
    check_for_flag(&cb_stedord, &cb_eq_marks, &cb_quotes, &cb_caps, 
    &notcb_stedord, &notcb_eq_marks, &notcb_quotes, &notcb_caps);
    
    is_cb = cb_prob(cb_stedord, cb_eq_marks, cb_quotes, cb_caps);
    isnot_cb = notcb_prob(notcb_stedord, notcb_eq_marks, notcb_quotes, notcb_caps);
    
    printf("is_cb = %lf\nisnot_cb = %lf\n", is_cb, isnot_cb);
    print_bayes(is_cb, isnot_cb);
 
    return 0;
}

/* flags kan evt sendes herned, som kan bruges hvis features ikke optråde*/
void check_for_flag(double *cb_stedord, double *cb_eq_marks, double *cb_quotes, double *cb_caps,
double *notcb_stedord, double *notcb_eq_marks, double *notcb_quotes, double *notcb_caps){

double fw_flag = 1.0, eq_flag = 0.0, quote_flag = 1.0, caps_flag = 1.0;
    if (fw_flag == 0.0){
        *cb_stedord = 1.0 - *cb_stedord;
        *notcb_stedord = 1.0 - *notcb_stedord;
    }
    if (eq_flag == 0.0){
        *cb_eq_marks = 1.0 - *cb_eq_marks;
        *notcb_eq_marks = 1.0 - *notcb_eq_marks;
    }
    if(quote_flag == 0.0){
        *cb_quotes = 1.0 - *cb_quotes;
        *notcb_quotes = 1.0 - *notcb_quotes;
    }
    if(caps_flag == 0.0){
        *cb_caps = 1.0 - *cb_caps;
        *notcb_caps = 1.0 - *notcb_caps;
    }   
}

double cb_prob(double cb_stedord, double cb_eq_marks, double cb_quotes, double cb_caps){
    
    return (cb_stedord * cb_eq_marks * cb_quotes * cb_caps);
}

double notcb_prob(double notcb_stedord, double notcb_eq_marks, double notcb_quotes, double notcb_caps){
    
    return (notcb_stedord * notcb_eq_marks * notcb_quotes * notcb_caps);
}

void print_bayes(double is_cb, double isnot_cb){
    double bayes_score = is_cb/(is_cb+isnot_cb);
    printf("Bayes score is %.2lf %% for chance of clickbait", bayes_score*100);
    
}