#include "controller.h"

#define str std::to_string

/**
 * This is the controller of the game.
 * The controller works as router to transfer commands from GameWidget
 * to associating with snake, food, etc and
 * convey properties of game elements to the GameWidget.
 */
Controller::Controller(int player, int cell_number)
    : cell_number(cell_number), mode(player) {
    // snake = new Snake;
    snakeList = new Snake*[player];
    srand(time(NULL));
    for (int i = 0; i < player; i++) {
        /**
         * TODO: rebuild the Snake Constructor so that controller
         * can set the initial range of the snake head
         */
        Log::d("time(NULL): " + str(time(NULL)));
        int point_x = rand() % cell_number;
        int point_y = rand() % cell_number;
        Log::d("the initial position of the snake is: (" + str(point_x) + ", " +
               str(point_y) + ")");
        Point head_point = Point(point_x, point_y);
        snakeList[i] = new Snake(&head_point);
        Log::d("snake is constructed");
    }
    cell_number = 1;
    generateFood();
    score = 0;
}

void Controller::updateGame() {
    Log::d("----------------------------------------");
    moveSnake();
    for (int i = 0; i < mode; i++) {
        collideDetection(i);
    }
    // debug:
    // snake vertices
    for (int snake_index = 0; snake_index < mode; snake_index++) {
        Snake* snake = snakeList[snake_index];
        for (int i = 0; i < snake->getBodyVertexSize(); i++) {
            Log::d("snake_vertex[" + std::to_string(i) + "]\t(" +
                   std::to_string(snake->getBodyVertex()[i].getX()) + "," +
                   std::to_string(snake->getBodyVertex()[i].getY()) + ")");
        }
    }
    // food position
    Log::d("food @(" + std::to_string(food->getPosition().getX()) + ", " +
           std::to_string(food->getPosition().getY()) +
           ") food_t: " + str(food->getFoodType()));
    Log::d("score: " + std::to_string(score));
}

void Controller::moveSnake() {
    for (int snake_index = 0; snake_index < mode; snake_index++) {
        snakeList[snake_index]->move();
    }
}

void Controller::collideDetection(int index) {
    Point head_position = snakeList[index]->getBodyVertex()[0];
    // check snake and food
    Point food_position = food->getPosition();

    if (head_position == food_position) {
        Log::d("Controller::collideDetection collide with FOOD !!!");
        eatFood(index);  // TODO: should be renamed to clarify the object being
                         // handled
        generateFood();

        // food effect handler:
        auto foodType = food->getFoodType();
        switch (foodType) {
            case Food::FoodTypes::Ice:
                emit scaleSpeed(0.8);
                break;
            case Food::FoodTypes::Fire:
                emit scaleSpeed(1.25);
                break;
            case Food::FoodTypes::Normal:
                emit scaleSpeed(0);
                break;
            case Food::FoodTypes::Poisoned:
                break;
            default:
                break;
        }
    }
    // check whether the snake head meets its body
    for (int i = 1; i < snakeList[index]->getBodyVertexSize() - 1; i++) {
        Point a = snakeList[index]->getBodyVertex()[i];
        Point b = snakeList[index]->getBodyVertex()[i + 1];
        if (a.getX() == b.getX() && head_position.getX() == a.getX()) {
            bool flag = a.getY() < b.getY();
            if (flag && a.getY() <= head_position.getY() &&
                head_position.getY() <= b.getY()) {
                Log::d("self collide v|1 i=" + std::to_string(i) +
                       " flag=" + std::to_string(flag));
            } else if (!flag && a.getY() >= head_position.getY() &&
                       head_position.getY() >= b.getY()) {
                Log::d("self collide v|2 i=" + std::to_string(i) +
                       " flag=" + std::to_string(flag));
            }
        } else if (a.getY() == b.getY() && head_position.getY() == a.getY()) {
            bool flag = a.getX() < b.getX();
            if (flag && a.getX() <= head_position.getX() &&
                head_position.getX() <= b.getX()) {
                Log::d("self collide h|1 i=" + std::to_string(i) +
                       " flag=" + std::to_string(flag));
            } else if (!flag && a.getX() >= head_position.getX() &&
                       head_position.getX() >= b.getX()) {
                Log::d("self collide h|2 i=" + std::to_string(i) +
                       " flag=" + std::to_string(flag));
            }
        }
    }
    // check whether the snake collide with the wall
    // currently the wall is from
    // UP: (0,0) to (800, 0) DOWN: (0, 800) to (800, 800)
    // LEFT: (0, 0) to (0, 800) RIGHT(800, 0) to (800, 800)
    if (head_position.getX() < 0 || head_position.getX() >= cell_number ||
        head_position.getY() < 0 || head_position.getY() >= cell_number) {
        Log::d("Hit the wall!!!");
        // restart();
    }
}

void Controller::setSnakeDirection(Snake::Direction d, int index) const {
    if (index >= mode)
        return;
    snakeList[index]->setDirection(d);
    Log::d("Controller::setSnakeDirection\tget direction: " +
           std::to_string(d));
}

Point* Controller::getSnakeVertices(int index) const {
    return snakeList[index]->getBodyVertex();
}

int Controller::getSnakeVerticesSize(int index) const {
    return snakeList[index]->getBodyVertexSize();
}

void Controller::eatFood(int index) {
    Log::d("Controller::eatFood()");
    snakeList[index]->grow();
    emit updateSnake(QString("SIGNAL_EAT_FOOD"));
    score += 10;
}

/**
 * Points in generateFood() is **logical**.
 */
void Controller::generateFood(int index) {
    Log::d("Controller::generateFood cell_number: " + str(cell_number));
    Log::d("time(NULL): " + str(time(NULL)));
    int point[2];
    do {
        for (int i = 0; i < 2; i++) {
            point[i] = rand() % cell_number;
        }
        food = new Food(Point(point[0], point[1]));
        Log::d("Controller::generateFood in random part get: " + str(point[0]) +
               " " + str(point[1]));
    } while (snakeList[index]->inBody(Point(point[0], point[1])));
    Log::d("Controller::generateFood() cell_number:" +
           std::to_string(cell_number));
}

bool Controller::foodHidden() const { return food->getHidden(); }

bool Controller::foodExists() const { return food == NULL; }

Point Controller::getFoodPosition() const { return food->getPosition(); }

Food::FoodType Controller::getFoodType() const {
    return food->getFoodType();
}

int Controller::getScore() const { return score; };

int Controller::getSnakeNumber() const { return mode; }

void Controller::setScore(int new_score) { score = new_score; }

void Controller::setCellNumber(int n) {
    cell_number = n;
    generateFood();
}

void Controller::setPlayer(int player) { this->mode = player; }

void Controller::restart() {
    for (int i = 0; i < mode; i++) {
        Snake* old = snakeList[i];
        snakeList[i] = new Snake;
        score = 0;
        delete old;
    }
}
