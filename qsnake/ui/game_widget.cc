#include "game_widget.h"
#include <QEvent>
#include <QKeyEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include "../game/point.h"
#include "../log/log.h"

#define tStr std::to_string

GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
    Log::d("building GameWidget...");
    resize(800, 800);
    setWindowTitle(tr("Snake: Infinity"));
    setFocusPolicy(Qt::StrongFocus);  // enable keyboard press and click

    state = false;
    cell = 30;
    cell_number = height() * 0.8 / cell;

    // update_timer_id = startTimer(1000);
    update_timer = new QTimer(this);
    update_interval = 1000;
    update_timer->start(update_interval);
    connect(update_timer, &QTimer::timeout, this, &GameWidget::updateGame);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this,
            QOverload<>::of(&GameWidget::update));
    timer->start(1000 / 30.0);
    Log::d("GameWidget is built");
}

void GameWidget::paintEvent(QPaintEvent *) {
    // Log::d("PaintEvent is called");
    QPainter *painter = new QPainter(this);
    renderBackground(painter);
    renderLand(painter);
    renderFood(painter);
    renderSnake(painter);
}

void GameWidget::timerEvent(QTimerEvent *event) {
    Log::d("game content is to be updated");
    if (state && event->timerId() == update_timer->timerId()) {
        controller->updateGame();
    }
}

void GameWidget::updateGame() {
    Log::d("update the game ...");
    if(state) controller->updateGame();
}

// it seems that this function has no use
void GameWidget::render() {
    // QPainter *painter = new QPainter(this);
    // Log::d("GameWidget::render is called");
    // controller->updateGame();
    // renderBackground(painter);
    // renderLand(painter);
    // renderFood(painter);
    // renderSnake(painter);
}

void GameWidget::bindController(Controller *controller) {
    this->controller = controller;
    controller->setCellNumber(cell_number);
}

int GameWidget::getCellNumber() const { return cell_number; }

void GameWidget::changeGameState() {
    // TODO: rename the function
    state = true;
}

void GameWidget::enterGame(int id) {
    /**
     * stateId: explanation
     * 0: start the game
     */
    switch (id) {
        case 1:
            state = true;
            break;

        default:
            break;
    }
}

void GameWidget::changeSpeed(int interval) {}

/**
 * set the speed to be ratio*(current speed)
 * if ratio is 0 then restore the speed
 */
void GameWidget::scaleSpeed(int ratio) {
    Log::d("in GameWidget receive signal in scaleSpeed ratio: " + tStr(ratio));
    if(ratio==0) {
        qDebug() << "the update_timer interval is restored to " << update_interval; 
        update_timer->setInterval(update_interval);
    }else{
        qDebug() << "the update_timer interval is set to " << update_timer->interval()/ratio << '\n';
        update_timer->setInterval(update_timer->interval()/ratio);
    }
}

void GameWidget::keyPressEvent(QKeyEvent *event) {
    // TODO: merge if and switch condition controll
    if (event->key() == Qt::Key_Up)
        controller->setSnakeDirection(Snake::UP);
    if (event->key() == Qt::Key_Down)
        controller->setSnakeDirection(Snake::DOWN);
    if (event->key() == Qt::Key_Right)
        controller->setSnakeDirection(Snake::RIGHT);
    if (event->key() == Qt::Key_Left)
        controller->setSnakeDirection(Snake::LEFT);
    if (event->key() == Qt::Key_Space) {
        Log::d("GameWidget::keyPressEvent\t Game Paused");
        state = !state;
    }
    switch (event->key()) {
        case Qt::Key_W:
            controller->setSnakeDirection(Snake::UP, 1);
            break;
        case Qt::Key_S:
            controller->setSnakeDirection(Snake::DOWN, 1);
            break;
        case Qt::Key_A:
            controller->setSnakeDirection(Snake::LEFT, 1);
            break;
        case Qt::Key_D:
            controller->setSnakeDirection(Snake::RIGHT, 1);
            break;

        default:
            break;
    }
    if (event->key() == Qt::Key_E) {
        controller->updateGame();
        Log::d("accelerating!!");
        emit controller->updateSnake(QString("SIGNAL_ACCELERATE"));
    }
}

void GameWidget::mousePressEvent(QMouseEvent *ev) {
    Log::d("mouse clicked at " + std::to_string(ev->x()) + ", " +
           std::to_string(ev->y()));
}

void GameWidget::renderBackground(QPainter *painter) {
    painter->save();
    int statusbar_height = height() / 10;
    int padding = statusbar_height / 10;
    int icon_size = statusbar_height * 0.8;
    painter->fillRect(0, 0, width(), height(), QColor("#578A34"));
    painter->fillRect(0, 0, width(), statusbar_height,
                      QColor("#4A752C"));  // designed for game status bar
    QPixmap apple_image(":img/apple");
    painter->drawPixmap(width() / 80, width() / 80, icon_size, icon_size,
                        apple_image);
    // render score:
    painter->setPen(Qt::white);
    QFont score_font = painter->font();
    score_font.setPointSize(25);
    score_font.setBold(true);
    painter->setFont(score_font);
    // Log::d("controller->getScore():" +
    // std::to_string(controller->getScore()));
    painter->drawText(icon_size + 2 * padding, statusbar_height - padding * 2,
                      QString(QString::fromStdString(
                          std::to_string(controller->getScore()))));
    painter->restore();
}

