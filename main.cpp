#include <QApplication>
#include "game_scene.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GameScene scene(50,50);
    scene.startGame();
    scene.show();

    return app.exec();
}
