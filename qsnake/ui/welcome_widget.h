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
    void btnPressed(int id);
    void btnMultiplayerPressed();
    void btnStartPressed(int id);
    
public slots:

private slots:
    void buttonPressed(int id);
};

#endif // WELCOME_WIDGET_H
