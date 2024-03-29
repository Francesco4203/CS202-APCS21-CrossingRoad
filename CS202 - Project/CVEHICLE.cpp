﻿#include "CVEHICLE.h"
using namespace std;
using namespace sf;
CVEHICLE::CVEHICLE(double x, double y, int mode, int randomFactor) {
    speed = (mode == 1 ? 7 : (mode == 2 ? 10 : 13));
    isStop = 1;
    int shift = mode != 3 ? 900 + randomFactor : 400 + randomFactor;
    object.setPosition(x < 0 ? x + shift : x - shift, y);
    object.scale(0.3, 0.3);
}

CTRUCK::CTRUCK(int direction, double x, double y, int mode, int randomFactor) : CVEHICLE(x, y, mode, randomFactor) {
    !_Bsound.loadFromFile("Resource/Sound/truck.wav");
    _sound.setBuffer(_Bsound);
    if (direction == 2) enemy.loadFromFile("Resource/Rtruck.png");
    else enemy.loadFromFile("Resource/truck.png");
    _currentImage.width = enemy.getSize().x / 4;
    _currentImage.height = enemy.getSize().y;
    object.setTexture(enemy);
    object.setTextureRect(_currentImage);
    _scale.x = 0;
    _scale.y = 0;
    _switchTime = 0.1f;
    _totalTime = 0;
    type = 1;
}

CCAR::CCAR(int direction, double x, double y, int mode, int randomFactor) : CVEHICLE(x, y, mode, randomFactor) {
    _Bsound.loadFromFile("Resource/Sound/car.wav");
    _sound.setBuffer(_Bsound);
    if (direction == 2) enemy.loadFromFile("Resource/Rcar.png");
    else enemy.loadFromFile("Resource/car.png");
    _currentImage.width = enemy.getSize().x / 4;
    _currentImage.height = enemy.getSize().y;
    object.setTexture(enemy);
    object.setTextureRect(_currentImage);
    _scale.x = 0;
    _scale.y = 0;
    _switchTime = 0.1f;
    _totalTime = 0;
    type = 0;
}