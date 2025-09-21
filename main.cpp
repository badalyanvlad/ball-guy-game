#include <QApplication>

#include "game_scene.h"

int main(int argc, char * argv[]) {
    QApplication app(argc, argv);
    GameScene scene(600, 800);
    scene.show();
    return app.exec();
}
