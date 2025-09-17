#include "game_scene.h"

GameScene::GameScene(/*int brickCount, int brickRowCount,*/ QWidget *parent)
    : QWidget{parent}
{
    s = State::Wait;
    for(int i = 0; i < 5; ++i){
        Ball* ball1 = new Ball(this);
        ball1->setGeometry(ball1->pointX,ball1->pointY,10,10);
        ball1->setStyleSheet(
            "background-color: red;"
            "border-radius: 5px;"
            "color: white;"
            );
        balls.push_back(ball1);

    }

    this->setFixedSize(400,600);

    actor = new Actor(this);
    QPixmap pixmap (":/images/nkar.png");
    actor->setPixmap(pixmap);
    actor->setScaledContents(true);
    actor->setGeometry(190,570,30,30);


    const int raw_count = 4;
    QList<int> positions;
    for(int i = 0; i < 10; ++i){
        positions.push_back(i);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(positions.begin(), positions.end(), g);

    for(int i = 0 ; i < raw_count; ++i){
        int brick_count = QRandomGenerator::global()->bounded(1,11);

        for(int j = 0 ; j < brick_count; ++j){
            int brick_life = QRandomGenerator::global()->bounded(1,21);
            QLabel* brick = new QLabel(QString::number(brick_life),this);
            int brick_place = positions[j];
            brick->setGeometry(brick_place*40,i*40,40,40);
            brick->setStyleSheet("background-color: red;"
                                 "color:white;"
                                 "border:2px solid black;"
                                 "border-radius:8px");
            brick->setAlignment(Qt::AlignCenter);
            bricks.push_back(brick);
        }
        std::shuffle(positions.begin(), positions.end(), g);
    }



    timer = new QTimer;

    ball = new Ball(this);
    // ball->setGeometry(ball->pointX,ball->pointY,10,10);
    // ball->setStyleSheet(
    //     "background-color: red;"
    //     "border-radius: 5px;"
    //     "color: white;"
    //     );

    QObject::connect(timer, &QTimer::timeout,this,&GameScene::fireAnim);
    QObject::connect(this,&GameScene::readyToFire,this,&GameScene::fire);

    QPushButton * btn = new QPushButton("2x",this);
    btn->setGeometry(360,560,30,30);
    connect(btn, &QPushButton::clicked, [this,btn](){
        if(btn->text() == "2x"){
            ball->setVelocity(ball->getVelocity()*2);
            btn->setText("1x");
        }else{
            ball->setVelocity(ball->getVelocity()/2);
            btn->setText("2x");
        }
    });

}
void GameScene::fireAnim(){
    if(currentBallIndex >= balls.size()){
        timerStop();
        return;
    }

    Ball* ball1 = balls[currentBallIndex];

    for(Ball* ball1: balls){
        double nextX = ball1->pointX + ball1->getVelocity() * dx;
        double nextY = ball1->pointY + ball1->getVelocity() * dy;

        QRect ballRect(nextX, nextY, ball1->width(), ball1->height());

        bool collided = false;

        for (int i = 0; i < bricks.size(); ++i) {
            QWidget* w = bricks.at(i);
            QRect blockRect = w->geometry();

            if (ballRect.intersects(blockRect)) {
                QLabel* label = dynamic_cast<QLabel*>(w);
                bool ok = false;
                int value = label->text().toInt(&ok);
                if (!ok) value = 1;

                value--;
                if (value <= 0) {
                    w->hide();
                    delete w;
                    bricks.removeAt(i);
                    i--;
                } else {
                    label->setText(QString::number(value));
                }

                if (ballRect.bottom() <= blockRect.top() + ball1->height() || ballRect.top() >= blockRect.bottom() - ball1->height()) {
                    dy = -dy;
                } else {
                    dx = -dx;
                }
                collided = true;
                break;
            }
        }

        if (!collided) {
            ball1->pointX = nextX;
            ball1->pointY = nextY;
        } else {
            ball1->pointX += ball1->getVelocity() * dx;
            ball1->pointY += ball1->getVelocity() * dy;
        }

        if (ball1->pointX <= 0 || ball1->pointX >= (double)this->size().width() - (double)ball1->size().width()) dx = -dx;
        if (ball1->pointY <= 0) dy = -dy;
        if (ball1->pointY >= (double)this->size().height() - (double)ball1->size().height()){
            //std::clamp(ballY,0.0,590.0);
            qDebug() << ball1->pointY;
            actor->move(ball1->pointX - 10);
            actor->setPoint(ball1->pointX);
            ball1->move(actor->pointX, actor->pointY);
            timerStop();

            currentBallIndex++;  // переходим к следующему шару
            if(currentBallIndex < balls.size()){
                balls[currentBallIndex]->pointX = actor->pointX;
                balls[currentBallIndex]->pointY = actor->pointY;
            } else {
                timerStop();  // все шары вылетели
            }
            return;
        }

        ball1->move(ball1->pointX, ball1->pointY);
    }

}
void GameScene::mousePressEvent(QMouseEvent *event) {
    if(event->type() == QEvent::MouseButtonPress){
        auto *mouseEvent = static_cast<QMouseEvent*>(event);

        if(s != State::Wait || (mouseEvent->pos().x() > 350 && mouseEvent->pos().y() > 550)){
            event->ignore();
        }else{
            s = State::ActorIsAiming;
            mouseupdate(mouseEvent->pos().x(), mouseEvent->pos().y());
            event->accept();
        }
    }

}

/**
     * fires balls
     */
void GameScene::mouseMoveEvent(QMouseEvent *event)  {
    if(s != State::ActorIsAiming){
        event->ignore();
        return;

    }else{
        for(QLabel* label : ballsForAim){
            if(label){
                label->hide();
                delete label;
            }
        }
        ballsForAim.clear();
        auto* mouseEvent = static_cast<QMouseEvent*>(event);
        mouseupdate(mouseEvent->pos().x(), mouseEvent->pos().y());
        event->accept();
        return;
    }
}
void GameScene::mouseReleaseEvent(QMouseEvent* event){
    for(QLabel* label: ballsForAim){
        label->hide();
        delete label;
    }
    ballsForAim.clear();
    //s = State::BallsAreFlying;
    emit readyToFire(dx,dy);
    event->accept();
}
void GameScene::mouseupdate(double mousePosX, double mousePosY){
    double x1 = actor->pointX;
    double y1 = actor->pointY;
    double x2 = mousePosX;
    double y2 = mousePosY;
    double curx = actor->pointX, cury = actor->pointY;
    double L = std::sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    qDebug() << mousePosX << mousePosY;
    dx = (x2 - x1) / L;
    dy = (y2 - y1) / L;
    double dx1 = dx;
    double dy1 = dy;
    int k = 4;
    for (int i = 0; i < 50; ++i) {
        curx += 10 * dx1;
        cury += 10 * dy1;

        if (curx <= 0 || curx >= (double)this->width() - 10) {
            dx1 = -dx1;
            curx = std::clamp(curx, 0.0, (double)this->width() - 10);
        }
        if(k == 4 || curx == (double)this->width() - 10 || curx == 0 ){
            QLabel* ball1 = new QLabel(this);
            ball1->setGeometry(curx, cury, 10, 10);
            ball1->setStyleSheet(
                "background-color: red;"
                "border-radius: 5px;"
                );
            ball1->show();
            ballsForAim.push_back(ball1);
        }
        k--;
        if(!k)k = 4;
    }

}
void GameScene::fire(double dx1, double dy1){


    if(s == State::ActorIsAiming){
        s = State::BallsAreFlying;
        this->dx = dx1;
        this->dy = dy1;

            currentBallIndex = 0;
            balls[currentBallIndex]->pointX = actor->pointX;
            balls[currentBallIndex]->pointY = actor->pointY;

        timer->start(20);
    }else{
        return;
    }

}
void GameScene::timerStop(){
    s = State::Wait;
    timer->stop();
}

