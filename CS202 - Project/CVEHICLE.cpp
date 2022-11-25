#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "CANIMAL.h"
#include "CPEOPLE.h"
#include "CVEHICLE.h"
#include "CGAME.h"
#include "CTRAFFIC.h"
#include "CENEMY.h"
using namespace std;
using namespace sf;


CVEHICLE::CVEHICLE(int x, int y, int mode) {
    speed = (mode == 1 ? 7 : (mode == 2 ? 10 : 13));
    isStop = 1;
    object.setPosition(x, y);
    object.scale(0.3, 0.3);
}
CTRUCK::CTRUCK(int x, int y, int mode) : CVEHICLE(x, y, mode) {
    if (x > 0) enemy.loadFromFile("Resource/Rtruck.png");
    else enemy.loadFromFile("Resource/truck.png");
    object.setTexture(enemy);
}

CCAR::CCAR(int x, int y, int mode) : CVEHICLE(x, y, mode) {
    if (x > 0) enemy.loadFromFile("Resource/Rcar.png");
    else enemy.loadFromFile("Resource/car.png");
    object.setTexture(enemy);
}