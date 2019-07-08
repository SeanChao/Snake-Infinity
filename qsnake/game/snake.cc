#include "snake.h"
#include "../log/log.h"

Snake::Snake() {
    vertex_size = 4;
    body_vertex = new Point[vertex_size];
    body_vertex[0] = Point(420, 300);
    body_vertex[1] = Point(300, 300);
    body_vertex[2] = Point(300, 100);
    body_vertex[3] = Point(40, 100);
    direction = RIGHT;
    step = 20;
    digestFood = false;
}

Snake::~Snake() {
    // TODO:
}

void Snake::setDirection(Direction d) {
    // UP=0 DOWN=1 LEFT=2 RIGHT=3
    if (direction == d)
        return;
    if (direction + d == 1)
        return;  // if the snake moves UP/DOWN, but try to set to UP/DOWN
    if (direction + d == 5)
        return;  // as above, LEFT/RIGHT
    // copy the head and reset the direction
    Point* tmp = body_vertex;
    body_vertex = new Point[++vertex_size];
    for (int i = 0; i < vertex_size - 1; i++) {
        body_vertex[i + 1] = tmp[i];
    }
    body_vertex[0] = body_vertex[1];
    delete[] tmp;
    direction = d;
}

void Snake::move() {
    // update the position of the head
    switch (direction) {
        case UP:
            body_vertex[0].setY(body_vertex[0].getY() - step);
            break;
        case DOWN:
            body_vertex[0].setY(body_vertex[0].getY() + step);
            break;
        case LEFT:
            body_vertex[0].setX(body_vertex[0].getX() - step);
            break;
        case RIGHT:
            body_vertex[0].setX(body_vertex[0].getX() + step);
            break;
        default:
            break;
    }
    // update the position of the tail
    // special case: after eat food
    if (!digestFood) {
        Log::d("Snake::move no need to digest food");
        sloughed_tail = body_vertex[vertex_size-1];
        int delta_x = body_vertex[vertex_size - 1].getX() - body_vertex[vertex_size - 2].getX();
        int delta_y = body_vertex[vertex_size - 1].getY() - body_vertex[vertex_size - 2].getY();
        // Log::d("Snake::move\tdelta_x=" + std::to_string(delta_x) + "\tdelta_y=" + std::to_string(delta_y));
        if (delta_x == 0) {
            // Log::d("tail should move vertically");
            (delta_y > 0) ? (body_vertex[vertex_size - 1].setY(body_vertex[vertex_size - 1].getY() - step)) : (body_vertex[vertex_size - 1].setY(body_vertex[vertex_size - 1].getY() + step));
        }
        if (delta_y == 0) {
            // Log::d("tail should move horizontally");
            (delta_x > 0) ? (body_vertex[vertex_size - 1].setX(body_vertex[vertex_size - 1].getX() - step))
                          : (body_vertex[vertex_size - 1].setX(body_vertex[vertex_size - 1].getX() + step));
        }
        // if the tail meets its previous vertex
        if (body_vertex[vertex_size - 1].getX() == body_vertex[vertex_size - 2].getX() && body_vertex[vertex_size - 1].getY() == body_vertex[vertex_size - 2].getY()) {
            // Log::d("tail meets its previous vertex");
            vertex_size--;
        }
    }else{
        digestFood = false;
    }
}

void Snake::grow() {
    // Log::d("digest food is set to TRUE");
    // digestFood = true;
    // lengthen the head accroding to the direction
    // the right strategy is hold the position of its tail.
    // but according to the hierarchy, i need to implement this in another way
    // after collide with food copy its original tail as if it didn't move:
    Log::d("Snake::grow(), direction");
    // copy the tail (last time)
    Point *tmp = body_vertex;
    body_vertex = new Point[++vertex_size];
    for (int i = 0; i < vertex_size; i++) {
        body_vertex[i] = tmp[i];
    }
    body_vertex[vertex_size-1] = sloughed_tail;
}

Snake::Direction Snake::getDirection() const { return direction; }

Point* Snake::getBodyVertex() const { return body_vertex; }

int Snake::getBodyVertexSize() const { return vertex_size; }

bool Snake::getDigestFood() const {
    return digestFood;
}