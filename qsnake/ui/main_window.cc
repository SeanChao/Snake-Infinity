#include "main_window.h"
#include <QMenuBar>
#include <QStackedWidget>
#include "game_window.h"
#include "ui/components/qtmaterialflatbutton.h"
#include "ui/welcome_widget.h"
#include "ui/game_widget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // setFixedSize(800, 800);
    resize(800, 800);
    // createActions();
    // createMenus();
    // QtMaterialFlatButton *btn = new QtMaterialFlatButton("flat button");
    // btn->setForegroundColor(Qt::blue);
    // btn->setBackgroundColor(Qt::white);
    // btn->setCornerRadius(10);
    // btn->setHaloVisible(false);
    // btn->setBackgroundMode(Qt::OpaqueMode);
    // btn->setFixedWidth(200);
    // btn->setFixedHeight(100);

    WelcomeWidget *welcome_widget = new WelcomeWidget;
    GameWidget *game_widget = new GameWidget;
    controller = new Controller;
    game_widget->bindController(controller);
    QObject::connect(controller, &Controller::updateSnake, game_widget, QOverload<>::of(&GameWidget::update));

    widget_stack = new QStackedWidget(this);
    widget_stack->addWidget(welcome_widget);
    widget_stack->addWidget(game_widget);
    
    connect(welcome_widget, SIGNAL(btnNormalPressed()), this, SLOT(btnNormalPressed()));
    connect(welcome_widget, WelcomeWidget::btnNormalPressed, game_widget, GameWidget::changeGameState);
    setCentralWidget(widget_stack);
    // setCentralWidget(game_widget);
}

void MainWindow::btnNormalPressed() {
    Log::d("button [normal mode] is pressed");
    widget_stack->setCurrentIndex(1);
}

void MainWindow::createActions() {
}

void MainWindow::createMenus() {
    QMenu *menu_option = menuBar()->addMenu(tr("&Options"));
    // menu_option->addAction(action_new_game);
}
