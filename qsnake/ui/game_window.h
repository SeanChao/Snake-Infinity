#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

// #include <QMainWindow>

#include "raster_window.h"
#include "../core/controller.h"
#include "../game/snake.h"
#include "../game/point.h"

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
    int update_timer_id;
    int render_timer_id;
    int snake_timer_id;
    Controller *controller;
    bool state;
    int cell;           // the length of a cell in grassland
    int cell_number;    // the number of cells
    int land_x;         // the left-top x cordinate of grassland
    int land_y;

    void render(QPainter *painter) override;
    void renderBackground(QPainter *painter);
    void renderLand(QPainter *painter);
    void renderSnake(QPainter *painter);
    void renderFood(QPainter *painter);
};

#endif  // GAME_WINDOW_H