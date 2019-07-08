#include <QTimer>
#include <QGraphicsView>
#include <QPainter>

#include "../constants.h"
#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this))
    //   view(new QGraphicsScene(scene, this)),
    //   game(new GameController(*scene, this)) 
{
    setCentralWidget(view);
    resize(600, 600);
    initScene();
    initSceneBackground();

    QTimer::singleShot(0, this, SLOT(adjustViewSize));
}

MainWindow::~MainWindow() {
    
}

void MainWindow::initScene() {
    scene->setSceneRect(-100, -100, 200, 200);
}

void MainWindow::initSceneBackground() {
    QPixmap bg(TILE_SIZE, TILE_SIZE);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));
    p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);

    view->setBackgroundBrush(QBrush(bg));
}

void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}