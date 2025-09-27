#include "game_scene.h"

GameScene::GameScene(QWidget *parent)
    : QMainWindow{parent},s(State::Wait),currentBallIndex(0),count(0){

    gameoverWidget = new GameOver();
    gameWidget = new QWidget();
    this->setCentralWidget(gameWidget);
    gameWidget->resize(400,600);
    actor = new Actor(gameWidget,50);

    for(int i = 0; i < 50; ++i){
        Ball* ball1 = new Ball(gameWidget);
        ball1->setPos(actor->getPosX() + ball1->width(),
                      actor->getPosY() - ball1->height());
        balls.push_back(ball1);
    }
    brickCreating();


    timer = new QTimer;
    QObject::connect(timer, &QTimer::timeout,this,&GameScene::fireAnim);
    btn = new QPushButton("2x",gameWidget);
    btn->resize(30,30);
    btn->move(gameWidget->width() - btn->width(),gameWidget->height() - btn->height());
    connect(btn, &QPushButton::clicked, [this](){
        if(btn->text() == "2x"){
            for(Ball* ball : balls ){
                ball->setVelocity(ball->getVelocity()*2);
            }
            btn->setText("1x");
        }else{
            for(Ball* ball : balls ){
                ball->setVelocity(ball->getVelocity()/2);
            }
            btn->setText("2x");
        }
    });


}

void GameScene::fireAnim(){
    count++;
    if(currentBallIndex < balls.size() && count  == balls[0]->width()/2){
        this->balls[currentBallIndex]->setVector(QVector2D(dx,dy));
        currentBallIndex++;
    }

    if(count > balls[0]->width()/2 ){
        count = 0;
    }

    for(Ball* ball1: balls){

        if(ball1->getVector() == QVector2D(0,0)){
            continue;
        }
        double nextX = ball1->getPosX() + ball1->getVelocity() * ball1->getVector().x();
        double nextY = ball1->getPosY() + ball1->getVelocity() * ball1->getVector().y();

        QRect ballRect(nextX, nextY, ball1->width(), ball1->height());

        for (int i = 0; i < bricks.size(); ++i) {
            Brick* w = bricks.at(i);
            QRect blockRect = w->geometry();

            if (ballRect.intersects(blockRect)) {
                bricks[i]->changeHealth();

                double overlapLeft   = ballRect.right()  - blockRect.left();
                double overlapRight  = blockRect.right() - ballRect.left();
                double overlapTop    = ballRect.bottom() - blockRect.top();
                double overlapBottom = blockRect.bottom() - ballRect.top();

                double minOverlapX = std::min(overlapLeft, overlapRight);
                double minOverlapY = std::min(overlapTop, overlapBottom);

                if (minOverlapX < minOverlapY) {
                    ball1->setVector(QVector2D(-1 * ball1->getVector().x(),ball1->getVector().y()));
                    if (overlapLeft < overlapRight)
                        nextX = blockRect.left() - ball1->width();
                    else
                        nextX = blockRect.right();
                } else {
                    ball1->setVector(QVector2D(ball1->getVector().x(), -1 * ball1->getVector().y()));
                    if (overlapTop < overlapBottom)
                        nextY = blockRect.top() - ball1->height();
                    else
                        nextY = blockRect.bottom();
                }


                 break;
            }
        }

        if (nextX <= 0 || nextX >= (double)gameWidget->size().width() - (double)ball1->size().width()){
            ball1->setVector(QVector2D(-1 * ball1->getVector().x(),ball1->getVector().y()));
            nextX += ball1->getVector().x();
        }
        if (nextY <= 0){
            ball1->setVector(QVector2D(ball1->getVector().x(),-1 * ball1->getVector().y()));
            nextY += ball1->getVector().y();
        }
        if (nextY >= (double)gameWidget->size().height()) {
            if(k1 == 0){
                actor->setPos(nextX - actor->width()/4, gameWidget->height() - actor->height());
            }

            ball1->setVector(QVector2D(0,0));

            ball1->setPos(actor->geometry().x() + (actor->width()/4 - ball1->width()/2),actor->getPosY() - ball1->height());

            k1++;
            actor->setBallCount(k1);
            if (k1 == balls.size()) {
                timerStop();
                return;
            }
            continue;
        }

        ball1->setPos(nextX,nextY);

    }
}


