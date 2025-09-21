#include "game_scene.h"

GameScene::GameScene(int brickCount, int brickRowCount, QWidget *parent)
    : QWidget{parent}
{
    state = State::Default_s;
    bricks_rows = new QVBoxLayout(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameScene::update);
    timer->start(16);

    // for(int i = 0; i < brickRowCount; ++i)
    // {
    //     for(int j = 0; j < brickCount; ++j)
    //     {
    //         //bricks.push_back(Brick());
    //     }
    // }
    creatingBricksRow(10);
    connect(this, &GameScene::bonusSignal, this, [this](){
        addBallsByBonus(5) ;
    });
}

void GameScene::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event);
    set_state(State::BallsAreFlying);
}

void GameScene::mouseMoveEvent(QMouseEvent *event){
    Q_UNUSED(event);
    set_state(State::ActorIsAiming);
}

void GameScene::showAiming(){

}

void GameScene::ballsFlying(){

}


void GameScene::set_state(State st){
    state = st;
    if((state == State::ActorIsAiming || state == State::BallsAreFlying) && !timer->isActive()){
        timer->start(16);
    }
    else{
        timer->stop();
    }
}

void GameScene::update(){
    if(this->state == State::ActorIsAiming){
        showAiming();
    }
    else if(this->state == State::BallsAreFlying){
        ballsFlying();
    }
    else{

    }
}

void GameScene::addBallsByBonus(int count){
    for(int i = 0; i < count; ++i){
        //balls.push_back(Ball{});
    }
}

void GameScene::creatingBricksRow(int count){
    QHBoxLayout *new_row = new QHBoxLayout();
    for(int i = 0; i < count; ++i){
        Brick *newBrick = new Brick(15);
        bricks.push_back(newBrick);
        new_row->addWidget(newBrick);
    }
    new_row->setSpacing(0);
    new_row->setContentsMargins(0, 0, 0, 0);
    bricks_rows->addLayout(new_row);
}











