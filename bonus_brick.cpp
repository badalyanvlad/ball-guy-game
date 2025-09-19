#include "bonus_brick.h"

#include <QDebug>

BonusBrick::BonusBrick(int health, BonusType type, QWidget *parent)
    : Brick(health, parent), m_type(type)
{
}

BonusBrick::~BonusBrick() {}

BonusBrick::BonusType BonusBrick::bonusType() const
{
    return m_type;
}

void BonusBrick::hit()
{
    Brick::hit();
    //ete brick qandvel e emit bonusDropped
    if (isDestroyed() && m_type != None)
    {
        qDebug() << "Bonus dropped:" << m_type;
        emit bonusDropped(m_type);
    }
}
