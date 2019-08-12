#include <QApplication>
#include <QLabel>
#include "core/controller.h"
#include "log/Log.h"
#include "ui/game_window.h"

int main(int argc, char *argv[]) {
    Log::d("****** Application is running! ******");
    QApplication application(argc, argv);
    GameWindow game_window;

    Controller controller;
    game_window.bindController(&controller);
    QObject::connect(&controller, Controller::updateSnake, &game_window, GameWindow::renderNow);

    game_window.show();
    return application.exec();
}
