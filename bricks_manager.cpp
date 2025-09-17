#include "bricks_manager.h"
#include <QDebug>

BricksManager::BricksManager(QObject *parent)
    : QObject(parent),
    m_brickWidth(0),
    m_brickHeight(0)
{
}

BricksManager::~BricksManager()
{
    reset();
}

void BricksManager::createBricks(int rows, int cols, int brickWidth, int brickHeight, QWidget *parent)
{
    qDeleteAll(m_bricks); //jnjum e naxord xaxic mnaacac brickery
    m_bricks.clear();

    m_brickWidth = brickWidth;
    m_brickHeight = brickHeight;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int hp = QRandomGenerator::global()->bounded(1, 50); // 1–50 health

            // voroshenq BonusBrick e te sovorakan Brick
            bool makeBonus = (QRandomGenerator::global()->bounded(100) < 20); // 20% havaanakanutyun vor bonus brick kklini

            Brick *brick = nullptr;
            if (makeBonus) {   //ete bonus e petq e stexcvi
                auto type = static_cast<BonusBrick::BonusType>(
                    QRandomGenerator::global()->bounded(1, 7)); // random bonus enq yntrum
                auto *bbrick = new BonusBrick(hp, type, parent);
                connect(bbrick, &BonusBrick::bonusDropped, this, &BricksManager::bonusDropped);   //signal sloty kapum e vor erb bonus ynkni managery imana
                brick = bbrick;
            } else {
                brick = new Brick(hp, parent);  //hakarak depqum sovorakan brick e stexcum
            }

            brick->setGeometry(j * (brickWidth + 5),  //sahmaanum enq bricki dirqy window mej x,y ev bricki chapery
                               i * (brickHeight + 5),
                               brickWidth,
                               brickHeight);
            brick->show();

            m_bricks.append(brick);         //manageri vectori mej avelacvum e bricky
        }
    }
}

const QVector<Brick*>& BricksManager::bricks() const
{
    return m_bricks;  //veradardznum e brickeri vectory
}

bool BricksManager::allDestroyed() const  //veradardxznum e true ete bolor brickery qandvac en
{
    for (Brick *b : m_bricks) {
        if (!b->isDestroyed())
            return false;
    }
    return true;
}

void BricksManager::reset()
{
    qDeleteAll(m_bricks);
    m_bricks.clear();
}

void BricksManager::onBallHit(int brickWidth, int brickHeight, QWidget *parent)  //kanchvum e amen angam erb gndaky kpnum e bricki
{
    int cols = QRandomGenerator::global()->bounded(4, 8); // 4–7 brick ,, RAndom voroshum e te verevi toxum qani hat brick avelana
    for (int j = 0; j < cols; j++) {
        int hp = QRandomGenerator::global()->bounded(1, 50);  //random health amen bricki hamar

        bool makeBonus = (QRandomGenerator::global()->bounded(100) < 20);  //random voroshum e bonus lini te voch

        Brick *brick = nullptr;
        if (makeBonus) {
            auto type = static_cast<BonusBrick::BonusType>(
                QRandomGenerator::global()->bounded(1, 7));
            auto *bbrick = new BonusBrick(hp, type, parent);
            connect(bbrick, &BonusBrick::bonusDropped, this, &BricksManager::bonusDropped);
            brick = bbrick;
        } else {
            brick = new Brick(hp, parent);
        }

        brick->setGeometry(j * (brickWidth + 5), 0, brickWidth, brickHeight);  //nor brick texdrum e y = 0, ev nshvac x koordinatum hamapatasxan colunum
        brick->show();
        m_bricks.append(brick);
    }

    for (Brick *b : m_bricks) {  // yuraqanchyur brick ijacnum e mi levelov , qandvac brickery chen sharjvum
        if (!b->isDestroyed()) {
            QRect geom = b->geometry();
            b->setGeometry(geom.x(), geom.y() + (brickHeight + 5),
                           geom.width(), geom.height());
        }
    }

}

bool BricksManager::checkGameOver(int windowHeight)  //stugum e ardyoq hasel e bricky verjin
{
    for (Brick *b : m_bricks) {  //ancnum e bollor brickeri vrayov
        if (!b->isDestroyed() && b->geometry().bottom() >= windowHeight) {  //stugume bricky destroy exac che(healthy>0)    stgum e bricki nerqin sahmaany -y
            //ete y >= patuhani bardzrutyunic , nshanakum e bricky hasel e field ev uxarkum e gameover signaly
            emit gameOver();
            return true;
        }
    }
    return false;
}
