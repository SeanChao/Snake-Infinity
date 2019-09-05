#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "../core/controller.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
   public:
    explicit MainWindow(QWidget *parent = nullptr);

   signals:

   public slots:
    void btnNormalPressed();

   private:
    Controller *controller;
    void createActions();
    void createMenus();
    QStackedWidget *widget_stack;
    QAction *action_new_game;
};

#endif  // MAIN_WINDOW_H
