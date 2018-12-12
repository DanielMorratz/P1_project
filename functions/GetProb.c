void get_prob(double nonclickbaitprob[], double clickbaitprob[], FILE *fp){
    int i = 0;

    for(i = 0; i < amountoffeature; i++){
        fscanf(fp," %lf ", nonclickbaitprob[i]);
    }
    for(i = 0; i < amountoffeature; i++){
        fscanf(fp," %lf ", clickbaitprob[i]);    
    }    
}