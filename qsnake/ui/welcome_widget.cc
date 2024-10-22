#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>
#include "../log/Log.h"
#include "welcome_widget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent) : QWidget(parent) {
    QLabel *label = new QLabel("贪吃蛇");
    label->setAlignment(Qt::AlignHCenter);
    QPushButton *btn_start = new QPushButton("开始游戏", this);
    QPushButton *btn_multi_start = new QPushButton("双人模式", this);
    QPushButton *btn_ai_mode = new QPushButton("AI 模式", this);
    label->setStyleSheet("font: 18pt");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(btn_start);
    layout->addWidget(btn_multi_start);
    layout->addWidget(btn_ai_mode);
    layout->setAlignment(Qt::AlignVCenter);
    connect(btn_start, &QPushButton::clicked, this,
            [this] { buttonPressed(1); });
    connect(btn_multi_start, &QPushButton::clicked, this,
            [this] { buttonPressed(2); });
    connect(btn_ai_mode, &QPushButton::clicked, this,
            [this] { buttonPressed(3); });
    setLayout(layout);
}

void WelcomeWidget::buttonPressed(int id) {
    Log::d("WelcomeWidget get signal -> buttonPressed id: " +
           std::to_string(id));
    emit btnPressed(id);
}