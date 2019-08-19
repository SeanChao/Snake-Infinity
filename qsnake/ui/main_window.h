#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT
   public:
    explicit MainWindow(QWidget *parent = nullptr);

   signals:

   public slots:
    // void changeWidget();
    
   private:
   void createActions();
   void createMenus();
   QAction *action_new_game;
};

#endif  // MAIN_WINDOW_H
