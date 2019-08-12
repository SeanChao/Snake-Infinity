#include "game_window.h"
#include "../game/point.h"
#include "../log/log.h"

GameWindow::GameWindow() {
    setTitle(tr("Snake: Infinity"));
    resize(800, 800);
    update_timer_id = startTimer(1000);
    render_timer_id = startTimer(800);
    snake_timer_id = startTimer(400);
    state = true;
    cell = 30;
    cell_number = height() * 0.8 / cell;
}

GameWindow::~GameWindow() {}

void GameWindow::bindController(Controller *controller) {
    this->controller = controller;
    controller->setCellNumber(cell_number);
}

void GameWindow::timerEvent(QTimerEvent *event) {
    if (state && event->timerId() == render_timer_id) {
        controller->updateGame();
        renderNow();
    }
    if (state && event->timerId() == snake_timer_id) {
        // controller->moveSnake();
        // controller->updateGame();
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
    if (event->key() == Qt::Key_Space) {
        Log::d("GameWindow::keyPressEvent\t Game Paused");
        state = !state;
    }
    // debug:
    if (event->key() == Qt::Key_E) {
        controller->updateGame();
        renderNow();
    }
}

void GameWindow::mousePressEvent(QMouseEvent *ev) {
    Log::d("mouse clicked at " + std::to_string(ev->x()) + ", " +
           std::to_string(ev->y()));
}

void GameWindow::render(QPainter *painter) {
    renderBackground(painter);
    renderLand(painter);
    renderFood(painter);
    renderSnake(painter);
}

void GameWindow::renderBackground(QPainter *painter) {
    painter->save();
    int statusbar_height = height() / 10;
    int padding = statusbar_height / 10;
    int icon_size = statusbar_height * 0.8;
    painter->fillRect(0, 0, width(), height(), QColor("#578A34"));
    painter->fillRect(0, 0, width(), statusbar_height, QColor("#4A752C"));  // designed for game status bar
    QPixmap apple_image(":img/apple");
    painter->drawPixmap(width() / 80, width() / 80, icon_size, icon_size, apple_image);
    // render score:
    painter->setPen(Qt::white);
    QFont score_font = painter->font();
    score_font.setPointSize(25);
    score_font.setBold(true);
    painter->setFont(score_font);
    Log::d("controller->getScore():" + std::to_string(controller->getScore()));
    painter->drawText(icon_size + 2*padding, statusbar_height - padding *2, QString(QString::fromStdString(std::to_string(controller->getScore()))));
    Log::d("render land finished");
    painter->restore();
}

// TODO: extract all the length/width/height
void GameWindow::renderLand(QPainter *painter) {
    painter->save();
    int grassland_width = cell * cell_number;
    land_x = (width() - grassland_width) / 2;
    land_y = height() * 0.1 + (height() * 0.9 - grassland_width) / 2;
    Log::d("cell: " + std::to_string(cell) + " cell_number: " + std::to_string(cell_number));
    Log::d("grassland_width: " + std::to_string(grassland_width) + " lx: " + std::to_string(land_x) + " ly: " + std::to_string(land_y));
    for (int i = 0; i < cell_number; i++) {
        for (int j = 0; j < cell_number; j++) {
            if ((i + j) % 2 == 0) {
                painter->fillRect(land_x + i * cell, land_y + j * cell, cell, cell, QColor(157, 207, 65));
                // Log::d("draw cell E at (" + std::to_string(land_x + i * cell)+", "+ std::to_string(land_y + j * cell)+ ")");
            } else {
                painter->fillRect(land_x + i * cell, land_y + j * cell, cell, cell, QColor(170, 215, 81));
                // Log::d("draw cell O at (" + std::to_string(land_x + i * cell)+", "+ std::to_string(land_y + j * cell)+ ")");
            }
        }
    }

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
    // for (int i = 0; i < vertex_size; i++) {
    //     Log::d("snake_vertex[" + std::to_string(i) + "]\t(" + std::to_string(snake_vertex[i].getX())+","+ std::to_string(snake_vertex[i].getY())+")");
    // }
    //special case: if the length of snake is 1:
    if (vertex_size == 1) {
        painter->drawRect(land_x + cell * snake_vertex[0].getX(), land_y + cell * snake_vertex[0].getY(), cell, cell);
    } else {
        for (int i = 0; i < vertex_size - 1; ++i) {
            // Log::d("snake_vertex[" + std::to_string(i) + "].getX()=" + std::to_string(snake_vertex[i].getX()));
            // Log::d("snake_vertex[" + std::to_string(i + 1) + "].getX()=" + std::to_string(snake_vertex[i + 1].getX()));
            // Log::d("snake_vertex[" + std::to_string(i) + "].getY()=" + std::to_string(snake_vertex[i].getY()));
            // Log::d("snake_vertex[" + std::to_string(i + 1) + "].getY()=" + std::to_string(snake_vertex[i + 1].getY()));
            for (int j = abs(snake_vertex[i].getX() - snake_vertex[i + 1].getX());
                 j >= 0; j -= 1) {
                int left_vertex_index =
                    (snake_vertex[i].getX() > snake_vertex[i + 1].getX()) ? i + 1
                                                                          : i;
                painter->drawRect(land_x + cell * snake_vertex[left_vertex_index].getX() + j * cell,
                                  land_y + cell * snake_vertex[left_vertex_index].getY(), cell, cell);
                // Log::d("renderSnake->drawRect at\t(" +std::to_string(snake_vertex[i].getX() + j) + "," +std::to_string(snake_vertex[i].getY()) + ", 20, 20)");
            }
            for (int k = abs(snake_vertex[i].getY() - snake_vertex[i + 1].getY());
                 k >= 0; k -= 1) {
                int below_vertex_index =
                    (snake_vertex[i].getY() > snake_vertex[i + 1].getY()) ? i
                                                                          : i + 1;
                painter->drawRect(land_x + cell * snake_vertex[below_vertex_index].getX(),
                                  land_y + cell * snake_vertex[below_vertex_index].getY() - k * cell, cell, cell);
                // Log::d("renderSnake->drawRect at\t(" + std::to_string(snake_vertex[i].getX()) + "," +  std::to_string(snake_vertex[i].getY() - k) + ", 20, 20)");
            }
        }
    }
    painter->restore();
    // Log::d("GameWindow::renderSnake finished");
}

void GameWindow::renderFood(QPainter *painter) {
    if (controller->foodHidden())
        return;
    painter->save();
    Point position = controller->getFoodPosition();
    painter->setBrush(Qt::red);
    painter->drawRect(land_x + cell * position.getX(), land_y + cell * position.getY(), cell, cell);
    painter->restore();
}
