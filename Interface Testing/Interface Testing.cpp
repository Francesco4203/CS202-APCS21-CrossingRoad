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

class CVEHICLE {
protected:
    int speed;//step per second, or seconds needed for 1 step
    bool isStop;
    Sprite object;
    Texture vehicle;
public:
    CVEHICLE() = delete;//default NOT available
    CVEHICLE(int x, int y, int mode);
    virtual void Move(bool reverse) = 0;
    void stop();//stop when red light
    void resume();//move again when green light
    Sprite getObject();
};

//Constructor set image for object

class CTRUCK : public CVEHICLE {
    // image
public:
    CTRUCK() = delete;//default NOT available
    CTRUCK(int x, int y, int mode);//1 2 3 -> easy medium hard
    void Move(bool reverse);//if reverse, move right to left
};
class CCAR : public CVEHICLE {
    // image
public:
    CCAR() = delete;//default NOT available
    CCAR(int x, int y, int mode);//1 2 3 -> easy medium hard
    void Move(bool reverse);//if reverse, move right to left
};


void CVEHICLE::stop() {
    isStop = true;
}
void CVEHICLE::resume() {
    isStop = false;
}
Sprite CVEHICLE::getObject() {
    return object;
}
CVEHICLE::CVEHICLE(int x, int y, int mode) {
    speed = (mode == 1 ? 5 : (mode == 2 ? 7 : 10));
    isStop = 1;
    object.setPosition(x, y);
    object.scale(0.3, 0.3);
}
CTRUCK::CTRUCK(int x, int y, int mode) : CVEHICLE(x, y, mode) {
    vehicle.loadFromFile("Resource/truck.png");
    object.setTexture(vehicle);
}
void CTRUCK::Move(bool reverse) {
    if (isStop) return;
    srand(time(NULL));
    object.move((reverse ? -1 : 1) * (speed + 3) / 50.0, 0);
    if (object.getPosition().x >= 1500) {
        object.setPosition(-350, object.getPosition().y);
    }
}
CCAR::CCAR(int x, int y, int mode) : CVEHICLE(x, y, mode) {
    vehicle.loadFromFile("Resource/car.png");
    object.setTexture(vehicle);
}
void CCAR::Move(bool reverse) {
    if (isStop) return;
    srand(time(NULL));
    object.move((reverse ? -1 : 1) * (speed + 5 + 3) / 50.0, 0);
    if (object.getPosition().x >= 1500) {
        object.setPosition(-350, object.getPosition().y);
    }
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
    vector <CVEHICLE*> list;
    string linePath = "Resource/line.png";
    LIGHT light;
    int direction;//1 left --> right; 2 left <-- right
    Texture Tline;
    Sprite line;

public:
    LINE() = delete;//default NOT available
    LINE(int y, int dirction, int mode);// 1 2 3 - easy medium hard

    LIGHT& getLight();
    Sprite getSpriteLine();
    void stop();
    void draw(sf::RenderWindow& window);
};

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
        int num = mode + 3;
        CVEHICLE* car = NULL;
        while (num > 0) {
            car = new CCAR(num*(-250), y, mode);
            list.push_back(car);
            num--;
        }
     
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

int main()
{
    RenderWindow window(VideoMode(1500, 800), "Crossing Road Game!");
    LINE line(50, 1, 3);
    clock_t start, end;
    start = clock();
    end = clock();
    while (window.isOpen()) {
        end = clock();

        window.clear();
        
        if ((end - start) / CLOCKS_PER_SEC >= line.getLight().getTime()) {
            line.getLight().changeLight();
            start = clock();
        }

        line.draw(window);

        window.display();
    }

    return 0;
}