#include "Line.h"
#include "Vect2D.h"

#include <iostream>

Line::Line()
{
    Line(Vect2D(), Vect2D(1, 0));
}

Line::Line(Vect2D p1, Vect2D p2)
{
    this->p1 = p1;
    this->p2 = p2;
}

/*
 * Metoda care returneaza o linie paralela.
 * distance -> distanta liniei paralele fata de linia originala
 * hint -> punctul care determina partea pe care e trasata paralela.
 */
Line Line::parallel(double distance, const Vect2D &hint) const
{
	Vect2D vect = p2 - p1;
	Vect2D perpendicular = Vect2D(vect.y, -vect.x).normalized();

	if (not this->same_side(perpendicular + p1, hint)) {
		perpendicular *= -1;
	}

	perpendicular *= distance;

    return Line(this->p1 + perpendicular, this->p2 + perpendicular);
}


Vect2D Line::intersection(const Line &line) const
{
    double x1 = this->p1.x;
    double y1 = this->p1.y;
    double x2 = this->p2.x;
    double y2 = this->p2.y;

    double x3 = line.p1.x;
    double y3 = line.p1.y;
    double x4 = line.p2.x;
    double y4 = line.p2.y;

    double xi, yi;

    xi = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) /
        ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

    yi = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) /
        ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

    return Vect2D(xi, yi);
}


Line Line::perpendicular(const Vect2D &point) const
{
	Vect2D segment = p2 - p1;
	Vect2D direction = Vect2D(-segment.y, segment.x);

	return Line(point, point + direction);
}


double Line::side(const Vect2D &point) const
{
	double x1 = this->p1.x;
    double y1 = this->p1.y;

    double x2 = this->p2.x;
    double y2 = this->p2.y;

    double x = point.x;
    double y = point.y;

    return (x - x1) * (y2 - y1) - (y - y1) * (x2 - x1);
}


bool Line::same_side(const Vect2D &p1, const Vect2D &p2) const
{
	if (this->side(p1) * this->side(p2) > 0) {
        return true;
    }
    return false;
}