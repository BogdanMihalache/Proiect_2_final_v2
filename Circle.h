#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Vect2D.h"

#define EPS 0.0001


struct Circle {
	Vect2D position;
	double radius;

	Circle();
	Circle(Vect2D position, double radius);

	bool contains(Vect2D point);
};

#endif // CIRCLE_H_
