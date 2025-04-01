#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct Point {
    double x, y;
};

struct Triangle {
    Point A, B, C;

    double area(int method) const;
    bool contains(const Point &P, int method) const;
    bool degenerate() const;
    bool on_border(const Point &P) const;
};

double distance(const Point &p1, const Point &p2);
double heronArea(const Triangle &t);
double gaussArea(const Triangle &t);
double crossProduct(const Point &A, const Point &B, const Point &C);
void runCode();

#endif // TRIANGLE_H