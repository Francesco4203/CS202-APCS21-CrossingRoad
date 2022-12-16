#pragma once
#include "CENEMY.h"
using namespace std;
using namespace sf;

void CENEMY::sound() {
    _sound.play();
}

int CENEMY::getSpeed() {
    return speed;
}
void CENEMY::setSpeed(int speed) {
    this->speed = speed;
}

void CENEMY::setPosition(double x, double y) {
    object.setPosition(x, y);
}
void CENEMY::output(ofstream& f) {
    f << type << ' ' << speed << ' ' << isStop << ' ' << object.getPosition().x << ' ' << object.getPosition().y << '\n';
}
void CENEMY::stop() {
    isStop = true;
}
void CENEMY::resume() {
    isStop = false;
}
Sprite CENEMY::getObject() {
    return object;
}

void CENEMY::Move(bool reverse, float deltaTime) {
    if (isStop) return;

    _totalTime += deltaTime;
    if (_totalTime >= _switchTime) {
        _totalTime = 0;
        if (!reverse) {
            ++_scale.x;
            if (_scale.x == 4) {
                _scale.x = 0;
            }
        }
        else {
            --_scale.x;
            if (_scale.x == -1) {
                _scale.x = 3;
            }
        }
    }
    _currentImage.left = _scale.x * _currentImage.width;
    _currentImage.top = _scale.y * _currentImage.height;
    object.setTextureRect(_currentImage);

    object.move((reverse ? -1 : 1) * (speed + 3) / 50.0, 0);
    if (object.getPosition().x >= 1500 && !reverse) {
        object.setPosition(-350, object.getPosition().y);
    }
    if (object.getPosition().x <= -200 && reverse) {
        object.setPosition(1500 + 350, object.getPosition().y);
    }
}