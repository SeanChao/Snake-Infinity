#include "brick.h"

#define tStr std::to_string

/**
 * TODO: exclude the case of generate a long wall
 */
Brick::Brick(int cell_number) {
    int sides = 0;
    while (sides <= 1) {
        sides = rand() % 5;
    }
    int x, y;
    int i = 1;
    brick_point.push_back(Point(rand() % cell_number, rand() % cell_number));
    while (i <= sides) {
        if (i % 2 == 0) {
            x = rand() % cell_number;
            y = brick_point.at(i - 1).getY();
        } else {
            y = rand() % cell_number;
            x = brick_point.at(i - 1).getX();
        }
        Log::d("create brick @(" + tStr(x) + ", " + tStr(y) + ")");
        if (abs(x - brick_point.at(i - 1).getX()) >= 0.6 * cell_number ||
            abs(y - brick_point.at(i - 1).getY()) >= 0.6 * cell_number)
            continue;
        else
            brick_point.push_back(Point(x, y));
        i++;
    }
}

Brick::~Brick() {}

std::vector<Point>* Brick::getBrick() { return &brick_point; }
