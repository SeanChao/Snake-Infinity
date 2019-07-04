#include <QApplication>
#include <QLabel>
#include "core/controller.h"
#include "log/Log.h"
#include "ui/game_window.h"

int main(int argc, char *argv[]) {
    Log::d("****** Application is running! ******");
    QApplication application(argc, argv);
    // MainWindow main_window;
    // main_window.show();
    GameWindow game_window;
    game_window.show();

    Controller controller;
    game_window.bindController(&controller);
    
    Log::d("****** Application ended! ******");
    return application.exec();
}
