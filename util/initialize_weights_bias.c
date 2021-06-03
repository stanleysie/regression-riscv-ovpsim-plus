#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initializeWeights(float *weights, int num){
    int i=0;
    srand((unsigned int)time(NULL));

    for(i=0;i<num;i++){
        float x = (rand()%1000000);
        x = x/1000000;
        weights[i] = x;
    }
}

float initializeBias(){
    float x = (rand()%1000000);
    return x/1000000;
}
