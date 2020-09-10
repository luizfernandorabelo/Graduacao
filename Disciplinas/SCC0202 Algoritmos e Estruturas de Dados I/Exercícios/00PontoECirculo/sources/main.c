#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "point.h"
#include "circle.h"
#include "readNumber.h"

int main(int argc, char *argv[]){

    setlocale(LC_ALL, "Portuguese");

    printf("Digite as coordenadas do centro do círculo:\n");
    float pointX = readFloat();
    float pointY = readFloat();

    POINT *myPoint = pointCreate(pointX, pointY);
    printf("\nPonto central definido:\n");
    pointPrint(myPoint);

    printf("\nDigite o raio do círculo: ");
    float circleRadius = readFloat();

    CIRCLE *myCircle = circleCreate(myPoint, circleRadius);
    printf("\nCírculo definido:\n");
    circlePrint(myCircle);

    printf("\nDigite as coordenadas do ponto a ser analisado:\n");
    float newPointX = readFloat();
    float newPointY = readFloat();
    POINT *newPoint = pointCreate(newPointX, newPointY);

    bool inside = isPointInsideCircle(myCircle, newPoint);
    
    if(inside == True) printf("\n-> O ponto (%.1f, %.1f) é interior ao círculo\n", newPointX, newPointY);
    else printf("\nO ponto (%.1f, %.1f) é exterior ao círculo\n", newPointX, newPointY);

    pointDelete(&myPoint);
    pointDelete(&newPoint);
    circleDelete(&myCircle);
    
    return 0;
}