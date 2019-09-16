#ifndef FOOD_H
#define FOOD_H
#include "point.h"

class Food {
   public:
    typedef int FoodType;
    enum FoodTypes { Normal, Ice, Fire, Poisoned };
    Food();
    Food(Point pos);
    ~Food();
    bool getHidden() const;
    void setHidden(bool hidden);
    Point getPosition() const;
    FoodType getFoodType() const;

   private:
    Point position;
    bool hidden;
    FoodType food_type;
};

#endif  // FOOD_H
