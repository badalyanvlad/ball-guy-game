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

    int getHealth() const;
    bool isDestroyed() const;

    virtual void hit();

    void setPosition(int x, int y);
    void setSize(int w, int h);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_health;
};

#endif // BRICK_H
