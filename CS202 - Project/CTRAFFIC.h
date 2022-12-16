#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include <ctime>
#include <chrono>
#include <thread>
#include "CENEMY.h"
#include "CANIMAL.h"
#include "CVEHICLE.h"
using namespace std;
using namespace sf;
class LIGHT {
private:
    string redPath = "Resource/red_light.png";
    string yellowPath = "Resource/yellow_light.png";
    string greenPath = "Resource/green_light.png";
    int time;
    int state;//1 red - 2 yellow - 3 green
    int red, yellow, green;//time of a state, 2-3s for yellow
    int mode;
    Texture red_light;
    Texture green_light;
    Texture yellow_light;
    Sprite light;
    friend class CGAME;
public:
    LIGHT() = delete;//default NOT available
    LIGHT(int mode);// 1 2 3 - easy medium hard

    int getTime();
    int getState();
    Sprite getSpriteLight();
    void changeLight();
    void setPosition(double x, double y);
    int getMode();
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
    bool isLane;
public:
    LINE() = delete;//default NOT available
    LINE(int y, int dirction, bool isLane, int mode);// 1 2 3 - easy medium hard
    vector<CENEMY*> getVectorList() { return this->list; };
    LIGHT& getLight();
    Sprite getSpriteLine();
    void stop();
    void draw(sf::RenderWindow& window, pair<clock_t, clock_t>& time, float deltaTime);
    void output(ofstream& f);
    int getMode();
    void setEnemy(vector<CENEMY*> enemyList);
    ~LINE();
};