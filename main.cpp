#include <QApplication>

#include "game_scene.h"

int main(int argc, char * argv[]) {
    QApplication app(argc, argv);
    GameScene scene;
    scene.show();
    return app.exec();
}
