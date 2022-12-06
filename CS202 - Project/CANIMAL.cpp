#include "INCLUDING.h"

using namespace std;
using namespace sf;

CANIMAL::CANIMAL(double x, double y, int mode, int randomFactor) {
    speed = (mode == 1 ? 7 : (mode == 2 ? 10 : 13));
    isStop = 1;
    int shift = mode != 3 ? 900 + randomFactor : 400 + randomFactor;
    object.setPosition(x < 0 ? x + shift : x - shift, y);
    object.scale(0.3, 0.3);
}
CDINAUSOR::CDINAUSOR(int direction, double x, double y, int mode, int randomFactor) : CANIMAL(x, y, mode, randomFactor) {
    if (direction == 2) enemy.loadFromFile("Resource/Rdinausor.png");
    else enemy.loadFromFile("Resource/dinausor.png");
    object.setTexture(enemy);
    type = 3;
}

CBIRD::CBIRD(int direction, double x, double y, int mode, int randomFactor) : CANIMAL(x, y, mode, randomFactor) {
    if (direction == 2) enemy.loadFromFile("Resource/Rbird.png");
    else enemy.loadFromFile("Resource/bird.png");
    object.setTexture(enemy);
    type = 2;
}