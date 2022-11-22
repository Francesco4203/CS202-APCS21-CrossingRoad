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

class LINE {
private:
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
};

LINE::LINE(int y, int direction, int mode) : light(mode) {
    Tline.loadFromFile(linePath);
    line.setTexture(Tline);
    line.scale(3, 0.4);
    line.setPosition(0, y);
    this->direction = direction;
    if (direction == 1) {
        light.setPosition(WIDTH-120, y-30);
    }
    else {
        light.setPosition(-50, y-30);
    }
}

LIGHT& LINE::getLight() { return light; }
Sprite LINE::getSpriteLine() { return line; }

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Crossing Road Game!");

    LINE line(50, 2, 1);
    clock_t start, end;
    start = clock();
    end = clock();
    while (window.isOpen())
    {
        window.clear();
        window.draw(line.getSpriteLine());
        window.draw(line.getLight().getSpriteLight());
        
        end = clock();
        if ((end - start) / CLOCKS_PER_SEC >= line.getLight().getTime()) {
            line.getLight().changeLight();
            start = clock();
        }


        window.display();
    }

    return 0;
}