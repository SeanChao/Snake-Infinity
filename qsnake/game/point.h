#ifndef POINT_H
#define POINT_H

#include "../log/log.h"

class Point {
   private:
    // the cordinate of the Point
    int x;
    int y;

   public:
    Point();
    Point(int x, int y);
    ~Point();
    
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);

    bool operator==(const Point &r) const;
};
#endif  // POINT_H