#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "../game/brick.h"
#include "../game/food.h"
#include "../game/point.h"
#include "../game/snake.h"
#include "../log/log.h"

class Controller : public QObject {
    Q_OBJECT
   public:
    Controller(int player = 1, int cell_number = 1, bool ai = false);
    void updateGame();
    // Snake *getSnake();
    void moveSnake();
    void setSnakeDirection(Snake::Direction d, int index = 0) const;
    Point *getSnakeVertices(int index = 0) const;
    int getSnakeVerticesSize(int index = 0) const;
    std::vector<Point> *getBrickVertices() const;
    void eatFood(int index = 0);
    void generateFood(int index = 0);
    bool foodHidden() const;
    bool foodExists() const;
    Point getFoodPosition() const;
    void collideDetection(int index = 0);  // return the point collides with sth
    Food::FoodType getFoodType() const;
    int getScore(int index = 0) const;
    int getSnakeNumber() const;
    void setScore(int new_score, int index = 0);
    void setCellNumber(int n);
    void setPlayer(int player);
    void restart();
    bool enableAi();

   signals:
    void updateSnake(
        const QString &type);  // use signal slot to actively update gamewindow
    void changeSpeed(int interval);
    void scaleSpeed(double ratio);
    void gameOver();

   public slots:
    void reUpdate();

   private:
    Snake **snakeList;  // an array to store Snake*
    Food *food;
    Brick *brick;
    bool updateState;
    bool ai_enabled;
    int *score;
    int round;
    int cell_number;             // the number of cells in the grassland
    int mode;                    // the number of players
    std::vector<Point> ai_path;  // the path that AI follows

    void handleFoodEffect();
    std::vector<Point> bfsFindPath();  // find the bfs path
    Point nextPathPoint(Point &cur, int *h_dist_arr) const;
};

#endif  // CONTROLLER_H