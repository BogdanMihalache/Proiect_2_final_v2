#include "Polygon.h"
#include "Line.h"
#include "Triangle.h"

#define EPS 0.0001


Polygon::Polygon()
{
    Polygon(3);
}

Polygon::Polygon(int n)
{
    this->p = std::vector<Vect2D>(n, Vect2D());
    v_count = n;
}

Polygon::Polygon(const std::vector<Vect2D> &p)
{
    this->p = p;
    v_count = p.size();
}


std::vector<int> Polygon::crop(int i1, int i2, const Line &new_edge)
{
    Vect2D new_p2;
    Vect2D new_p1;
    bool found_p1 = false;
    bool found_p2 = false;

    // primii indici in interiorul noului poligon decupat
    int last_i2;
    int last_i1;

    // se cauta prima latura taiata de dreapta care decupeaza poligonul
    for (int i = i2; i != i1; i = (i + 1) % v_count)
    {
        int j = (i + 1) % v_count;
        if (!new_edge.same_side(p[i], p[j])) {
            new_p2 = new_edge.intersection(Line(p[i], p[j]));
            found_p2 = true;
            last_i2 = j;
            break;
        }
    }

    // se cauta a doua latura taiata de dreapta care decupeaza poligonul
    for (int i = i1; i != i2; i = (i + v_count - 1) % v_count)
    {
        int j = (i + v_count - 1) % v_count;
        if (!new_edge.same_side(p[i], p[j])) {
            new_p1 = new_edge.intersection(Line(p[i], p[j]));
            found_p1 = true;
            last_i1 = j;
            break;
        }
    }

    // daca nu s-a gasit nicio latura decupata, inseamna ca tot poligonul a fost decupat
    if (not found_p1 || not found_p2) {
        for (int i = 1; i < v_count; ++i) {
            p[i] = p[i2];
        }
        return {};
    }

    std::vector<int> cropped_i;

    // se adauga in vector varfurile unice (care nu se suprapun) aflate dupa varful i2
    for (int i = (i2 + 1) % v_count; i != last_i2; i = (i + 1) % v_count)
    {
        p[i] = new_p2;
        bool duplicate = false;
        for (unsigned int j = 0; j < cropped_i.size(); ++j) {
            if (distance(p[i], p[j]) < EPS) {
                duplicate = true;
                break;
            }
        }
        if (not duplicate) {
            cropped_i.push_back(i);
        }
    }

    // punctele de dinainte de i1 sunt acumulate intr-unul din punctele formate in urma decuparii
    for (int i = i1; i != last_i1; i = (i + v_count - 1) % v_count)
    {
        p[i] = new_p1;
    }

    // punctele  de dupa i2 sunt acumulate in celalalt punct rezultat in urma decuparii
    for (int i = i2; i != i1; i = (i + v_count - 1) %v_count)
    {
        p[i] = new_p2;
    }

    return cropped_i;
}


bool Polygon::converged() {
    int edges = 0;
    for (int i = 0; i < v_count; ++i)
    {
        int j = (i + 1) % v_count;
        if (distance(p[i], p[j]) > EPS)
        {
            edges++;
        }
    }

    if (edges > 2) {
        return false;
    }
    return true;
}


int Polygon::next_index(int index)
{
    int next = (index + 1) % v_count;
    while (distance(p[index], p[next]) < EPS && next != index)
    {
        next = (next + 1) % v_count;
    }

    return next;
}


int Polygon::prev_index(int index)
{
    int prev = (index + v_count - 1) % v_count;
    while (distance(p[index], p[prev]) < EPS && prev != index)
    {
        prev = (prev + v_count - 1) % v_count;
    }

    return prev;
}


Circle Polygon::smallest_circle()
{
    Circle circle(Vect2D(), 1000000);
    for (int i = 0; i < v_count - 2; ++i) {
        for (int j = i + 1; j < v_count - 1; ++j) {
            for (int k = j + 1; k < v_count; ++k) {
                Circle aux = Triangle(p[i], p[j], p[k]).smallest_circle();
                bool ok = true;
                for (int l = 0; l < v_count; ++l) {
                    if (!aux.contains(p[l])) {
                        ok = false;
                        break;
                    } else {
                    }
                }
                if (ok && aux.radius < circle.radius) {
                    circle = aux;
                }
            }
        }
    }

    return circle;
}