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
        double length_rate = 0.3;
        if (abs(x - brick_point.at(i - 1).getX()) >=
                length_rate * cell_number ||
            abs(y - brick_point.at(i - 1).getY()) >= length_rate * cell_number)
            continue;
        else
            brick_point.push_back(Point(x, y));
        i++;
    }
}

Brick::~Brick() {}

bool Brick::inBrick(const Point& p) const {
    int x = p.getX();
    int y = p.getY();
    bool in = false;
    for (int i = 0; i < brick_point.size() - 1; i++) {
        Point a = brick_point.at(i);
        Point b = brick_point.at(i + 1);
        if (a.getX() == b.getX() && x == a.getX()) {
            bool flag = (a.getY() < b.getY()) ? true : false;
            if (flag && a.getY() <= y && y <= b.getY()) {
                // Log::d("inBrick v|1 i=" + std::to_string(i) +
                //        " flag=" + std::to_string(flag));
                in = true;
            } else if (!flag && a.getY() >= y && y >= b.getY()) {
                // Log::d("inBrick v|2 i=" + std::to_string(i) +
                //        " flag=" + std::to_string(flag));
                in = true;
            }
        } else if (a.getY() == b.getY() && y == a.getY()) {
            bool flag = a.getX() < b.getX();
            if (flag && a.getX() <= x && x <= b.getX()) {
                // Log::d("inBrick h|1 i=" + std::to_string(i) +
                //        " flag=" + std::to_string(flag));
                in = true;
            } else if (!flag && a.getX() >= x && x >= b.getX()) {
                // Log::d("inBrick h|2 i=" + std::to_string(i) +
                //        " flag=" + std::to_string(flag));
                in = true;
            }
        }
    }
    // Log::d("inBrick returned " + std::to_string(in));
    return in;
}

std::vector<Point>* Brick::getBrick() { return &brick_point; }
