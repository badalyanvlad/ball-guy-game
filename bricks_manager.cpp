#include "bricks_manager.h"

BricksManager::BricksManager(QObject *parent)
    : QObject{parent}
{}


// void BrickManager::creatingBricksRow(int count, GameScene *game_scene){
//     QHBoxLayout *new_row = new QHBoxLayout();
//     for(int i = 0; i < count; ++i){
//         Brick *newBrick = new Brick(15);
//         game_scene->getBricks.push_back(newBrick);
//         new_row->addWidget(newBrick);
//     }
//     new_row->setSpacing(0);
//     new_row->setContentsMargins(0, 0, 0, 0);
//     bricks_rows->addLayout(new_row);
// }

