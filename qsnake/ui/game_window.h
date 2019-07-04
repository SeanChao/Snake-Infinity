#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "raster_window.h"
#include "../core/controller.h"
#include "../game/snake.h"

class GameWindow : public RasterWindow {
   public:
    GameWindow();
    ~GameWindow();
    void bindController(Controller *controller);
    // void bindSnake(Snake *snake);

   protected:
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *ev) override;
    
   private:
    // int x;
    // int y;
    int update_timer_id;
    Controller *controller;
    // Snake *snake;

    void render(QPainter *painter) override;
    void renderBackground(QPainter *painter);
    void renderScene(QPainter *painter);
    void renderSnake(QPainter *painter);
    void renderSnack(QPainter *painter);

};

#endif  // GAME_WINDOW_H