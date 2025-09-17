#include "brick.h"

Brick::Brick(int health, QWidget *parent)
     : QWidget{parent}, m_health(health)
{
    setFixedSize(25,25);
}
Brick::~Brick(){}

int Brick::getHealth() const
{
    return m_health;
}
bool Brick::isDestroyed() const
{
    return m_health == 0;
}
void Brick::hit()
{
    if(m_health > 0)
    {
        --m_health;
    }
}
void Brick::setPosition(int x, int y)
{
    move(x, y);
}
void Brick::setSize(int w, int h)
{
    move(w, h);
}

void Brick::paintEvent(QPaintEvent *event) override
{
    QPainter painter(this);

    if(m_health == 4)
    {
        painter.setBrush(Qt::red);
    }
    else if(m_health == 2)
    {
        painter.setBrush((Qt::green));
    }
    else if(m_health == 1)
    {
        painter.setBrush(Qt::blue);
    }
    else
    {
        painter.setBrush((Qt::yellow));
    }

    painter.setPen(Qt::black);
    painter.drawRect(rect());

}
