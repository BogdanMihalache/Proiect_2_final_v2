#ifndef VECT2D_H_
#define VECT2D_H_

#include <iostream>

struct Line;

struct Vect2D {

    double x;
    double y;

    Vect2D();
    Vect2D(double x, double y);

	double length() const;
	Vect2D normalized() const;

    Vect2D operator + (const Vect2D &other) const;
    Vect2D& operator += (const Vect2D &other);

    Vect2D operator - (const Vect2D &other) const;
    Vect2D& operator -= (const Vect2D &other);

	Vect2D operator * (double scalar) const;
	Vect2D& operator *= (double scalar);
};

double dot(Vect2D p1, Vect2D p2);
double distance(Vect2D p1, Vect2D p2);
bool obtuse_angle(Vect2D p1, Vect2D p2, Vect2D p3);

std::ostream& operator << (std::ostream &os, const Vect2D &v);
std::istream& operator >> (std::istream &is, Vect2D &v);

#endif // VECT2D_H_