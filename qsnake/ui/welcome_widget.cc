#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>

#include "welcome_widget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent) : QWidget(parent) {
    QLabel *label = new QLabel("贪吃蛇");
    QPushButton *btn_start = new QPushButton("开始游戏", this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(btn_start);
    connect(btn_start, SIGNAL(clicked()), SIGNAL(btnNormalPressed()));
    setLayout(layout);
}