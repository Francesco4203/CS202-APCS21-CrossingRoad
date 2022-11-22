#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "CANIMAL.h"
#include "CPEOPLE.h"
#include "CVEHICLE.h"
#include "CGAME.h"
#include "CTRAFFIC.h"
using namespace std;
using namespace sf;

//Constructor set image for object

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
};