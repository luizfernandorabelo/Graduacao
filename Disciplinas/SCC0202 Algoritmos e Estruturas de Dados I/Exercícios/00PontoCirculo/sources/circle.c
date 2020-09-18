#include "circle.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct circle_{
    POINT *point;
    float radius;
};

CIRCLE *circleCreate(POINT *point, float radius){
    CIRCLE *circle = NULL;
    circle = (CIRCLE *) malloc(sizeof(CIRCLE));
    if(circle != NULL){
        circle->point = point;
        circle->radius = radius;
    }
    return circle;
}

bool circleSetPoint(CIRCLE *circle, POINT *point){
    if(circle != NULL){
        circle->point = point;
        return(True);
    }
    return(False);
}

bool circleSetRadius(CIRCLE *circle, float radius){
    if(circle != NULL){
        circle->radius = radius;
        return(True);
    }
    return(False);
}

POINT *circleGetPoint(CIRCLE *circle){
    if(circle != NULL){
        return(circle->point);
    }
    return NULL;
}

float circleGetRadius(CIRCLE *circle){
    if(circle != NULL){
        return(circle->radius);
    }
    return 0;
}

bool isPointInsideCircle(CIRCLE *circle, POINT *newPoint){
    float twoPointsDistance = pointGetTwoPointsDistance(circle->point, newPoint);
    if(twoPointsDistance > circle->radius) return False;
    return True;
}

void circlePrint(CIRCLE *circle){
    if(circle != NULL){
        printf("Circulo, coord. x: %.1f\n", pointGetX(circle->point));
        printf("Circulo, coord. y: %.1f\n", pointGetY(circle->point));
        printf("Raio: %.0lf\n", circle->radius);
    }
}

void circleDelete(CIRCLE **circle){
    if((*circle) != NULL){
        free((*circle));
        (*circle) = NULL;
    }
}