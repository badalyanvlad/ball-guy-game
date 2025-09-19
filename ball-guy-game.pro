QT += widgets

CONFIG += c++17 console
CONFIG -= app_bundle

TEMPLATE = app
TARGET = ball-guy-game
SOURCES += main.cpp \
    actor.cpp \
    ball.cpp \
    bonus_brick.cpp \
    brick.cpp \
    bricks_factory.h \
    game_scene.cpp


HEADERS += \
    actor.h \
    ball.h \
    bonus_brick.h \
    brick.h \
    bricks_factory.h \
    game_scene.h
