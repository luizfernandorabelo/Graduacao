#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "circle.h"

float readFloat(){
    float number = 0;
    scanf("%f", &number);
    return number;
}

int main(int argc, char *argv[]){

    float pointX = readFloat();
    float pointY = readFloat();

    POINT *myPoint = pointCreate(pointX, pointY);

    float circleRadius = readFloat();

    CIRCLE *myCircle = circleCreate(myPoint, circleRadius);

    pointPrint(myPoint);
    circlePrint(myCircle);

    pointDelete(&myPoint);
    circleDelete(&myCircle);

    return(0);
}
