#include "INCLUDING.h"
using namespace std;
using namespace sf;


CVEHICLE::CVEHICLE(int x, int y, int mode, int randomFactor) {
    speed = (mode == 1 ? 7 : (mode == 2 ? 10 : 13));
    isStop = 1;
    int shift = mode != 3 ? 900 + randomFactor : 400 + randomFactor;
    object.setPosition(x < 0 ? x + shift : x - shift, y);
    object.scale(0.3, 0.3);
}
CTRUCK::CTRUCK(int x, int y, int mode, int randomFactor) : CVEHICLE(x, y, mode, randomFactor) {
    if (x > 0) enemy.loadFromFile("Resource/Rtruck.png");
    else enemy.loadFromFile("Resource/truck.png");
    object.setTexture(enemy);
}

CCAR::CCAR(int x, int y, int mode, int randomFactor) : CVEHICLE(x, y, mode, randomFactor) {
    if (x > 0) enemy.loadFromFile("Resource/Rcar.png");
    else enemy.loadFromFile("Resource/car.png");
    object.setTexture(enemy);
}