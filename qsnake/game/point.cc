#include "Point.h"

Point::Point(/* args */) {}

Point::Point(int x, int y): x(x), y(y){}

Point::~Point() {}

int Point::getX() {
    return x;
}

int Point::getY() {
    return y;
}