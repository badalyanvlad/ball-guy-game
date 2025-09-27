QT += widgets
QT += multimedia

CONFIG += c++17 console
CONFIG -= app_bundle

TEMPLATE = app
TARGET = ball-guy-game
SOURCES += main.cpp \
    actor.cpp \
    ball.cpp \
    bonus_brick.cpp \
    brick.cpp \
    bricks_manager.cpp \
    game_scene.cpp \
    gameover.cpp


HEADERS += \
    actor.h \
    ball.h \
    bonus_brick.h \
    brick.h \
    bricks_manager.h \
    game_scene.h \
    gameover.h

RESOURCES += \
    resources.qrc
