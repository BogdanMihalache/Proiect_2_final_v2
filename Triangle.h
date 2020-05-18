#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Vect2D.h"
#include "Circle.h"

struct Triangle {
    Vect2D p[3];

    Triangle();
    Triangle(Vect2D p1, Vect2D p2, Vect2D p3);

	Circle smallest_circle();
};

#endif // TRIANGLE_H_