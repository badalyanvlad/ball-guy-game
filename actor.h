#ifndef ACTOR_H
#define ACTOR_H

#include <QWidget>

class Actor : public QWidget
{
    Q_OBJECT
public:
    explicit Actor(QWidget *parent = nullptr);

signals:
};

#endif // ACTOR_H
