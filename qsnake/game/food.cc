#include <QPainter>

#include "food.h"

Food::Food() {
}

Food::Food(Point position) {
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