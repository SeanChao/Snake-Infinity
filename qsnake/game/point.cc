#include "Point.h"

Point::Point(/* args */) {}

Point::Point(int x, int y): x(x), y(y){}

Point::~Point() {}

int Point::getX() const{
    return x;
}

void Point::setX(int x) {
    this->x = x;
}

int Point::getY() const{
    return y;
}

void Point::setY(int y) {
    this->y = y;
}