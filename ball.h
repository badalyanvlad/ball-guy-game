#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QVector2D>

class Ball : public QWidget {
public:
    Ball(QWidget *parent = nullptr);
    void setVelocity(const QVector2D& v);
    QVector2D velocity() const;
    bool doesHitted(QWidget* widget);
    void moveBall();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QVector2D m_velocity;
};

#endif
