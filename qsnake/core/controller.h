#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "../game/food.h"
#include "../game/point.h"
#include "../game/snake.h"
#include "../log/log.h"

class Controller : public QObject {
    Q_OBJECT
   public:
    Controller(int player = 1);
    void updateGame();
    // Snake *getSnake();
    void moveSnake();
    void setSnakeDirection(Snake::Direction d, int index = 0) const;
    Point *getSnakeVertices(int index = 0) const;
    int getSnakeVerticesSize(int index = 0) const;
    void eatFood(int index = 0);

    void generateFood(int index = 0);
    bool foodHidden() const;
    bool foodExists() const;
    Point getFoodPosition() const;

    void collideDetection(int index = 0);  // return the point that something collides
    int getScore() const;
    void setScore(int new_score);
    void setCellNumber(int n);

    void restart();

   signals:
    void updateSnake(const QString &type);  // use signal slot to actively update gamewindow

   private:
    // Snake *snake;
    Snake **snakeList;  // an array to store Snake*
    Food *food;
    int score;
    int cell_number;
    int mode;  // the number of players
};

#endif  // CONTROLLER_H