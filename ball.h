#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QRect>
#include "brick.h"

class Ball : public QWidget
{
    Q_OBJECT
public:
    explicit Ball(QWidget *parent = nullptr);

    void setVelocity(const QVector2D& v);

    bool doesHitted(QWidget* widget);
};

#endif // BALL_H
 //velocity gndaki skzbnakan dirqy (0,0)
