#include "controller.h"

Controller::Controller() {
    snake = new Snake;
}

void Controller::moveSnake() {

}

Snake* Controller::getSnake() {
    return snake;
}

void Controller::setSnakeDirection(Snake::Direction d) const{
    snake->setDirection(d);
    Log::d("Controller::setSnakeDirection\tDirection changed to" + std::to_string(d));
}