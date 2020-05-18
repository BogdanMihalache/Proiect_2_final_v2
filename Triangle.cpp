#include "Triangle.h"
#include "Line.h"
#include "Circle.h"


Triangle::Triangle()
{
    Triangle(Vect2D(), Vect2D(), Vect2D());
}

Triangle::Triangle(Vect2D p1, Vect2D p2, Vect2D p3)
{
    this->p[0] = p1;
    this->p[1] = p2;
    this->p[2] = p3;
}


Circle Triangle::smallest_circle()
{
    if (obtuse_angle(p[0], p[1], p[2]) ||
        obtuse_angle(p[1], p[0], p[2]) ||
        obtuse_angle(p[0], p[2], p[1])) {

        Vect2D p1 = p[0];
        Vect2D p2 = p[1];

        if (distance(p1, p2) > distance(p[1], p[2])) {
            p1 = p[1];
            p2 = p[2];
        }

        if (distance(p1, p2) > distance(p[0], p[2])) {
            p1 = p[2];
            p2 = p[0];
        }

        Circle circle;
        circle.radius = distance(p1, p2) / 2;
        circle.position = (p1 + p2) * 0.5;

        return circle;
    }

    Vect2D middle1 = (p[0] + p[1]) * 0.5;
    Vect2D middle2 = (p[1] + p[2]) * 0.5;

    Line perpendicular1 = Line(p[0], p[1]).perpendicular(middle1);
    Line perpendicular2 = Line(p[1], p[2]).perpendicular(middle2);

    Circle circle;
    circle.position = perpendicular1.intersection(perpendicular2);
    circle.radius = distance(circle.position, p[0]);

    return circle;
}