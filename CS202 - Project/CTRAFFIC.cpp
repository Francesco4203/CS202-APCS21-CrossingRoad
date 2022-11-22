#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "CANIMAL.h"
#include "CPEOPLE.h"
#include "CVEHICLE.h"
#include "CGAME.h"
#include "CTRAFFIC.h"

#include <ctime>

using namespace std;
using namespace sf;

LIGHT::LIGHT(int mode) {
    red_light.loadFromFile(redPath);
    yellow_light.loadFromFile(yellowPath);
    green_light.loadFromFile(greenPath);
    light.setTexture(green_light);
    light.scale(0.3, 0.3);
    time = 3 * (4 - mode);
    state = 3;
}

int LIGHT::getTime() {
    return time;
}
int LIGHT::getState() {
    return state;
}
Sprite LIGHT::getSpriteLight() {
    return light;
}

void LIGHT::changeLight() {
    if (state == 1) {
        state = 3;
        light.setTexture(green_light);
        return;
    }
    if (state == 2) {
        state = 1;
        light.setTexture(red_light);
        return;
    }
    state = 2;
    light.setTexture(yellow_light);
}

void LIGHT::setPosition(int x, int y) {
    light.setPosition(x, y);
}

LINE::LINE(int y, int direction, int mode) : light(mode) {
    Tline.loadFromFile(linePath);
    line.setTexture(Tline);
    line.scale(3, 0.4);
    line.setPosition(0, y);
    this->direction = direction;
    if (direction == 1) {
        list.clear();
        CVEHICLE* car = new CCAR(0, y, mode);
        list.push_back(car);
        light.setPosition(WIDTH - 120, y - 30);
    }
    else {
        light.setPosition(-50, y - 30);
    }
}

LIGHT& LINE::getLight() { return light; }
Sprite LINE::getSpriteLine() { return line; }

void LINE::stop() {
    for (auto p : list) {
        p->stop();
    }
}