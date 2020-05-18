#ifndef ROBOT_H_
#define ROBOT_H_

#include "Vect2D.h"
#include "Triangle.h"
#include "Polygon.h"


struct Robot {

	Vect2D position;
	double radius;
	int corner;
	bool first_lap;

	Polygon remaining_area;

	bool done;

	bool compensate;
	int compensation_level;

	void init(const Polygon &room, bool compensate);
	void fill_room();
	void next_corner();
	Vect2D compute_target(Vect2D p1, Vect2D p2, Vect2D p3);
	Vect2D compute_secondary_target(Vect2D p1, Vect2D p2, Vect2D p3, int level);
	Line compute_new_edge(Vect2D p1, Vect2D p2, Vect2D p3);
	void log_position();
};

#endif // ROBOT_H_