#include "point.h"
#include <math.h>

Point::Point(double x, double y, double z): x(x), y(y), z(z) {}

double Point::len() {
    return sqrt(x * x + y * y + z * z);
}

Point Point::operator+(Point p) {
    return Point(x + p.x, y + p.y, z + p.z);
}

Point Point::operator-(Point p) {
    return Point(x - p.x, y - p.y, z - p.z);
}

double Point::operator*(Point p) {
    return x * p.x + y * p.y + z * p.z;
}

Point Point::operator*(double d) {
    return Point(x * d, y * d, z * d);
}

void Point::normalize() {
    double l = len();
    x /= l;
    y /= l;
    z /= l;
}

Point Point::rotate(Point v, double a) {
    v.normalize();
    double nx = x * (cos(a) + (1 - cos(a)) * v.x * v.x) +
                y * ((1 - cos(a)) * v.y * v.x + sin(a) * v.z) +
                z * ((1 - cos(a)) * v.z * v.x - sin(a) * y);
    double ny = x * ((1 - cos(a)) * v.x * v.y - sin(a) * v.z) +
                y * (cos(a) + (1 - cos(a)) * v.y * v.y) +
                z * ((1 - cos(a)) * v.z * v.y + sin(a) * v.x);
    double nz = x * ((1 - cos(a)) * v.x * v.z + sin(a) * v.y) +
                y * ((1 - cos(a)) * v.y * v.z + sin(a) * v.x) +
                z * (cos(a) + (1 - cos(a)) * v.z * v.z);
    return Point(nx, ny, nz);
}
