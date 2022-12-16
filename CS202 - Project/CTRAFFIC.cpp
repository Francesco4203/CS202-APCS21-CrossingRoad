#include "CTRAFFIC.h"
const int WIDTH = 1500;
const int HEIGHT = 900;
using namespace std;
using namespace sf;

int LIGHT::getMode() {
    return mode;
}
void LINE::setEnemy(vector<CENEMY*> enemyList) {
    for (int i = 0; i < list.size(); i++) delete list[i];
    list = enemyList;
}
int LINE::getMode() {
    return light.getMode();
}
void LINE::output(ofstream& f) {
    f << direction << ' ' << isLane << ' ' << list.size() << ' ' << getMode() << '\n';
    for (int i = 0; i < list.size(); i++) list[i]->output(f);
}
LINE::~LINE() {
    for (int i = 0; i < list.size(); i++) delete list[i];
}
LIGHT::LIGHT(int mode) {
    red_light.loadFromFile(redPath);
    yellow_light.loadFromFile(yellowPath);
    green_light.loadFromFile(greenPath);
    light.setTexture(green_light);
    light.scale(0.3, 0.3);
    time = 2 * (4 - mode);
    this->mode = mode;
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
        time = 2 * (4 - mode) + rand() % 5;
        return;
    }
    if (state == 2) {
        state = 1;
        light.setTexture(red_light);
        time = 2 * (4 - mode) + rand() % 3;
        return;
    }
    time = 2 * (4 - mode);
    state = 2;
    light.setTexture(yellow_light);
}

void LIGHT::setPosition(double x, double y) {
    light.setPosition(x, y);
}

LINE::LINE(int y, int direction, bool isLane, int mode) : light(mode) {
    if (isLane) Tline.loadFromFile(lanePath);
    else Tline.loadFromFile(grassPath);
    this->isLane = isLane;
    line.setTexture(Tline);
    line.setPosition(0, y);
    this->direction = direction;
    int randomFactor = rand() % 200;
    if (direction == 1) {
        list.clear();
        int num = mode + 4;
        if (isLane) {
            CENEMY* enemy = NULL;
            while (num > 0) {
                int type = rand() % 2;
                if (type) enemy = new CCAR(direction, num * (-250), y, mode, randomFactor);
                else enemy = new CTRUCK(direction, num * (-250), y, mode, randomFactor);
                list.push_back(enemy);
                num--;
            }
        }
        else {
            CENEMY* enemy = NULL;
            while (num > 0) {
                int type = rand() % 2;
                if (type) enemy = new CBIRD(direction, num * (-250), y, mode, randomFactor);
                else enemy = new CDINAUSOR(direction, num * (-250), y, mode, randomFactor);
                list.push_back(enemy);
                num--;
            }
        }

        light.setPosition(WIDTH - 120, y - 30);
    }
    else {
        list.clear();
        int num = mode + 4;
        if (isLane) {
            CENEMY* enemy = NULL;
            while (num > 0) {
                int type = rand() % 2;
                if (type) enemy = new CCAR(direction, 1500 + num * 250, y, mode, randomFactor);
                else enemy = new CTRUCK(direction, 1500 + num * 250, y, mode, randomFactor);
                list.push_back(enemy);
                num--;
            }
        }
        else {
            CENEMY* enemy = NULL;
            while (num > 0) {
                int type = rand() % 2;
                if (type) enemy = new CBIRD(direction, 1500 + num * 250, y, mode, randomFactor);
                else enemy = new CDINAUSOR(direction, 1500 + num * 250, y, mode, randomFactor);
                list.push_back(enemy);
                num--;
            }
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

void LINE::draw(sf::RenderWindow& window, pair<clock_t, clock_t>& time, float deltaTime) {
    time.second = clock();
    if ((time.second - time.first) / CLOCKS_PER_SEC >= light.getTime()) {
        light.changeLight();
        time.first = clock();
    }
    window.draw(line);

    for (auto p : list) {
        p->resume();
        if (this->getLight().getState() == 1 && isLane) p->stop();
        p->Move(direction == 2, deltaTime);
        window.draw(p->getObject());
    }

    if (isLane) window.draw(this->getLight().getSpriteLight());
}