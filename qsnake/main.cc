#include <QApplication>
#include <QWidget>
#include "core/controller.h"
#include "log/Log.h"
#include "ui/game_widget.h"
#include "ui/game_window.h"
#include "ui/main_window.h"

int main(int argc, char *argv[]) {
    Log::d("****** Application is running! ******");
    QApplication application(argc, argv);
    MainWindow main_window;
    // MaterialWidget mw; mw.show();
    // GameWindow game_window;
    // Controller controller;
    // game_window.bindController(&controller);
    // QObject::connect(&controller, Controller::updateSnake, &game_window, GameWindow::renderNow);

    // game_window.show();
    // main_window.setGameWindow(game_window);
    main_window.show();

    // GameWidget gw;
    // Controller *controller = new Controller;
    // gw.bindController(controller);
    // gw.show();
    return application.exec();
}
