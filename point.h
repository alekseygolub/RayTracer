#ifndef POINT_H
#define POINT_H


struct Point {
    double x, y, z;

    Point(double x = 0, double y = 0, double z = 0);

    double len();

    Point operator+(Point);

    Point operator-(Point);

    Point operator*(double d);

    double operator*(Point);

    void normalize();

    Point rotate(Point v, double a);
};

#endif // POINT_H
