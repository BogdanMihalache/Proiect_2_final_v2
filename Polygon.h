#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>
#include "Vect2D.h"
#include "Circle.h"

struct Polygon {
	std::vector<Vect2D> p;
	int v_count;

	Polygon();
	Polygon(int n);
	Polygon(const std::vector<Vect2D> &p);

	std::vector<int> crop(int i1, int i2, const Line &new_edge);

	bool converged();

	int next_index(int index);
	int prev_index(int index);

	Circle smallest_circle();
};

#endif // SHAPE_H_