#-------------------------------------------------
#
# Project created by QtCreator 2019-05-08T16:00:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qsnake
TEMPLATE = app
SUBDIRS = ui/components

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cc \
        core/controller.cc \
        ui/game_widget.cc \
        ui/main_window.cc \
        game/brick.cc \
        game/food.cc \
        game/snake.cc \
        game/point.cc \
        log/log.cc \
        ui/welcome_widget.cc


HEADERS += \
        core/controller.h \
        ui/game_widget.h \
        ui/main_window.h \
        game/brick.h \
        game/food.h \
        game/snake.h \
        game/point.h \
        log/log.h \
        ui/welcome_widget.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/images.qrc
