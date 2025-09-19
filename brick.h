#ifndef BRICK_H
#define BRICK_H

#include <QWidget>
#include <QPainter>

class Brick : public QWidget
{
    Q_OBJECT
public:
    explicit Brick(int health, QWidget *parent = nullptr);
    virtual ~Brick();

    bool isDestroyed() const;

    virtual void hit();

    void setSize(int w, int h);

private:
    int m_health;
};

#endif // BRICK_H
