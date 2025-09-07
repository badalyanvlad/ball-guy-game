#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <QWidget>

class GameScene : public QWidget
{
    Q_OBJECT
public:
    explicit GameScene(QWidget *parent = nullptr);

signals:
};

#endif // GAME_SCENE_H
