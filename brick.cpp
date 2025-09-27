#include "brick.h"

Brick::Brick(int health, QWidget *parent)
    : QWidget{parent}
{
    resize(40,40); // resize
    brick_label = new QLabel(this);
    QFont font;
    font.setBold(true);
    brick_label->setFont(font);
    brick_label->setText(QString::number(health));
    QVBoxLayout *brick_layout = new QVBoxLayout(this);
    brick_layout->addWidget(brick_label, 0, Qt::AlignCenter);
    this->setLayout(brick_layout);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setContentsMargins(0, 0, 0, 0);
}

Brick::Brick(int health, int x, int y, int h, int w, QWidget *parent) : QWidget{parent}, health(health), rect_m(x,y,w,h){
    this->health = health;
    resize(40,40);
}

void Brick::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(Qt::red);
    QPen pen(Qt::black);
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawRect(rect());
    // QPainter p(this);
    // p.setRenderHint(QPainter::Antialiasing);
    // p.setPen(Qt::NoPen);
    // p.setBrush(QColor(180, 60, 30));
    // p.drawRect(rect());
}

void Brick::reduce_health(){
    health -= 1;
    if(health <= 0){
        hide();
    }
}


























