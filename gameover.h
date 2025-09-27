#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
class GameOver:public QWidget
{
public:
    GameOver(QWidget* parent = nullptr);
    QLabel* label;
};

#endif // GAMEOVER_H
