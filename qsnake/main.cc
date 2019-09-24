#include <QApplication>
#include <QWidget>
#include "core/controller.h"
#include "log/Log.h"
#include "ui/game_widget.h"
#include "ui/main_window.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    MainWindow main_window;
    main_window.show();
    return application.exec();
}
