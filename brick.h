#ifndef BRICK_H
#define BRICK_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QFont>
#include <QGraphicsTextItem>
#include <QPointF>

class Brick : public QWidget
{
    Q_OBJECT
public:
    explicit Brick(int health , QWidget *parent = nullptr);
    Brick(int health, int x, int y, int h = 40, int w = 40, QWidget *parent = nullptr);
    void reduce_health();

signals:
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    int health;
    QRect rect_m;
    QLabel *brick_label;
};

#endif // BRICK_H
