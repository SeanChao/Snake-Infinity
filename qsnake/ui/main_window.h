#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "../core/controller.h"
#include "game_widget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
   public:
    explicit MainWindow(QWidget *parent = nullptr);

   signals:

   public slots:
    void btnNormalPressed();
    void startGame(int id);

   private:
    Controller *controller;
    GameWidget *game_widget;
    QStackedWidget *widget_stack;
    QAction *action_new_game;

    void createActions();
    void createMenus();

    void connectSignalSlot();   
};

#endif  // MAIN_WINDOW_H
