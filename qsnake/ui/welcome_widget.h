#ifndef WELCOME_WIDGET_H
#define WELCOME_WIDGET_H

#include <QWidget>
#include "game_window.h"

class WelcomeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeWidget(QWidget *parent = nullptr);
    void setGameWindow(GameWindow *game_window);
    
signals:

public slots:

private:
    void startGame();
    GameWindow *game_window;
};

#endif // WELCOME_WIDGET_H
