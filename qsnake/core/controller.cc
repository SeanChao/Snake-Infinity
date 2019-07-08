#include "controller.h"

Controller::Controller() {
    snake = new Snake;
    generateFood();
}

void Controller::updateGame() {
    Log::d("-------------------------------------");
    moveSnake();
    collideDetection();
}

void Controller::moveSnake() {
    snake->move();
}

Point Controller::collideDetection() {
    Log::d("Controller::collideDetection");
    Point head_position = snake->getBodyVertex()[0];
    // check snake and food
    Point food_position = food->getPosition();
    if(head_position==food_position) {
        Log::d("Controller::collideDetection collide with FOOD !!!");
        eatFood();      // TODO: should be renamed to clarify the object being handled
        generateFood();
    }
    // check whether the snake head meets its body
    //debug:
    for (int i = 0; i < snake->getBodyVertexSize(); i++) {
        Log::d("snake_vertex[" + std::to_string(i) + "]\t(" + std::to_string(snake->getBodyVertex()[i].getX())+","+ std::to_string(snake->getBodyVertex()[i].getY())+")");
    }
    for (int  i = 1; i < snake->getBodyVertexSize()-1; i++) {
        Point a = snake->getBodyVertex()[i];
        Point b = snake->getBodyVertex()[i+1];
        if(a.getX()==b.getX() && head_position.getX()==a.getX()) {
            bool flag = (a.getY()<b.getY()) ? true : false;
            if(flag && a.getY() <= head_position.getY() && head_position.getY() <= b.getY()) {
                Log::d("self collide v|1 i="+std::to_string(i)+" flag="+std::to_string(flag));
            }else if(!flag && a.getY() >= head_position.getY() && head_position.getY() >= b.getY()) {
                Log::d("self collide v|2 i="+std::to_string(i)+" flag="+std::to_string(flag));
            }
        }else if(a.getY()==b.getY() && head_position.getY()==a.getY()) {
            bool flag = (a.getX()<b.getX()) ? true : false;
            if(flag && a.getX() <= head_position.getX() && head_position.getX() <= b.getX()) {
                Log::d("self collide h|1 i="+std::to_string(i)+" flag="+std::to_string(flag));
            }else if(!flag && a.getX() >= head_position.getX() && head_position.getX() >= b.getX()) {
                Log::d("self collide h|2 i="+std::to_string(i)+" flag="+std::to_string(flag));
            }
        }
    }
    
    Log::d("Controller::collideDetection finishes");
}

Snake* Controller::getSnake() {
    return snake;
}

void Controller::setSnakeDirection(Snake::Direction d) const {
    snake->setDirection(d);
    Log::d("Controller::setSnakeDirection\tDirection changed to" + std::to_string(d));
}

void Controller::eatFood() {
    Log::d("Controller::eatFood()");
    snake->grow();
    emit updateSnake(QString("SIGNAL_EAT_FOOD"));
}

void Controller::generateFood() {
    srand(time(NULL));
    int point[2];
    for (int i = 0; i < 2; i++){
        int p;
        do{
            p = rand()%800;
        }while(p%20!=0);
        point[i]=p;
    }
    food = new Food(Point(point[0], point[1]));
}

bool Controller::foodHidden() const {
    return food->getHidden();
}

bool Controller::foodExists() const{
    return food == NULL;
}

Point Controller::getFoodPosition() const {
    return food->getPosition();
}