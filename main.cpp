#include <QApplication>
#include <QWidget>
#include "game_scene.h"

int main(int argc, char * argv[]) {
    QApplication app(argc, argv);
    GameScene scene;
    scene.show();
    // QWidget eidgt;
    // eidgt.show();
    return app.exec();
}
