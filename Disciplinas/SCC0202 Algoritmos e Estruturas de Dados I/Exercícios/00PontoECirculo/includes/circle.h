#ifndef CIRCLE_H
    #define CIRCLE_H

    #define bool char
    #define True 1
    #define False 0

    #include "point.h"

    typedef struct circle_ CIRCLE;

    CIRCLE *circleCreate(POINT *point, float radius);
    bool circleSetPoint(CIRCLE *circle, POINT *point);
    bool circleSetRadius(CIRCLE *circle, float radius); 
    POINT *circleGetPoint(CIRCLE *circle);
    float circleGetRadius(CIRCLE *circle);
    void circlePrint(CIRCLE *circle);
    void circleDelete(CIRCLE **circle);
    bool isPointIsideCircle(CIRCLE *circle, POINT *point);

#endif

