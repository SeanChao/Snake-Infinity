#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H
#include <QWidget>
#include "../core/controller.h"
#include "../game/point.h"
#include "../game/snake.h"

class GameWidget : public QWidget {
    Q_OBJECT
   public:
    explicit GameWidget(QWidget *parent = nullptr);
    void bindController(Controller *controller);
    int getCellNumber() const;

   signals:

   public slots:
    void render();
    void changeGameState();
    void enterGame(int id);
    void updateGame();
    void changeSpeed(int interval);
    void scaleSpeed(double ratio);

   protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *e) override;
    void mousePressEvent(QMouseEvent *ev) override;

   private:
    int render_timer_id;    // timer to render the widget
    int update_timer_id;    // timer to update the game content
    Controller *controller;
    bool state;             // false for pause
    int cell;               // the length of a cell in grassland
    int cell_number;        // the number of cells
    int land_x;             // the left-top x cordinate of grassland
    int land_y;
    QTimer *update_timer;
    QTimer *render_timer;
    int update_interval;    // original update interval
    // void render(QPainter *painter) override;
    void renderBackground(QPainter *painter);
    void renderLand(QPainter *painter);
    void renderSnake(QPainter *painter);
    void renderSnake(QPainter *painter, int index);
    void renderFood(QPainter *painter);
    void restart();
};

#endif  // GAME_WIDGET_H
