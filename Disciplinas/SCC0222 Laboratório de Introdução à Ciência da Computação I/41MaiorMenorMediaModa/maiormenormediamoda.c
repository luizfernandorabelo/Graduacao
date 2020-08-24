#include <stdio.h>
#include <stdlib.h>

#define DIMENSION 10

int *readValues();
int getBiggest(int *values);
int getShortest(int *values);
double getAverage(int *values);
int getTrend(int *values);
void printData(int biggest, int shortest, double average, int trend);

int main(int argc, char *argv[]){

    int *values = readValues();
    int biggest = getBiggest(values);
    int shortest = getShortest(values);
    double average = getAverage(values);
    int trend = getTrend(values);

    printData(biggest, shortest, average, trend);

    free(values);

    return 0;
}

int *readValues(){
    int *values = malloc(DIMENSION * sizeof(int));
    for(int i = 0; i < DIMENSION; i++){
        scanf("%d", &values[i]);
    }
    return values;
}

int getBiggest(int *values){
    int biggest = 0;
    for(int i = 1; i < DIMENSION; i++){
        biggest = (values[i] > values[biggest]) ? i : biggest;
    }
    return values[biggest];
}

int getShortest(int *values){
    int shortest = 0;
    for(int i = 1; i < DIMENSION; i++){
        shortest = (values[i] < values[shortest]) ? i : shortest;
    }
    return values[shortest];
}

double getAverage(int *values){
    int sum = 0;
    for(int i = 0; i < DIMENSION; i++){
        sum += values[i];
    }
    return (double) sum / DIMENSION;
}

int getTrend(int *values){
    int *frequency = calloc(DIMENSION, sizeof(int));
    int best = 0;
    for(int i = 1; i < DIMENSION; i++){
        frequency[i] = 1;        
        for(int j = 0; j < i; j++){
            frequency[i] = (values[j] == values[i]) ? frequency[i] + 1 : frequency[i];
        }
        best = (frequency[i] > frequency[best]) ? i : best;
    }
    free(frequency);
    return values[best];
}

void printData(int biggest, int shortest, double average, int trend){
    printf("%d %d %.2lf %d\n", biggest, shortest, average, trend);
    return;
}