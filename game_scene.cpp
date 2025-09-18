#include "game_scene.h"

GameScene::GameScene(QWidget *parent)
    : QWidget{parent},s(State::Wait),actorpos(false),currentBallIndex(0),count(0)
{
    lowestBrick = 160;
    this->setFixedSize(400,600);
    for(int i = 0; i < 50; ++i){
        Ball* ball1 = new Ball(this);
        balls.push_back(ball1);
    }
    brickCreating();
    actor = new Actor(this,50);

    timer = new QTimer;
    QObject::connect(timer, &QTimer::timeout,this,&GameScene::fireAnim);

    QPushButton * btn = new QPushButton("2x",this);
    btn->setGeometry(360,560,30,30);
    connect(btn, &QPushButton::clicked, [this,btn](){
        // if(btn->text() == "2x"){
        //     for(Ball* ball : balls ){
        //         ball->setVelocity(ball->getVelocity()*2);
        //     }
        //     btn->setText("1x");
        // }else{
        //     for(Ball* ball : balls ){
        //         ball->setVelocity(ball->getVelocity()/2);
        //     }
        //     btn->setText("2x");
        // }
    });

}
void GameScene::fireAnim(){
    count++;
    if(currentBallIndex < balls.size() && count  == 5){
        this->balls[currentBallIndex]->setVelocity(dx,dy);
        currentBallIndex++;
    }


    if(count > 5 ){
        count = 0;
    }

        for(Ball* ball1: balls){

            if(ball1->dx == 0 && ball1->dy == 0){
                continue;
            }
            double nextX = ball1->pointX + ball1->dx;
            double nextY = ball1->pointY + ball1->dy;

            QRect ballRect(nextX, nextY, ball1->width(), ball1->height());

            bool collided = false;

            for (int i = 0; i < bricks.size(); ++i) {
                Brick* w = bricks.at(i);
                QRect blockRect = w->geometry();

                if (ballRect.intersects(blockRect)) {
                    bricks[i]->changeHealth();

                    if ((ballRect.bottom() <= blockRect.top() + ball1->height() && dy > 0)
                    || (ballRect.top() >= blockRect.bottom() - ball1->height() && dy < 0)){
                        ball1->dy *= -1;
                    } else {
                        ball1->dx *= -1;
                    }
                    collided = true;
                    break;
                }
            }

            if (!collided) {
                ball1->pointX = nextX;
                ball1->pointY = nextY;
            } else {
                ball1->pointX += ball1->dx;
                ball1->pointY += ball1->dy;
            }

            if (ball1->pointX <= 0 || ball1->pointX >= (double)this->size().width() - (double)ball1->size().width()) ball1->dx *= -1;
            if (ball1->pointY <= 0) ball1->dy *= -1;
            if (ball1->pointY >= (double)this->size().height() ){
                qDebug() << ball1->pointY;
                if(!actorpos){
                    std::clamp(ball1->pointX,0.0,570.0);
                    actor->move(ball1->pointX - 12);
                    actor->setPoint(ball1->pointX);
                    actorpos = true;
                }
                k1++;
                actor->setBallCount(k1);
                ball1->move(actor->pointX, actor->pointY);
                ball1->pointX = actor->pointX;
                ball1->pointY = actor->pointY;
                ball1->setVelocity(0, 0);
            }

            if(k1 == balls.size()){

                timerStop();
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
    if(s != State::ActorIsAiming){
        event->ignore();
    }
    else{
        for(QLabel* label: ballsForAim){
            label->hide();
            delete label;
        }
        ballsForAim.clear();
        //s = State::BallsAreFlying;
        fire();
        event->accept();
    }
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
void GameScene::fire(){

    k1 = 0;
    currentBallIndex = 0;
    actorpos = false;
    if(s == State::ActorIsAiming){
        s = State::BallsAreFlying;

        for(Ball* ball1:balls){
            ball1->pointX = actor->pointX;
            ball1->pointY = actor->pointY;
        }
        timer->start(10);
    }else{
        return;
    }

}
void GameScene::addNewLineBrickes(){
    int brick_count = QRandomGenerator::global()->bounded(1,11);
    QList<int> positions;
    for(int i = 0; i < 10; ++i){
        positions.push_back(i);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(positions.begin(), positions.end(), g);

    for(Brick* brick : bricks){
        brick->setGeometry(brick->geometry().x(),brick->geometry().y() + 40,40,40);
    }
    for(int j = 0 ; j < brick_count; ++j){
        int brick_life = QRandomGenerator::global()->bounded(1,80);
        Brick* brick = new Brick(brick_life,this);
        QObject::connect(brick,&Brick::brickDestroyed,this,&GameScene::removeBrick);
        int brick_place = positions[j];
        brick->setGeometry(brick_place*40,0,40,40);
        if(brick->geometry().y() + 40 > lowestBrick){
            lowestBrick = brick->geometry().y() + 40;
        }
        bricks.push_back(brick);
        brick->show();
    }
}
void GameScene::timerStop(){
    s = State::Wait;
    count = 0;
    currentBallIndex = 0;
    addNewLineBrickes();
    timer->stop();
}

void GameScene::brickCreating(){
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
            int brick_life = QRandomGenerator::global()->bounded(1,80);
            Brick* brick = new Brick(brick_life,this);
            QObject::connect(brick,&Brick::brickDestroyed,this,&GameScene::removeBrick);
            int brick_place = positions[j];
            brick->setGeometry(brick_place*40,i*40,40,40);

            bricks.push_back(brick);
        }
        std::shuffle(positions.begin(), positions.end(), g);
    }
}
void GameScene::removeBrick(Brick* brick){
    brick->hide();
    delete brick;
    bricks.removeOne(brick);
}

