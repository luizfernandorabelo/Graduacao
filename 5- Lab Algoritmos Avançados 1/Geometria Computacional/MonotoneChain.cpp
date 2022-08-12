#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


struct Point {
    double x, y;
};

typedef vector<Point*> Points;


Points readPoints(int totalPoints) {

    Points points;

    for (int i = 0; i < totalPoints; i++) {
        Point* point = new Point; 
        cin >> point->x >> point->y;
        points.push_back(point);
    }

    return points;
}


bool compar(const Point* p1, const Point* p2) {
    if (p1->x < p2->x)
        return true;
    if (p1->x == p2->x)
        return p1->y <= p2->y;
    return false;
}


Point* makePointDifference(Point* a, Point* b) {
    Point* newPoint = new Point;
    newPoint->x = a->x - b->x;
    newPoint->y = a->y - b->y;
    return newPoint;
}


double evaluateCrossProduct(const Point* v1, const Point* v2) {
    return v1->x * v2->y - v2->x * v1->y;
}


Points buildLowerHull(Points points) {

    Points lowerHull;

    lowerHull.push_back(points[0]);
    lowerHull.push_back(points[1]);

    Point* current, *previous;

    for (uint i = 2; i < points.size(); i++) {
        while (lowerHull.size() >= 2) {
            current = makePointDifference(
                points[i], lowerHull[lowerHull.size() - 2]
            );
            previous = makePointDifference(
                lowerHull[lowerHull.size() - 1], lowerHull[lowerHull.size() - 2]
            );
            if (evaluateCrossProduct(previous, current) < 0) lowerHull.pop_back();
            else break;
        }
        lowerHull.push_back(points[i]);
    }

    return lowerHull;
}


Points buildUpperHull(Points points) {

    Points upperHull;

    upperHull.push_back(points[points.size() - 1]);
    upperHull.push_back(points[points.size() - 2]);

    Point* current, *previous;

    for (int i = points.size() - 3; i >= 0; i--) {
        while (upperHull.size() >= 2) {
            current = makePointDifference(
                points[i], upperHull[upperHull.size() - 2]
            );
            previous = makePointDifference(
                upperHull[upperHull.size() - 1], upperHull[upperHull.size() - 2]
            );
            if (evaluateCrossProduct(previous, current) <= 0) upperHull.pop_back();
            else break;
        }
        upperHull.push_back(points[i]);
    }

    return upperHull;
}


Points joinHulls(const Points &lowerHull, const Points &upperHull) {
    Points hull = lowerHull;
    hull.insert(
        hull.end(), upperHull.begin() + 1,
        upperHull.begin() + upperHull.size() - 1
    );
    return hull;
}


double evaluateVertexDistance(Point* a, Point* b) {
    return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
}


double evaluateVerticesDistance(Points hull) {

    double distance = 0;

    for (uint i = 1; i < hull.size(); i++)
        distance += evaluateVertexDistance(hull[i], hull[i-1]);

    distance += evaluateVertexDistance(hull[0], hull[hull.size() - 1]);

    return distance;
}


double evaluateMinimumPerimeter(Points points) {

    sort(points.begin(), points.end(), compar); 

    Points lowerHull = buildLowerHull(points);
    Points upperHull = buildUpperHull(points);
    Points hull = joinHulls(lowerHull, upperHull);

    return evaluateVerticesDistance(hull);
}


int main(void) {

    int totalSheeps;
    cin >> totalSheeps;

    Points points = readPoints(totalSheeps);

    double minPerimeter = evaluateMinimumPerimeter(points);

    cout << fixed << setprecision(6) << minPerimeter <<  "\n";

    return 0;
}
