#include <QPainter>

#include "food.h"

Food::Food() {
    food_type = FoodTypes::Normal;
}

Food::Food(Point position):Food() {
    this->position = position;
    hidden = false;
}

Food::~Food(){

}

bool Food::getHidden() const{
    return hidden;
}

void Food::setHidden(bool hidden) {
    this->hidden = hidden;
}

Point Food::getPosition() const{
    return position;
}

Food::FoodType Food::getFoodType() const{
    return food_type;
}