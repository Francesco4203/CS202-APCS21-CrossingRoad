#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
//#include "CANIMAL.h"
//#include "CPEOPLE.h"
//#include "CVEHICLE.h"
//#include "CGAME.h"

#include <ctime>

using namespace std;
using namespace sf;

const int WIDTH = 1500;
const int HEIGHT = 800;

class CENEMY
{
protected:
    int speed;//step per second, or seconds needed for 1 step
    bool isStop;
    Sprite object;
    Texture enemy;
public:
    void Move(bool reverse);
    void stop();
    void resume();
    Sprite getObject();
};

void CENEMY::stop() {
    isStop = true;
}
void CENEMY::resume() {
    isStop = false;
}
Sprite CENEMY::getObject() {
    return object;
}

void CENEMY::Move(bool reverse) {
    if (isStop) return;
    object.move((reverse ? -1 : 1) * (speed + 3) / 50.0, 0);
    if (object.getPosition().x >= 1500 && !reverse) {
        object.setPosition(-350, object.getPosition().y);
    }
    if (object.getPosition().x <= -200 && reverse) {
        object.setPosition(1500 + 350, object.getPosition().y);
    }
}

class CANIMAL : public CENEMY {

public:
    CANIMAL() = delete;//default NOT available
    CANIMAL(int x, int y, int mode);
};

//Constructor set image for object

class CDINAUSOR : public CANIMAL {
    // image
public:
    CDINAUSOR() = delete;//default NOT available
    CDINAUSOR(int x, int y, int mode);// 1 2 3 -> easy medium hard
};
class CBIRD : public CANIMAL {
    //image
public:
    CBIRD() = delete;//default NOT available
    CBIRD(int x, int y, int mode);//1 2 3 -> easy medium hard;
};

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

class CVEHICLE : public CENEMY {
public:
    CVEHICLE() = delete;//default NOT available
    CVEHICLE(int x, int y, int mode);
};

//Constructor set image for object

class CTRUCK : public CVEHICLE {
    // image
public:
    CTRUCK() = delete;//default NOT available
    CTRUCK(int x, int y, int mode);//1 2 3 -> easy medium hard
};
class CCAR : public CVEHICLE {
    // image
public:
    CCAR() = delete;//default NOT available
    CCAR(int x, int y, int mode);//1 2 3 -> easy medium hard
};

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

class LIGHT {
private:
    string redPath = "Resource/red_light.png";
    string yellowPath = "Resource/yellow_light.png";
    string greenPath = "Resource/green_light.png";
    int time;
    int state;//1 red - 2 yellow - 3 green
    int red, yellow, green;//time of a state, 2-3s for yellow
    Texture red_light;
    Texture green_light;
    Texture yellow_light;
    Sprite light;
public:
    LIGHT() = delete;//default NOT available
    LIGHT(int mode);// 1 2 3 - easy medium hard

    int getTime();
    int getState();
    Sprite getSpriteLight();
    void changeLight();
    void setPosition(int x, int y);
};

class LINE {
private:
    vector <CENEMY*> list;
    string lanePath = "Resource/lane.png";
    string grassPath = "Resource/grass.png";
    LIGHT light;
    int direction;//1 left --> right; 2 left <-- right
    Texture Tline;
    Sprite line;

public:
    LINE() = delete;//default NOT available
    LINE(int y, int dirction, bool isLane, int mode);// 1 2 3 - easy medium hard

    LIGHT& getLight();
    Sprite getSpriteLine();
    void stop();
    void draw(sf::RenderWindow& window, pair<clock_t, clock_t>& time);
};

LIGHT::LIGHT(int mode) {
    red_light.loadFromFile(redPath);
    yellow_light.loadFromFile(yellowPath);
    green_light.loadFromFile(greenPath);
    light.setTexture(green_light);
    light.scale(0.3, 0.3);
    time = 2 * (4 - mode);
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
    line.setPosition(0, y);
    this->direction = direction;
    if (direction == 1) {
        list.clear();
        int num = mode + 3;
        if (isLane) {
            CVEHICLE* vehicle = NULL;
            while (num > 0) {
                int type = rand() % 2;
                if (type) vehicle = new CCAR(num * (-250), y, mode);
                else vehicle = new CTRUCK(num * (-250), y, mode);
                list.push_back(vehicle);
                num--;
            }
        }
        else {
            CANIMAL* animal = NULL;
            while (num > 0) {
                int type = rand() % 2;
                if (type) animal = new CBIRD(num * (-250), y, mode);
                else animal = new CDINAUSOR(num * (-250), y, mode);
                list.push_back(animal);
                num--;
            }
        }

        light.setPosition(WIDTH - 120, y - 30);
    }
    else {
        list.clear();
        int num = mode + 3;
        if (isLane) {
            CVEHICLE* vehicle = NULL;
            while (num > 0) {
                int type = rand() % 2;
                if (type) vehicle = new CCAR(1500 + num * 250, y, mode);
                else vehicle = new CTRUCK(1500 + num * 250, y, mode);
                list.push_back(vehicle);
                num--;
            }
        }
        else {
            CENEMY* enemy = NULL;
            while (num > 0) {
                int type = rand() % 2;
                if (type) enemy = new CBIRD(1500 + num * 250, y, mode);
                else enemy = new CDINAUSOR(1500 + num * 250, y, mode);
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

void LINE::draw(sf::RenderWindow& window, pair<clock_t, clock_t>& time) {
    time.second = clock();
    if ((time.second - time.first) / CLOCKS_PER_SEC >= light.getTime()) {
        light.changeLight();
        time.first = clock();
    }
    window.draw(line);

    for (auto p : list) {
        p->resume();
        if (this->getLight().getState() == 1) p->stop();
        p->Move(direction == 2);
        window.draw(p->getObject());
    }

    window.draw(this->getLight().getSpriteLight());
}

int main()
{
    srand(time(NULL));
    RenderWindow window(VideoMode(1500, 800), "Crossing Road Game!");
    LINE line(50, 1, 1, 1), line2(225, 2, 0, 2), line3(400, 1, 1, 3), line4(575, 2, 0, 2);
    pair<clock_t, clock_t> time[4];
    for (int i = 0; i < 4; ++i) {
        time[i].first = clock();
        time[i].second = clock();
    }
    while (window.isOpen()) {
        window.clear();
        
        line.draw(window, time[0]);
        line2.draw(window, time[1]);
        line3.draw(window, time[2]);
        line4.draw(window, time[3]);

        window.display();
    }

    return 0;
}