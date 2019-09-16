#include "snake.h"
#include "../log/log.h"

/**
 * Logical Positioning:
 * the point refers to the "cell" in the grassland 
 */
Snake::Snake() {
    vertex_size = 1;
    body_vertex = new Point[vertex_size];
    body_vertex[0] = Point(0, 0);
    sloughed_tail = body_vertex[0];
    direction = buffered_direction = RIGHT;
    step = 1;
    digestFood = false;
    score = 0;
}

/**
 * generate the snake at the specified point
 */
Snake::Snake(Point* point): Snake() {
    body_vertex[0] = *point;
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
    buffered_direction = d;
    Log::d("snake direction changed to"+std::to_string(d));
}

void Snake::move() {
    // if the snake needs to change direction:
    // copy the head and reset the direction
    if (direction != buffered_direction) {
        Point* tmp = body_vertex;
        body_vertex = new Point[++vertex_size];
        for (int i = 0; i < vertex_size - 1; i++) {
            body_vertex[i + 1] = tmp[i];
        }
        body_vertex[0] = body_vertex[1];
        delete[] tmp;
        direction = buffered_direction;
    }

    sloughed_tail = body_vertex[vertex_size - 1];  // backup last tail
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
    if (vertex_size == 1)
        return;
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
}

void Snake::grow() {
    // Log::d("digest food is set to TRUE");
    // digestFood = true;
    // lengthen the head accroding to the direction
    // the right strategy is hold the position of its tail.
    // but according to the hierarchy, i need to implement this in another way
    // after collide with food copy its original tail as if it didn't move:
    Log::d("Snake::grow()");
    Log::d("Snake::grow()\t sloughed_tail=(" + std::to_string(sloughed_tail.getX()) + " ," + std::to_string(sloughed_tail.getY()) + ")");
    // copy the tail (last time)
    Point* tmp = body_vertex;
    body_vertex = new Point[++vertex_size];
    for (int i = 0; i < vertex_size; i++) {
        body_vertex[i] = tmp[i];
    }
    body_vertex[vertex_size - 1] = sloughed_tail;
}

Snake::Direction Snake::getDirection() const { return direction; }

Point* Snake::getBodyVertex() const { return body_vertex; }

int Snake::getBodyVertexSize() const { return vertex_size; }

bool Snake::getDigestFood() const {
    return digestFood;
}

bool Snake::inBody(const Point& p) {
    int x = p.getX();
    int y = p.getY();
    bool in = false;
    for (int i = 0; i < vertex_size - 1; i++) {
        Point a = body_vertex[i];
        Point b = body_vertex[i + 1];
        if (a.getX() == b.getX() && x == a.getX()) {
            bool flag = (a.getY() < b.getY()) ? true : false;
            if (flag && a.getY() <= y && y <= b.getY()) {
                Log::d("inBody v|1 i=" + std::to_string(i) + " flag=" + std::to_string(flag));
                in = true;
            } else if (!flag && a.getY() >= y && y >= b.getY()) {
                Log::d("inBody v|2 i=" + std::to_string(i) + " flag=" + std::to_string(flag));
                in = true;
            }
        } else if (a.getY() == b.getY() && y == a.getY()) {
            bool flag = (a.getX() < b.getX()) ? true : false;
            if (flag && a.getX() <= x && x <= b.getX()) {
                Log::d("inBody h|1 i=" + std::to_string(i) + " flag=" + std::to_string(flag));
                in = true;
            } else if (!flag && a.getX() >= x && x >= b.getX()) {
                Log::d("inBody h|2 i=" + std::to_string(i) + " flag=" + std::to_string(flag));
                in = true;
            }
        }
    }
    Log::d("inPlace returned " + std::to_string(in));
    return in;
}