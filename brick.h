#ifndef BRICK_H
#define BRICK_H

#include <QWidget>

class Brick : public QWidget {
    Q_OBJECT
public:
    explicit Brick(int health, QWidget *parent = nullptr);
    virtual ~Brick() {}
    bool isDestroyed() const { return m_health <= 0; }
    virtual void hit();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    int m_health;
};

#endif
