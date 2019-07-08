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

    Point collideDetection();  // return the point that something collides
   
   signals:
    void updateSnake(const QString &type);    // use signal slot to actively update gamewindow

   private:
    Snake *snake;
    Food *food;
};

#endif  // CONTROLLER_H