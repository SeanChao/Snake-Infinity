#include "controller.h"
#include <QObject>
#include <queue>

#define tStr std::to_string

/**
 * This is the controller of the game.
 * The controller works as router to transfer commands from GameWidget
 * to associating with snake, food, etc and
 * convey properties of game elements to the GameWidget.
 */
Controller::Controller(int player, int cell_number, bool ai)
    : ai_enabled(ai), round(0), cell_number(cell_number), mode(player) {
    snakeList = new Snake*[player];
    brick = new Brick(cell_number);

    for (int i = 0; i < player; i++) {
        /**
         * TODO: rebuild the Snake Constructor so that controller
         * can set the initial range of the snake head
         */
        Log::d("time(NULL): " + tStr(time(NULL)));
        int point_x = rand() % cell_number;
        int point_y = rand() % cell_number;
        Log::d("the initial position of the snake is: (" + tStr(point_x) +
               ", " + tStr(point_y) + ")");
        Point head_point = Point(point_x, point_y);
        snakeList[i] = new Snake(&head_point);
        Log::d("snake is constructed");
    }
    generateFood();
    score = 0;

    if (ai_enabled) {
        ai_path = bfsFindPath();
        emit changeSpeed(100);
    }
    Log::d("generate bfsPath done");
    updateState = true;
}

void Controller::updateGame() {
    if (!updateState) return;
    Log::d("----------------------------------------");
    round++;
    moveSnake();
    for (int i = 0; i < mode; i++) {
        collideDetection(i);
    }
    if (round % 100 == 0 && !ai_enabled) {
        brick = new Brick(cell_number);
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
           ") food_t: " + tStr(food->getFoodType()));
    Log::d("score: " + std::to_string(score));
    // debug: bricks
    // std::vector<Point>* bricks = getBrickVertices();
    // auto sides = bricks->size();
    // for (auto i = 0; i < sides; i++) {
    //     Log::d("brick @(" + tStr(bricks->at(i).getX()) + ", " +
    //            tStr(bricks->at(i).getY()) + ")");
    // }
}

