#include "Circle.h"


Circle::Circle()
{
	Circle(Vect2D(), 1.0);
}

Circle::Circle(Vect2D position, double radius)
{
	this->position = position;
	this->radius = radius;
}

bool Circle::contains(Vect2D point)
{
	if (distance(point, position) < radius + EPS)
	{
		return true;
	}
	return false;
}