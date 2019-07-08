#include "game_window.h"
#include "../game/point.h"
#include "../log/log.h"

GameWindow::GameWindow() {
    setTitle(tr("Snake: Infinity"));
    resize(800, 800);
    update_timer_id = startTimer(1000);
    render_timer_id = startTimer(500);
    snake_timer_id = startTimer(500);
    state = true;
}

GameWindow::~GameWindow() {}

void GameWindow::bindController(Controller *controller) {
    this->controller = controller;
}

// int counter = 0;
void GameWindow::timerEvent(QTimerEvent *event) {
    if (state&&event->timerId() == render_timer_id) {
        renderNow();
    }
    if (state&&event->timerId()== snake_timer_id){
        // controller->moveSnake();
        controller->updateGame();
    }
}

void GameWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Up)
        controller->setSnakeDirection(Snake::UP);
    if (event->key() == Qt::Key_Down)
        controller->setSnakeDirection(Snake::DOWN);
    if (event->key() == Qt::Key_Right)
        controller->setSnakeDirection(Snake::RIGHT);
    if (event->key() == Qt::Key_Left)
        controller->setSnakeDirection(Snake::LEFT);
    if (event->key()==Qt::Key_Space) {
        Log::d("GameWindow::keyPressEvent\t Game Paused");
        state = !state;
    }
    // debug:
    if (event->key()==Qt::Key_E)
        controller->eatFood();
    // renderNow();
}

void GameWindow::mousePressEvent(QMouseEvent *ev) {
    Log::d("mouse clicked at " + std::to_string(ev->x()) + ", " +
           std::to_string(ev->y()));
}

void GameWindow::render(QPainter *painter) {
    renderBackground(painter);
    renderFood(painter);
    renderSnake(painter);
}

// void GameWindow::renderNow() {
//     QPainter painter;
//     render(&painter);
// }

void GameWindow::renderBackground(QPainter *painter) {
    painter->fillRect(0, 0, width(), height(), QColor("#578A34"));
    painter->fillRect(0, 0, width(), 70, QColor("#4A752C"));

    QPixmap apple_image(":img/apple");
    painter->drawPixmap(width() / 80, width() / 80, width() / 10, width() / 10,
                        apple_image);
}

void GameWindow::renderLand(QPainter *painter) {
    painter->save();
    
    painter->restore();
}

int times = 0;
void GameWindow::renderSnake(QPainter *painter) {
    // Log::d("GameWindow::renderSnake");
    painter->save();
    painter->setBrush(Qt::blue);
    switch (times % 4) {
        case 0:
            break;
        case 1:
            painter->setBrush(Qt::red);
            break;
        case 2:
            painter->setBrush(Qt::yellow);
            break;
        case 3:
            painter->setBrush(Qt::green);
            break;
        case 4:
            painter->setBrush(Qt::white);
            break;
    }
    times++;
    // painter->drawRect(x, y, 20, 20);
    // Log::d("x=" + std::to_string(x) + "\ty=" + std::to_string(y));
    Point *snake_vertex = controller->getSnake()->getBodyVertex();  // TODO: change to indirect visit
    int vertex_size = controller->getSnake()->getBodyVertexSize();
    // paint the snake by connecting all the vertices
    //debug:
    for (int i = 0; i < vertex_size; i++) {
        // Log::d("snake_vertex[" + std::to_string(i) + "]\t(" + std::to_string(snake_vertex[i].getX())+","+ std::to_string(snake_vertex[i].getY())+")");
    }

    for (int i = 0; i < vertex_size - 1; ++i) {
        // Log::d("snake_vertex[" + std::to_string(i) + "].getX()=" + std::to_string(snake_vertex[i].getX()));
        // Log::d("snake_vertex[" + std::to_string(i + 1) + "].getX()=" + std::to_string(snake_vertex[i + 1].getX()));
        // Log::d("snake_vertex[" + std::to_string(i) + "].getY()=" + std::to_string(snake_vertex[i].getY()));
        // Log::d("snake_vertex[" + std::to_string(i + 1) + "].getY()=" + std::to_string(snake_vertex[i + 1].getY()));
        for (int j = abs(snake_vertex[i].getX() - snake_vertex[i + 1].getX());
             j >= 0; j -= 20) {
            int left_vertex_index =
                (snake_vertex[i].getX() > snake_vertex[i + 1].getX()) ? i + 1
                                                                      : i;
            painter->drawRect(snake_vertex[left_vertex_index].getX() + j,
                              snake_vertex[left_vertex_index].getY(), 20, 20);
            // Log::d("renderSnake->drawRect at\t(" +std::to_string(snake_vertex[i].getX() + j) + "," +std::to_string(snake_vertex[i].getY()) + ", 20, 20)");
        }
        for (int k = abs(snake_vertex[i].getY() - snake_vertex[i + 1].getY());
             k >= 0; k -= 20) {
            int below_vertex_index =
                (snake_vertex[i].getY() > snake_vertex[i + 1].getY()) ? i
                                                                      : i + 1;
            painter->drawRect(snake_vertex[below_vertex_index].getX(),
                              snake_vertex[below_vertex_index].getY() - k, 20, 20);
            // Log::d("renderSnake->drawRect at\t(" + std::to_string(snake_vertex[i].getX()) + "," +  std::to_string(snake_vertex[i].getY() - k) + ", 20, 20)");
        }
    }
    painter->restore();
    // Log::d("GameWindow::renderSnake finished");
}

void GameWindow::renderFood(QPainter *painter) {
    // Log::d("GameWindow::renderFood is called");
    if(controller->foodHidden()) return;
    painter->save();
    Point position = controller->getFoodPosition();
    painter->setBrush(Qt::red);
    painter->drawRect(position.getX(), position.getY(), 20, 20);
    painter->restore();
}