void Controller::moveSnake() {
    if (ai_enabled && !ai_path.empty()) {
        // follow AI path
        Point head = getSnakeVertices()[0];
        Point next_p;

        next_p = ai_path.at(0);
        ai_path.erase(ai_path.begin());

        Log::d("remain steps: " + tStr(ai_path.size()));
        Log::d("head point should be(" + tStr(head.getX()) + ", " +
               tStr(head.getY()) + ")");
        Log::d("next point should be(" + tStr(next_p.getX()) + ", " +
               tStr(next_p.getY()) + ")");
        if (head.getX() == next_p.getX()) {
            Snake::Direction d = snakeList[0]->getDirection();
            bool flag = head.getY() > next_p.getY();
            if (d == Snake::LEFT) {
                if (flag) {
                    snakeList[0]->setDirection(Snake::UP);
                    Log::d("turn Up");
                } else {
                    snakeList[0]->setDirection(Snake::DOWN);
                    Log::d("turn Down");
                }
            } else if (d == Snake::RIGHT) {
                if (flag) {
                    snakeList[0]->setDirection(Snake::UP);
                    Log::d("turn Up");
                }

                else {
                    snakeList[0]->setDirection(Snake::DOWN);
                    Log::d("turn Down");
                }
            }
        }
        if (head.getY() == next_p.getY()) {
            Snake::Direction d = snakeList[0]->getDirection();
            bool flag = head.getX() > next_p.getX();
            if (d == Snake::UP) {
                if (flag) {
                    snakeList[0]->setDirection(Snake::LEFT);
                    Log::d("turn Left");
                } else {
                    snakeList[0]->setDirection(Snake::RIGHT);
                    Log::d("turn Right");
                }
            } else if (d == Snake::DOWN) {
                if (flag) {
                    snakeList[0]->setDirection(Snake::LEFT);
                    Log::d("turn Left");
                }

                else {
                    snakeList[0]->setDirection(Snake::RIGHT);
                    Log::d("turn Right");
                }
            }
        }
    }
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
        handleFoodEffect();
        generateFood();
        if (ai_enabled) ai_path = bfsFindPath();
    }
    // check whether the snake's head meets its body
    for (int i = 1; i < snakeList[index]->getBodyVertexSize() - 1; i++) {
        Point a = snakeList[index]->getBodyVertex()[i];
        Point b = snakeList[index]->getBodyVertex()[i + 1];
        if (a.getX() == b.getX() && head_position.getX() == a.getX()) {
            bool flag = a.getY() < b.getY();
            if (flag && a.getY() <= head_position.getY() &&
                head_position.getY() <= b.getY()) {
                Log::d("self collide v|1 i=" + std::to_string(i) +
                       " flag=" + std::to_string(flag));
                emit gameOver();
            } else if (!flag && a.getY() >= head_position.getY() &&
                       head_position.getY() >= b.getY()) {
                Log::d("self collide v|2 i=" + std::to_string(i) +
                       " flag=" + std::to_string(flag));
                emit gameOver();
            }
        } else if (a.getY() == b.getY() && head_position.getY() == a.getY()) {
            bool flag = a.getX() < b.getX();
            if (flag && a.getX() <= head_position.getX() &&
                head_position.getX() <= b.getX()) {
                Log::d("self collide h|1 i=" + std::to_string(i) +
                       " flag=" + std::to_string(flag));
                emit gameOver();
            } else if (!flag && a.getX() >= head_position.getX() &&
                       head_position.getX() >= b.getX()) {
                Log::d("self collide h|2 i=" + std::to_string(i) +
                       " flag=" + std::to_string(flag));
                emit gameOver();
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
        updateState = false;
        emit gameOver();
        return;
    }
    // check collide with the bricks
    std::vector<Point>* bricks = getBrickVertices();
    for (int i = 0; i < bricks->size() - 1; i++) {
        Point a = bricks->at(i);
        Point b = bricks->at(i + 1);
        if (a.getX() == b.getX() && head_position.getX() == a.getX()) {
            bool flag = a.getY() < b.getY();
            if (flag && a.getY() <= head_position.getY() &&
                head_position.getY() <= b.getY()) {
                Log::d("brick collide v|1 i=" + std::to_string(i) +
                       " flag=" + std::to_string(flag));
                emit gameOver();
            } else if (!flag && a.getY() >= head_position.getY() &&
                       head_position.getY() >= b.getY()) {
                Log::d("brick collide v|2 i=" + std::to_string(i) +
                       " flag=" + std::to_string(flag));
                emit gameOver();
            }
        } else if (a.getY() == b.getY() && head_position.getY() == a.getY()) {
            bool flag = a.getX() < b.getX();
            if (flag && a.getX() <= head_position.getX() &&
                head_position.getX() <= b.getX()) {
                Log::d("brick collide h|1 i=" + std::to_string(i) +
                       " flag=" + std::to_string(flag));
                emit gameOver();
            } else if (!flag && a.getX() >= head_position.getX() &&
                       head_position.getX() >= b.getX()) {
                Log::d("brick collide h|2 i=" + std::to_string(i) +
                       " flag=" + std::to_string(flag));
                emit gameOver();
            }
        }
    }
}

void Controller::setSnakeDirection(Snake::Direction d, int index) const {
    if (ai_enabled) return;  // shield the user input
    if (index >= mode) return;
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

std::vector<Point>* Controller::getBrickVertices() const {
    return brick->getBrick();
}

void Controller::eatFood(int index) {
    Log::d("Controller::eatFood()");
    snakeList[index]->grow();
    emit updateSnake(QString("SIGNAL_EAT_FOOD"));
    score += 10;
}

/**
 * Points in generateFood is **logical**.
 */
void Controller::generateFood(int index) {
    Log::d("Controller::generateFood cell_number: " + tStr(cell_number));
    int point[2];
    do {
        for (int i = 0; i < 2; i++) {
            point[i] = rand() % cell_number;
        }
        food = new Food(Point(point[0], point[1]));
        Log::d("Controller::generateFood in random part get: " +
               tStr(point[0]) + " " + tStr(point[1]));
    } while (snakeList[index]->inBody(Point(point[0], point[1])) ||
             brick->inBrick(Point(point[0], point[1])));
    Log::d("Controller::generateFood() cell_number:" +
           std::to_string(cell_number));
}

bool Controller::foodHidden() const { return food->getHidden(); }

bool Controller::foodExists() const { return food == NULL; }

Point Controller::getFoodPosition() const { return food->getPosition(); }

Food::FoodType Controller::getFoodType() const { return food->getFoodType(); }

int Controller::getScore() const { return score; };

int Controller::getSnakeNumber() const { return mode; }

void Controller::setScore(int new_score) { score = new_score; }

void Controller::setCellNumber(int n) {
    cell_number = n;
    // generateFood();
}

void Controller::setPlayer(int player) { this->mode = player; }

void Controller::restart() {
    for (int i = 0; i < mode; i++) {
        Snake* old = snakeList[i];
        snakeList[i] = new Snake;  // TODO: randomize the initial pos
        score = 0;
        delete old;
    }
    updateState = true;
    brick = new Brick(cell_number);

    for (int i = 0; i < mode; i++) {
        /**
         * TODO: rebuild the Snake Constructor so that controller
         * can set the initial range of the snake head
         */
        Log::d("time(NULL): " + tStr(time(NULL)));
        int point_x = rand() % cell_number;
        int point_y = rand() % cell_number;
        Log::d("the initial position of the snake is: (" + tStr(point_x) +
               ", " + tStr(point_y) + ")");
        Point head_point = Point(point_x, point_y);
        snakeList[i] = new Snake(&head_point);
        Log::d("snake is constructed");
    }
    generateFood();
    score = 0;
    if (ai_enabled) ai_path = bfsFindPath();
}

void Controller::reUpdate() {
    updateState = true;
    restart();
}

void Controller::handleFoodEffect() {
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

/**
 * use BFS to find the shortest path to food
 */
std::vector<Point> Controller::bfsFindPath() {
    // calculate the Hamilton Distance of every point
    Point food = getFoodPosition();
    // build an array indicating every point's H-distance
    // map the 2d array to a 1d array
    // if a point hasn't been processed mark it as 1

    int* h_dist = new int[cell_number * cell_number];
    bool* marked = new bool[cell_number * cell_number];
    for (int i = 0; i < cell_number * cell_number; i++) {
        h_dist[i] = 0;
        marked[i] = false;
    }
    std::queue<int> indexMap;  // store the 2d->1d index of points
    indexMap.push(food.getX() + cell_number * food.getY());
    marked[food.getX() + cell_number * food.getY()] = true;
    Log::d(tStr(food.getX()) + tStr(food.getY()), "info.log");
    while (!indexMap.empty()) {
        auto index = indexMap.front();  // index is the 1d position of the point
        indexMap.pop();
        // push the point's four neighbour
        Point p(index % cell_number, index / cell_number);
        // Log::d("index: " + tStr(index));
        // Log::d("calculate index=" + tStr((index % cell_number)) + ", " +
        //               tStr(index / cell_number));
        if (index % cell_number != cell_number - 1 && !h_dist[index + 1] &&
            !snakeList[0]->inBody(p.adjPoint(Point::Right)) &&
            !brick->inBrick(p.adjPoint(Point::Right)) && !marked[index + 1]) {
            indexMap.push(index + 1);
            h_dist[index + 1] = h_dist[index] + 1;
            marked[index + 1] = true;
            // Log::d("Right added!");
        }
        if (index % cell_number != 0 && !h_dist[index - 1] &&
            !snakeList[0]->inBody(p.adjPoint(Point::Left)) &&
            !brick->inBrick(p.adjPoint(Point::Left)) && !marked[index - 1]) {
            indexMap.push(index - 1);
            h_dist[index - 1] = h_dist[index] + 1;
            marked[index - 1] = true;
            // Log::d("Left added!");
        }
        if (index < cell_number * (cell_number - 1) &&
            !h_dist[index + cell_number] &&
            !snakeList[0]->inBody(p.adjPoint(Point::Down)) &&
            !brick->inBrick(p.adjPoint(Point::Down)) &&
            !marked[index + cell_number]) {
            indexMap.push(index + cell_number);
            h_dist[index + cell_number] = h_dist[index] + 1;
            marked[index + cell_number] = true;
            // Log::d("Down added!");
        }
        if (index >= cell_number && !h_dist[index - cell_number] &&
            !snakeList[0]->inBody(p.adjPoint(Point::Up)) &&
            !brick->inBrick(p.adjPoint(Point::Up)) &&
            !marked[index - cell_number]) {
            indexMap.push(index - cell_number);
            h_dist[index - cell_number] = h_dist[index] + 1;
            marked[index - cell_number] = true;
            // Log::d("Up added!");
        }
    }
    Log::d("map built");
    // debug:
    for (int i = 0; i < cell_number; i++) {
        std::string map_line = "";
        for (int j = 0; j < cell_number; j++) {
            if (h_dist[i * cell_number + j] < 10)
                map_line += ("0" + tStr(h_dist[i * cell_number + j]) + " ");
            else
                map_line += (tStr(h_dist[i * cell_number + j]) + " ");
        }
        Log::d(map_line, "info.log");
    }

    // tell the snake the shortest path
    // std::vector <auto>
    std::vector<Point> pathPoints;
    // determine the possible directions
    Point snake_head = snakeList[0]->getBodyVertex()[0];
    //    Snake::Direction snake_dir = snakeList[0]->getDirection();
    int dist_up =
        snake_head.getY() == 0
            ? 0
            : h_dist[snake_head.getX() + (snake_head.getY() - 1) * cell_number];
    int dist_down = snake_head.getY() == cell_number - 1
                        ? 0
                        : h_dist[snake_head.getX() +
                                 (snake_head.getY() + 1) * (cell_number)];
    int dist_left =
        snake_head.getX() == 0
            ? 0
            : h_dist[snake_head.getX() + snake_head.getY() * cell_number - 1];
    int dist_right =
        snake_head.getX() == cell_number - 1
            ? 0
            : h_dist[snake_head.getX() + snake_head.getY() * cell_number + 1];
    int dist_arr[] = {dist_up, dist_down, dist_left, dist_right};
    int min = INT_MAX;
    int min_index = -1;
    for (int i = 0; i < 4; i++) {
        if (dist_arr[i] > 0 && dist_arr[i] < min) {
            min = dist_arr[i];
            min_index = i;
        }
    }
    Point cur_point;
    if (min_index == -1) {
        emit gameOver();
        return pathPoints;
    }
    switch (min_index) {
        case 0:
            cur_point = Point(snake_head.getX(), snake_head.getY() - 1);
            break;
        case 1:
            cur_point = Point(snake_head.getX(), snake_head.getY() + 1);
            break;
        case 2:
            cur_point = Point(snake_head.getX() - 1, snake_head.getY());
            break;
        case 3:
            cur_point = Point(snake_head.getX() + 1, snake_head.getY());
            break;
        default:
            break;
    }
    Log::d("cal: pathPoints");
    do {
        // Log::d("process point (" + tStr(cur_point.getX()) + ", " +
        //        tStr(cur_point.getY()) + ")");
        pathPoints.push_back(cur_point);
        cur_point = nextPathPoint(cur_point, h_dist);
        Log::d("get next point (" + tStr(cur_point.getX()) + ", " +
               tStr(cur_point.getY()) + ")");
    } while (h_dist[cur_point.getX() + cur_point.getY() * cell_number] != 0);
    // pathPoints.push_back(cur_point);
    pathPoints.push_back(getFoodPosition());
    Log::d("calculate path done");
    return pathPoints;
}

Point Controller::nextPathPoint(Point& cur, int* h_dist_arr) const {
    int cur_idx = cur.getX() + cur.getY() * cell_number;
    int h_dist_cur = h_dist_arr[cur_idx];
    if (cur_idx / cell_number != 0 &&
        h_dist_arr[cur_idx - cell_number] == h_dist_cur - 1) {
        return cur.adjPoint(Point::Up);
    } else if (cur_idx / cell_number < cell_number - 1 &&
               h_dist_arr[cur_idx + cell_number] == h_dist_cur - 1)
        return cur.adjPoint(Point::Down);
    else if (cur_idx % cell_number != 0 &&
             h_dist_arr[cur_idx - 1] == h_dist_cur - 1)
        return cur.adjPoint(Point::Left);
    else if (cur_idx % cell_number != cell_number - 1 &&
             h_dist_arr[cur_idx + 1] == h_dist_cur - 1)
        return cur.adjPoint(Point::Right);
    return Point(-1, -1);
}

bool Controller::enableAi() { return ai_enabled = true; }
