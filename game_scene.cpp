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
            bonus_bricks.push_back(new_bonus_brick);
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
    int scene_width = width();
    int scene_height = height();
    int brick_height = 40;

    for (int i = 0; i < bricks.size(); ++i) {
        int col = i % cols;
        int row = i / cols;

        int x = (col * scene_width) / cols;
        int next_x = ((col + 1) * scene_width) / cols;
        int w = next_x - x;

        if (bricks[i]) {
            bricks[i]->setParent(this);
            bricks[i]->setGeometry(x, row * brick_height, w, brick_height);
        }
    }

    for (int i = 0; i < bonus_bricks.size(); ++i) {
        int idx = bricks.size() + i;
        int col = idx % cols;
        int row = idx / cols;

        int x = (col * scene_width) / cols;
        int next_x = ((col + 1) * scene_width) / cols;
        int w = next_x - x;

        if (bonus_bricks[i]) {
            bonus_bricks[i]->setParent(this);
            bonus_bricks[i]->setGeometry(x, row * brick_height, w, brick_height);
        }
    }
}

// void GameScene::resizeEvent(QResizeEvent *event){
//     const int cols = 15;
//     int scene_width = width();
//     int scene_height = height();
//     for(int i = 0; i < bricks.size(); ++i){
//         bricks[i] -> resize(scene_width/cols, scene_height/10);
//     }
//     for(int i = 0; i < bonus_bricks.size(); ++i){
//         bonus_bricks[i]->resize(scene_width/cols, scene_height/10);
//     }
// }























