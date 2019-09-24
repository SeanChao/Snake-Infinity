#ifndef POINT_H
#define POINT_H

#include "../log/log.h"

class Point {
   private:
    // the cordinate of the Point
    int x;
    int y;

   public:
    enum Direction { Up, Down, Left, Right };
    Point();
    Point(int x, int y);
    ~Point();
    
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
    Point adjPoint(Direction d);

    bool operator==(const Point &r) const;
};
#endif  // POINT_H