// TODO: extract all the length/width/height
void GameWidget::renderLand(QPainter *painter) {
    painter->save();
    int grassland_width = cell * cell_number;
    land_x = (width() - grassland_width) / 2;
    land_y = height() * 0.1 + (height() * 0.9 - grassland_width) / 2;
    // Log::d("cell: " + std::to_string(cell) + " cell_number: " +
    // std::to_string(cell_number)); Log::d("grassland_width: " +
    // std::to_string(grassland_width) + " lx: " + std::to_string(land_x) + "
    // ly: " + std::to_string(land_y));
    for (int i = 0; i < cell_number; i++) {
        for (int j = 0; j < cell_number; j++) {
            if ((i + j) % 2 == 0) {
                painter->fillRect(land_x + i * cell, land_y + j * cell, cell,
                                  cell, QColor(157, 207, 65));
                // Log::d("draw cell E at (" + std::to_string(land_x + i *
                // cell)+", "+ std::to_string(land_y + j * cell)+ ")");
            } else {
                painter->fillRect(land_x + i * cell, land_y + j * cell, cell,
                                  cell, QColor(170, 215, 81));
                // Log::d("draw cell O at (" + std::to_string(land_x + i *
                // cell)+", "+ std::to_string(land_y + j * cell)+ ")");
            }
        }
    }

    painter->restore();
}

void GameWidget::renderSnake(QPainter *painter) {
    int count = controller->getSnakeNumber();
    for (auto i = 0; i < count; i++) {
        renderSnake(painter, i);
    }
}

void GameWidget::renderSnake(QPainter *painter, int index) {
    painter->save();
    painter->setBrush(Qt::blue);
    Point *snake_vertex =
        controller->getSnakeVertices(index);  // TODO: change to indirect visit
    int vertex_size = controller->getSnakeVerticesSize(index);
    // paint the snake by connecting all the vertices
    // debug:
    // for (int i = 0; i < vertex_size; i++) {
    //     Log::d("snake_vertex[" + std::to_string(i) + "]\t(" +
    //     std::to_string(snake_vertex[i].getX())+","+
    //     std::to_string(snake_vertex[i].getY())+")");
    // }
    // special case: if the length of snake is 1:
    if (vertex_size == 1) {
        painter->drawRect(land_x + cell * snake_vertex[0].getX(),
                          land_y + cell * snake_vertex[0].getY(), cell, cell);
    } else {
        for (int i = 0; i < vertex_size - 1; ++i) {
            // Log::d("snake_vertex[" + std::to_string(i) + "].getX()=" +
            // std::to_string(snake_vertex[i].getX())); Log::d("snake_vertex[" +
            // std::to_string(i + 1) + "].getX()=" +
            // std::to_string(snake_vertex[i + 1].getX()));
            // Log::d("snake_vertex[" + std::to_string(i) + "].getY()=" +
            // std::to_string(snake_vertex[i].getY())); Log::d("snake_vertex[" +
            // std::to_string(i + 1) + "].getY()=" +
            // std::to_string(snake_vertex[i + 1].getY()));
            for (int j =
                     abs(snake_vertex[i].getX() - snake_vertex[i + 1].getX());
                 j >= 0; j -= 1) {
                int left_vertex_index =
                    (snake_vertex[i].getX() > snake_vertex[i + 1].getX())
                        ? i + 1
                        : i;
                painter->drawRect(
                    land_x + cell * snake_vertex[left_vertex_index].getX() +
                        j * cell,
                    land_y + cell * snake_vertex[left_vertex_index].getY(),
                    cell, cell);
            }
            for (int k =
                     abs(snake_vertex[i].getY() - snake_vertex[i + 1].getY());
                 k >= 0; k -= 1) {
                int below_vertex_index =
                    (snake_vertex[i].getY() > snake_vertex[i + 1].getY())
                        ? i
                        : i + 1;
                painter->drawRect(
                    land_x + cell * snake_vertex[below_vertex_index].getX(),
                    land_y + cell * snake_vertex[below_vertex_index].getY() -
                        k * cell,
                    cell, cell);
            }
        }
    }
    painter->restore();
}

void GameWidget::renderFood(QPainter *painter) {
    if (controller->foodHidden())
        return;
    painter->save();
    Point position = controller->getFoodPosition();
    painter->setBrush(Qt::red);
    painter->drawRect(land_x + cell * position.getX(),
                      land_y + cell * position.getY(), cell, cell);
    painter->restore();
}

void GameWidget::restart() {}
