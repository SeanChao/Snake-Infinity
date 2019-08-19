#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>

#include "welcome_widget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent) : QWidget(parent) {
    // QSpinBox *spinBox = new QSpinBox(this);
    // QSlider *slider = new QSlider(Qt::Horizontal, this);
    // spinBox->setRange(0, 130);
    // slider->setRange(0, 130);

    // QObject::connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
    // void (QSpinBox:: *spinBoxSignal)(int) = &QSpinBox::valueChanged;
    // QObject::connect(spinBox, spinBoxSignal, slider, &QSlider::setValue);
    // spinBox->setValue(35);

    // QHBoxLayout *layout = new QHBoxLayout;
    // layout->addWidget(label);
    // layout->addWidget(spinBox);
    // layout->addWidget(slider);
    // setLayout(layout);

    QLabel *label = new QLabel("贪吃蛇");
    QPushButton *btn_start = new QPushButton("开始游戏", this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(btn_start);
    connect(btn_start, &QPushButton::clicked, this, &startGame);
    setLayout(layout);
}

void WelcomeWidget::setGameWindow(GameWindow *gw) {
    game_window = gw;
}

void WelcomeWidget::startGame() {
    
}