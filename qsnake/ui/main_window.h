#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class QGraphicsView;
class GameController;

class MainWindow: public QMainWindow {
    Q_OBJECT
   public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

   private slots:
    void adjustViewSize();
   
   private:
    void initScene();
    void initSceneBackground();

    QGraphicsScene *scene;
    QGraphicsView *view;

    GameController *game;
};
#endif  //MAIN_WINDOW_H