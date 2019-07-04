#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "../game/snake.h"
#include "../log/log.h"

class Controller : public QObject {
    Q_OBJECT
   public:
    Controller();
    Snake* getSnake();
    void moveSnake();
    void setSnakeDirection(Snake::Direction d) const;

   private:
    Snake *snake;
};

#endif  // CONTROLLER_H