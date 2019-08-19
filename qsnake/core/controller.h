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
    Controller();
    void updateGame();
    Snake *getSnake();
    void moveSnake();
    void setSnakeDirection(Snake::Direction d) const;

    void eatFood();

    void generateFood();
    bool foodHidden() const;
    bool foodExists() const;
    Point getFoodPosition() const;

    void collideDetection();  // return the point that something collides
    int getScore() const;
    void setScore(int new_score);
    void setCellNumber(int n);

    void restart();
    
   signals:
    void updateSnake(const QString &type);  // use signal slot to actively update gamewindow

   private:
    Snake *snake;
    Food *food;
    int score;
    int cell_number;
};

#endif  // CONTROLLER_H