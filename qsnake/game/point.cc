#include "Point.h"

Point::Point(/* args */) {}

Point::Point(int x, int y) : x(x), y(y) {}

Point::~Point() {}

int Point::getX() const { return x; }

void Point::setX(int x) { this->x = x; }

int Point::getY() const { return y; }

void Point::setY(int y) { this->y = y; }

Point Point::adjPoint(Direction d) {
    switch (d) {
        case Up:
            return Point(getX(), getY() - 1);
            break;
        case Down:
            return Point(getX(), getY() + 1);
            break;
        case Left:
            return Point(getX() - 1, getY());
            break;
        case Right:
            return Point(getX() + 1, getY());
            break;
        default:
            return Point(-1, -1);
            break;
    }
}

bool Point::operator==(const Point &r) const {
    return (this->x == r.x) && (this->y == r.y);
}