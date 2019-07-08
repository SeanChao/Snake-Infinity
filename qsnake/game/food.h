#ifndef FOOD_H
#define FOOD_H
#include "point.h"

class Food {
   public:
    Food();
    Food(Point pos);
    ~Food();
    bool getHidden() const;
    void setHidden(bool hidden);
    Point getPosition() const;

   private:
    Point position;
    bool hidden;
};

#endif  // FOOD_H
