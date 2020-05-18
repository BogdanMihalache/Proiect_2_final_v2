#ifndef LINE_H_
#define LINE_H_

#include "Vect2D.h"


struct Line {
	/*
	 * Punctele care definesc linia.
	 */
    Vect2D p1;
    Vect2D p2;

    Line();
    Line(Vect2D p1, Vect2D p2);

    Line parallel(double distance, const Vect2D &hint) const;
    Vect2D intersection(const Line &line) const;
	Line perpendicular(const Vect2D &point) const;

	double side(const Vect2D &point) const;
	bool same_side(const Vect2D &p1, const Vect2D &p2) const;
};

#endif // LINE_H_