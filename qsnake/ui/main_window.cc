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

    WelcomeWidget welcome_widget;

    GameWidget *game_widget = new GameWidget;
    Controller *controller = new Controller;
    game_widget->bindController(controller);
    QObject::connect(controller, &Controller::updateSnake, game_widget, QOverload<>::of(&GameWidget::update));
    Log::d("connect succeeded");
    setCentralWidget(game_widget);
    Log::d("GameWidget is set as central Widget");
}

void MainWindow::createActions() {
}

void MainWindow::createMenus() {
    QMenu *menu_option = menuBar()->addMenu(tr("&Options"));
    // menu_option->addAction(action_new_game);
}
