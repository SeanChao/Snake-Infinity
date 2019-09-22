#include "main_window.h"
#include <QDebug>
#include <QMenuBar>
#include <QStackedWidget>
#include "game_window.h"
#include "ui/components/qtmaterialflatbutton.h"
#include "ui/game_widget.h"
#include "ui/welcome_widget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // setFixedSize(800, 800);
    setGeometry(100, 100, 1000, 1000);  // TODO: delete this (debug)
    resize(800, 800);

    WelcomeWidget *welcome_widget = new WelcomeWidget;
    game_widget = new GameWidget;

    widget_stack = new QStackedWidget(this);
    widget_stack->addWidget(welcome_widget);
    widget_stack->addWidget(game_widget);

    // make game ui update
    connect(welcome_widget, WelcomeWidget::btnPressed, game_widget,
            GameWidget::changeGameState);
    // make game core run
    connect(welcome_widget, WelcomeWidget::btnPressed, this,
            MainWindow::startGame);
    setCentralWidget(widget_stack);
}

void MainWindow::btnNormalPressed() {
    Log::d("button [normal mode] is pressed");
    widget_stack->setCurrentIndex(1);
}

void MainWindow::startGame(int id) {
    Log::d("MainWindow::startGame (SLOT) id: " + std::to_string(id));
    int player = id;
    controller = new Controller(player, game_widget->getCellNumber());
    game_widget->bindController(controller);
    // connect(controller, &Controller::updateSnake, game_widget,
    // QOverload<>::of(&GameWidget::update));
    widget_stack->setCurrentIndex(1);

    connectSignalSlot();
}

void MainWindow::createActions() {}

void MainWindow::createMenus() {
    //    QMenu *menu_option = menuBar()->addMenu(tr("&Options"));
    // menu_option->addAction(action_new_game);
}

/**
 * connect related signals and slots
 * please make sure every pointer is initialize before being used.
 */
void MainWindow::connectSignalSlot() {
    connect(controller, &Controller::scaleSpeed, game_widget,
            &GameWidget::scaleSpeed);
    qDebug() << "connect done";
    Log::d("connection is created!");
}