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

LINE::LINE(int y, int direction, bool isLane, int mode) : light(mode) {
    if (isLane) Tline.loadFromFile(lanePath);
    else Tline.loadFromFile(grassPath);

    line.setTexture(Tline);
    line.scale(3, 0.4);
    line.setPosition(0, y);
    this->direction = direction;
    if (direction == 1) {
        list.clear();
        int num = mode + 3;
        CVEHICLE* car = NULL;
        while (num > 0) {
            int type = rand() % 2;
            if (type) car = new CCAR(num * (-250), y, mode);
            else car = new CTRUCK(num * (-250), y, mode);
            list.push_back(car);
            num--;
        }

        light.setPosition(WIDTH - 120, y - 30);
    }
    else {
        list.clear();
        int num = mode + 3;
        CVEHICLE* car = NULL;
        while (num > 0) {
            int type = rand() % 2;
            if (type) car = new CCAR(1500 + num * 250, y, mode);
            else car = new CTRUCK(1500 + num * 250, y, mode);
            list.push_back(car);
            num--;
        }
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

void LINE::draw(sf::RenderWindow& window) {

    window.draw(line);

    for (auto p : list) {
        p->resume();
        if (this->getLight().getState() == 1) p->stop();
        p->Move(direction == 2);
        window.draw(p->getObject());
    }

    window.draw(this->getLight().getSpriteLight());
}