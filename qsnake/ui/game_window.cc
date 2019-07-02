#include "game_window.h"
#include "../log/log.h"
#include "../game/point.h"

GameWindow::GameWindow() {
    setTitle(tr("Snake: Infinity"));
    resize(800, 450);
    update_timer_id = startTimer(1000);
    x = 100;
    y = 100;
}

GameWindow::~GameWindow() {}

void GameWindow::bindController(Controller *controller) { this->controller = controller; }

void GameWindow::bindSnake(Snake *snake) { this->snake = snake; }

void GameWindow::timerEvent(QTimerEvent *event) {
    // if(event->timerId() == update_timer_id) {
    //     x+=5;
    //     y+=5;
    //     renderNow();
    // }
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Up)
        y -= 5;
    if (event->key() == Qt::Key_Down)
        y += 5;
    if (event->key() == Qt::Key_Right)
        x += 5;
    if (event->key() == Qt::Key_Left)
        x -= 5;

    // Log::d("x=" + std::to_string(x) + "\ty=" + std::to_string(y) + "\t on key
    // pressed");
    renderNow();
}

void GameWindow::render(QPainter *painter) {
    renderBackground(painter);
    renderSnake(painter);
}

// void GameWindow::renderNow() {
//     QPainter painter;
//     render(&painter);
// }

void GameWindow::renderBackground(QPainter *painter) {
    painter->fillRect(0, 0, width(), height(), QColor("#578A34"));
    painter->fillRect(0, 0, width(), height() / 5, QColor("#4A752C"));

    QPixmap apple_image(":img/apple");
    painter->drawPixmap(width() / 80, width() / 80, width() / 10, width() / 10,
                        apple_image);
}

void GameWindow::renderScene(QPainter *painter) {
    painter->save();

    painter->restore();
}

void GameWindow::renderSnake(QPainter *painter) {
    painter->save();
    painter->setBrush(Qt::blue);
    // painter->drawRect(x, y, 20, 20);
    // Log::d("x=" + std::to_string(x) + "\ty=" + std::to_string(y));
    Point *snake_vertex = snake->getBodyVertex();
    int vertex_size = snake->getBodyVertexSize();
    for(int i = 0; i < vertex_size; ++i) {
        painter->drawRect(snake_vertex[i].getX(),snake_vertex[i].getY(), 20, 20);
    }
    painter->restore();
}