#include "Vect2D.h"
#include "Line.h"
#include <math.h>
#include <iostream>


Vect2D::Vect2D()
{
    Vect2D(0, 0);
}

Vect2D::Vect2D(double x, double y)
{
    this->x = x;
    this->y = y;
}

double Vect2D::length() const
{
	return sqrt(this->x * this->x + this->y * this->y);
}

double distance(Vect2D p1, Vect2D p2)
{
	return (p2 - p1).length();
}

double dot(Vect2D p1, Vect2D p2)
{
	return p1.x * p2.x + p1.y * p2.y;
}

Vect2D Vect2D::normalized() const
{
	double length = this->length();
	return Vect2D(this->x / length, this->y / length);
}

Vect2D Vect2D::operator + (const Vect2D &other) const
{
    return Vect2D(this->x + other.x, this->y + other.y);
}

Vect2D& Vect2D::operator += (const Vect2D &other)
{
    this->x += other.x;
    this->y += other.y;

    return *this;
}

Vect2D Vect2D::operator - (const Vect2D &other) const
{
    return Vect2D(this->x - other.x, this->y - other.y);
}

Vect2D& Vect2D::operator -= (const Vect2D &other)
{
    this->x -= other.x;
    this->y -= other.y;

    return *this;
}

Vect2D Vect2D::operator * (double scalar) const
{
    return Vect2D(this->x * scalar, this->y * scalar);
}

Vect2D& Vect2D::operator *= (double scalar)
{
    this->x *= scalar;
    this->y *= scalar;

    return *this;
}

bool obtuse_angle(Vect2D p1, Vect2D p2, Vect2D p3)
{
	p1 -= p2;
	p3 -= p2;

	if (dot(p1, p3) < 0) {
		return true;
	}

	return false;
}

std::ostream& operator << (std::ostream &os, const Vect2D &v)
{
	os << "(" << v.x << "," << v.y << ")";
	return os;
}

std::istream& operator >> (std::istream &is, Vect2D &v)
{
	is >> v.x >> v.y;
	return is;
}