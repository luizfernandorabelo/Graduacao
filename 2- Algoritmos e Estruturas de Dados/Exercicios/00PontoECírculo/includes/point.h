#ifndef POINT_H
    #define POINT_H 

    #define bool char
    #define True 1
    #define False 0

    #define GETTING_POINT_ERROR 0

    typedef struct point_ POINT;

    POINT *pointCreate(float x, float y);
    void pointDelete(POINT **point);
    bool pointSet(POINT *point, float x, float y);
    float pointGetX(POINT *point);
    float pointGetY(POINT *point);
    void pointPrint(POINT *point);

#endif
