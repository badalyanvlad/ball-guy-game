#include "game_scene.h"

GameScene::GameScene(QWidget *parent)
    : QWidget{parent}
{
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::cyan);
    setPalette(palette);
    state = State::Default_s;
     timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameScene::update);
    timer->start(16);
    creating_brick_row();
    creating_brick_row();
    creating_brick_row();
    // connect(this, &GameScene::bonusSignal, this, [this](){
    //     addBallsByBonus(5) ;
    // });
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

QVector<Brick*> GameScene::getBricks(){
    return bricks;
}

void GameScene::creating_brick_row(){
    static int start_height = 0;
    int start_width = 0;
    for(int i = 0; i < 15; ++i){
        int random_value = QRandomGenerator::global()->bounded(1, 11);
        int random_health = QRandomGenerator::global()->bounded(1,51);
        if(random_value == 3){
            BonusBrick *new_bonus_brick = new BonusBrick();
            new_bonus_brick->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            bonusBricks.push_back(new_bonus_brick);
            new_bonus_brick->setGeometry(start_width, start_height, 40, 40);
            start_width += 40;
        }
        else if(random_value != 2 && random_value != 8){
            Brick *new_brick = new Brick(random_health);
            bricks.push_back(new_brick);
            new_brick->setGeometry(start_width, start_height, 40, 40);
            start_width += 40;
        }
        else{
            start_width += 40;
        }
    }
    start_height +=40;
}

void GameScene::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    const int cols = 15;
    int sceneWidth = width();
    int brickH = 40;

    for (int i = 0; i < bricks.size(); ++i) {
        int col = i % cols;
        int row = i / cols;

        int x = (col * sceneWidth) / cols;
        int nextX = ((col + 1) * sceneWidth) / cols;
        int w = nextX - x;

        if (bricks[i]) {
            bricks[i]->setParent(this);
            bricks[i]->setGeometry(x, row * brickH, w, brickH);
        }
    }

    for (int i = 0; i < bonusBricks.size(); ++i) {
        int idx = bricks.size() + i;
        int col = idx % cols;
        int row = idx / cols;

        int x = (col * sceneWidth) / cols;
        int nextX = ((col + 1) * sceneWidth) / cols;
        int w = nextX - x;

        if (bonusBricks[i]) {
            bonusBricks[i]->setParent(this);
            bonusBricks[i]->setGeometry(x, row * brickH, w, brickH);
        }
    }
}




















