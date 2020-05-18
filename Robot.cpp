#include "Robot.h"
#include "Line.h"
#include "Vect2D.h"
#include <iostream>


void Robot::init(const Polygon &room, bool compensate)
{
    Line edge1 = Line(room.p.front(), room.p[1]);
    Line edge2 = Line(room.p.front(), room.p.back());

    Line line1 = edge1.parallel(this->radius, room.p.back());
    Line line2 = edge2.parallel(this->radius, room.p[1]);

    this->position = line1.intersection(line2);

    this->first_lap = true;
    this->compensate = compensate;
    this->compensation_level = 0;

    this->remaining_area = room;
    this->done = false;
    this->corner = 0;
    this->log_position();
}


void Robot::fill_room()
{
    while (not this->done) {
        this->next_corner();
    }
}


void Robot::next_corner()
{
    int first = corner;
    int second = remaining_area.next_index(first);
    int third = remaining_area.next_index(second);

    Circle circle = remaining_area.smallest_circle();

    if (circle.radius < radius) {
        this->done = true;
        this->position = circle.position;
        this->log_position();
        return;
    }

    if (second < first && first_lap) {
        first_lap = false;
        compensation_level = 2;
    }

    if (second > first && not first_lap) {
        compensation_level = 1;
    }

    Vect2D target = compute_target(remaining_area.p[first],
                                   remaining_area.p[second],
                                   remaining_area.p[third]);

    Line new_edge = compute_new_edge(remaining_area.p[first],
                                     remaining_area.p[second],
                                     remaining_area.p[third]);

    if (compensate && compensation_level != 0) {
        Vect2D secondary_target = compute_secondary_target(remaining_area.p[first],
                                                           remaining_area.p[second],
                                                           remaining_area.p[third],
                                                           compensation_level);

        this->position = secondary_target;
        this->log_position();
    }

    std::vector<int> cropped_i;

    Polygon area_backup = remaining_area;

    cropped_i = remaining_area.crop(first, second, new_edge);

    if (remaining_area.converged()) {
        this->done = true;
    }

    this->position = target;
    this->log_position();

    if (not this->done && compensation_level != 0) {
        for (int i : cropped_i) {
            int next = area_backup.next_index(i);
            int prev = area_backup.prev_index(i);

            if (compensate) {
                target = compute_target(area_backup.p[prev],
                                        area_backup.p[i],
                                        area_backup.p[next]);

                Vect2D secondary_target = compute_secondary_target(area_backup.p[prev],
                                                                   area_backup.p[i],
                                                                   area_backup.p[next], 1);

                this->position = secondary_target;
                this->log_position();
            }

            this->position = target;
            this->log_position();

        }
    }

    corner = remaining_area.next_index(corner);
}


Vect2D Robot::compute_target(Vect2D p1, Vect2D p2, Vect2D p3)
{
    Line edge1 = Line(p2, p1);
    Line edge2 = Line(p2, p3);

    Line line1 = edge1.parallel(this->radius, p3);
    Line line2 = edge2.parallel(this->radius, p1);

    Vect2D target = line1.intersection(line2);

    return target;
}


Vect2D Robot::compute_secondary_target(Vect2D p1, Vect2D p2, Vect2D p3, int level)
{
    Line edge1 = Line(p2, p1);
    Line edge2 = Line(p2, p3);

    Line line1 = edge1.parallel(this->radius, p3);

    if (level == 2) {
        Line line2 = edge2.parallel(-this->radius, p1);

        return line2.intersection(line1);
    }

    if (level == 1) {
        Line line2 = edge1.perpendicular(p2);

        return line2.intersection(line1);
    }

    return Vect2D();
}


Line Robot::compute_new_edge(Vect2D p1, Vect2D p2, Vect2D p3)
{
    Line edge1 = Line(p2, p1);

    Line new_edge = edge1.parallel(2 * this->radius, p3);

    return new_edge;
}


void Robot::log_position()
{
    std::cout << this->position << " ";
    for (int i = 0; i < remaining_area.v_count; ++i) {
        std::cout << this->remaining_area.p[i] << " ";
    }
    std::cout << std::endl;
}