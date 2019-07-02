#include "snake.h"

Snake::Snake() {
    body_vertex = new Point[3];
    body_vertex[0] = Point(20,30);
    body_vertex[1] = Point(40,30);
    body_vertex[2] = Point(40,80);
    vertex_counter = 3;
}

Snake::~Snake() {}

Point* Snake::getBodyVertex() {
    return body_vertex;
}

int Snake::getBodyVertexSize() {
    return vertex_counter;
}