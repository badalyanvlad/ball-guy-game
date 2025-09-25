#pragma once
#include <QWidget>
#include <QVector2D>
#include "ball.h"

class Actor : public QWidget
{
    Q_OBJECT
public:
    explicit Actor(QWidget *parent = nullptr);

    void move(float x, float y);

    void fire(float angle, const QVector<Ball*>& balls);

protected:
    void paintEvent(QPaintEvent *event) override;
};
