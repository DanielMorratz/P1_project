#include <stdio.h>

void getf1_score(int true_positives, int false_positives, int true_negatives, int false_negatives){
    double f1;
    int recall, precision;
    
    precision = true_positives/(false_positives + true_positives);
    recall = true_positives/(false_positives + true_negatives)
    
    f1 =(double) 2*(recall * precision)/(recall + precision);
    
    printf("true positives: %d\t false positives: %d\n Recall: %d precision: %d\n F1 score: %lf",true_positives, false_positives, recall, precision, f1);

}