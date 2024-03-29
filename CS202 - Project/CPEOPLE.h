﻿#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include <ctime>
#include <chrono>
#include <thread>
#include "CTRAFFIC.h"
#include "Collision.h"

using namespace std;
using namespace sf;

class CPEOPLE {
    Vector2u _scale;
    IntRect _currentImage;
    Texture _Tplayer;
    Sprite _player;
    float _switchTime;
    float _totalTime;
    float _speed = 30;
    int _direction;
    bool isDie;
    bool isMan;

    friend class CGAME;
public:
    CPEOPLE(float switchTime, float speed);
    void move(float deltaTime);
    void update(int direction, float deltaTime);
    CENEMY* isImpact(LINE* a);
    bool isFinish(Sprite& finishLine);
    void draw(sf::RenderWindow& window);
    void setPosition(double x, double y);
    void output(ofstream& f);
    void setPeople(float switchTime, float speed, int t);
    Sprite& getSprite();
    bool getIsMan();
};
