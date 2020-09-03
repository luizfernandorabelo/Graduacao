#ifndef POINT_H
    #define POINT_H 

    #define bool char
    #define True 1
    #define False 0

    #define GETTING_POINT_ERROR -1
    #define GETTING_TWO_POINTS_DISTANCE_ERROR -2

    typedef struct point_ POINT;

    POINT *pointCreate(float x, float y);
    void pointDelete(POINT **point);
    bool pointSet(POINT *point, float x, float y);
    float pointGetX(POINT *point);
    float pointGetY(POINT *point);
    float pointGetTwoPointsDistance(POINT *point1, POINT *point2);
    void pointPrint(POINT *point);

#endif
