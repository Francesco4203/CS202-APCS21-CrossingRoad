#include "INCLUDING.h"

using namespace std;
using namespace sf;

CANIMAL::CANIMAL(int x, int y, int mode) {
    speed = (mode == 1 ? 7 : (mode == 2 ? 10 : 13));
    isStop = 1;
    object.setPosition(x, y);
    object.scale(0.3, 0.3);
}
CDINAUSOR::CDINAUSOR(int x, int y, int mode) : CANIMAL(x, y, mode) {
    if (x > 0) enemy.loadFromFile("Resource/Rdinausor.png");
    else enemy.loadFromFile("Resource/dinausor.png");
    object.setTexture(enemy);
}

CBIRD::CBIRD(int x, int y, int mode) : CANIMAL(x, y, mode) {
    if (x > 0) enemy.loadFromFile("Resource/Rbird.png");
    else enemy.loadFromFile("Resource/bird.png");
    object.setTexture(enemy);
}