#include <iostream>
#include "Robot.h"
#include "Triangle.h"
#include "Vect2D.h"
#include "Polygon.h"

int main(int argc, char **argv) {
	Robot robot;
	Polygon room;
	int corners;
	std::vector<Vect2D> p;

	if (argc != 2) {
		return 1;
	}

	std::cin >> robot.radius;

	std::cin >> corners;

	for (int i = 0; i < corners; ++i) {
		Vect2D point;
		std::cin >> point;
		p.push_back(point);
	}

	room = Polygon(p);

	robot.init(room, atoi(argv[1]));
	robot.fill_room();

	return 0;
}

