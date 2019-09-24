#ifndef WELCOME_WIDGET_H
#define WELCOME_WIDGET_H

#include <QWidget>

class WelcomeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeWidget(QWidget *parent = nullptr);
    
signals:
    void btnPressed(int id);
    void btnMultiplayerPressed();
    void btnStartPressed(int id);
    
public slots:

private slots:
    void buttonPressed(int id);
};

#endif // WELCOME_WIDGET_H
