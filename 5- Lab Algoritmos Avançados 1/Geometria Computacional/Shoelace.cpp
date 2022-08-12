#include <iostream>
#include <vector>

using namespace std;


typedef long long int llint;

struct Point {
    llint x, y;
};

typedef vector<Point*> Polygon;


Polygon readPolygon(int totalVertices) {

    Polygon polygon;

    for (int i = 0; i < totalVertices; i++) {
        Point* point = new Point; 
        cin >> point->x >> point->y;
        polygon.push_back(point);
    }

    return polygon;
}


llint evaluateCrossProduct(const Point* v1, const Point* v2) {
    return v1->x * v2->y - v2->x * v1->y;  // parallelogram area
}


llint evaluatePolygonArea(Polygon &polygon, int totalVertices) {
    
    llint area = evaluateCrossProduct(polygon[0], polygon[totalVertices-1]);

    for (int i = 1; i < totalVertices; i++) {
        area += evaluateCrossProduct(polygon[i], polygon[i-1]);
    }

    return abs(area);  // 2x polygon area
}


int main(void) {

    int totalVertices;
    cin >> totalVertices;

    Polygon polygon = readPolygon(totalVertices);

    cout << evaluatePolygonArea(polygon, totalVertices) << "\n";

    return 0;
}