void GameScene::mousePressEvent(QMouseEvent *event) {
    if(event->type() == QEvent::MouseButtonPress){

        if(s != State::Wait ||
            (event->pos().x() > btn->geometry().x() && event->pos().y() > btn->geometry().y())){
            event->ignore();
        }else{
            s = State::ActorIsAiming;
            mouseupdate(event->pos().x(), event->pos().y());
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
        mouseupdate(event->pos().x(), event->pos().y());
        event->accept();
        return;
    }
}
void GameScene::mouseReleaseEvent(QMouseEvent* event){
    if(s != State::ActorIsAiming){
        event->ignore();
    }
    else{
        qDebug() << "mouseRelease" << event->pos() ;

        for(QLabel* label: ballsForAim){
            label->hide();
            delete label;
        }
        ballsForAim.clear();
        fire();
        event->accept();
    }
}

void GameScene::mouseupdate(double mousePosX, double mousePosY){
    double x1  = actor->geometry().x() + (actor->width()/4 - balls[0]->width()/2);
    double y1 =  actor->getPosY() - balls[0]->width();
    double x2 = mousePosX;
    double y2 = mousePosY;
    double curx = x1, cury = y1;
    double L = std::sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    qDebug() << mousePosX << mousePosY;

    dx = (x2 - x1) / L;
    dy = (y2 - y1) / L;

    if(dy > 0 ){
        dy *= -1;
    }

    double dx1 = dx;
    double dy1 = dy;
    int k = balls[0]->width()/3;
    for (int i = 0; i < 50; ++i) {
        curx += 10 * dx1;
        cury += 10 * dy1;

        if (curx <= 0 || curx >= (double)gameWidget->width() - balls[0]->width()) {
            dx1 = -dx1;
            curx = std::clamp(curx, 0.0, (double)gameWidget->width() - balls[0]->width());
        }
        if(k == balls[0]->width()/3  || curx == (double)gameWidget->width() - balls[0]->width() || curx == 0 ){
            QLabel* ball1 = new QLabel(gameWidget);
            ball1->setGeometry(curx, cury, balls[0]->width(), balls[0]->width());
            ball1->setStyleSheet(
                QString("background-color: red;"
                "border-radius: %1px;").arg(balls[0]->width()/2));
            ball1->show();
            ballsForAim.push_back(ball1);
        }
        k--;
        if(!k)k = balls[0]->width()/3;
    }

}
void GameScene::fire(){

    k1 = 0;
    currentBallIndex = 0;
    if(s == State::ActorIsAiming){
        s = State::BallsAreFlying;

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

    bool gameover = false;
    for(Brick* brick : bricks){
        brick->move(brick->geometry().x(),brick->geometry().y() + gameWidget->height()/15);
        brick->setPos(brick->getPosI() + 1,brick->getPosJ());
        if(brick->geometry().y() + brick->height() >= gameWidget->height() - brick->height()){
            gameover = true;
        }
    }

    for(int j = 0; j < brick_count; ++j){
        int brick_life = QRandomGenerator::global()->bounded(1,80);
        Brick* brick = new Brick(brick_life,gameWidget);
        QObject::connect(brick,&Brick::brickDestroyed,this,&GameScene::removeBrick);
        int brick_place = positions[j];
        int brickSize = gameWidget->width()/10;
        brick->setGeometry(brick_place*brickSize,0,brickSize,gameWidget->height()/15);
        brick->setPos(0,brick_place);
        bricks.push_back(brick);
        brick->show();
    }

    if(gameover){
        QThread::sleep(2);
        this->setCentralWidget(gameoverWidget);
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

        for(int j = 0; j < brick_count; ++j){
            int brick_life = QRandomGenerator::global()->bounded(1,80);
            Brick* brick = new Brick(brick_life,gameWidget);
            QObject::connect(brick,&Brick::brickDestroyed,this,&GameScene::removeBrick);
            int brick_place = positions[j];
            int brickSize = gameWidget->width()/10;
            brick->setGeometry(brick_place * brickSize,i * brickSize,brickSize,gameWidget->height()/15);
            brick->setPos(i,brick_place);
            bricks.push_back(brick);
            brick->show();
        }
        std::shuffle(positions.begin(), positions.end(), g);
    }
}

void GameScene::removeBrick(Brick* brick){
    brick->hide();
    delete brick;
    bricks.removeOne(brick);
}


void GameScene::resizeEvent(QResizeEvent* ){
    int brickSize = gameWidget->width()/10;
    for(Brick* brick: bricks){
        brick->setGeometry(brick->getPosJ() * brickSize,brick->getPosI() * gameWidget->height()/15,brickSize,gameWidget->height()/15);
    }
    actor->updateSize();

    for(Ball* ball: balls){
        ball->resize(gameWidget->width() * gameWidget->height() / 20000,gameWidget->width() * gameWidget->height() / 20000);
        ball->setPos(actor->geometry().x() + (actor->width()/4 - ball->width()/2),actor->getPosY() - ball->height());
        ball->setStyleSheet(QString("background-color: red; border-radius: %1px;").arg(ball->width()/2));
    }
    btn->move(gameWidget->width() - btn->width(),gameWidget->height() - btn->height());


}

