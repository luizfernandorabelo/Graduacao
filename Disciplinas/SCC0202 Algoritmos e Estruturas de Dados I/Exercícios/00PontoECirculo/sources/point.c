#include "point.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point_{
    float x;
    float y;
};

POINT *pointCreate(float x, float y){
    POINT *point = NULL;
    point = (POINT *) malloc(sizeof(POINT));
    if(point != NULL){
        point->x = x;
        point->y = y;
    }
    return(point);
}

void pointDelete(POINT **point){
    if((*point) != NULL){
        free((*point));
        (*point) = NULL;
    }
}

bool pointSet(POINT *point, float x, float y){
    if(point != NULL){
        point->x = x;
        point->y = y;
        return(True);
    }
    return(False);
}

float pointGetX(POINT *point){
    if(point != NULL){
        return(point->x);
    }
    exit(GETTING_POINT_ERROR);
}

float pointGetY(POINT *point){
    if(point != NULL){
        return(point->y);
    }
    exit(GETTING_POINT_ERROR);
}

float pointGetTwoPointsDistance(POINT *point1, POINT *point2){
    if(point1 != NULL && point2 != NULL)
        return sqrt(pow(point2->x - point1->x, 2) + pow(point2->y - point1->y, 2));
    exit(GETTING_TWO_POINTS_DISTANCE_ERROR);
}

void pointPrint(POINT *point){
    if(point != NULL){
        printf("Ponto, coord. x: %.1f\n", pointGetX(point));
        printf("Ponto, coord. y: %.1f\n", pointGetY(point));
    }
}