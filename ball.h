#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QPointF>


class Ball : public QWidget
{
    Q_OBJECT
public:
    explicit Ball(QWidget *parent = nullptr);

    void setVelocity(const QVector2D& v);

    void moveBall ();

    bool doesHitted(QWidget* widget);
private:
    QVector2D velocity;
};

#endif // BALL_H2
