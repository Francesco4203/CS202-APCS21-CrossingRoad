#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;
using namespace sf;
class CENEMY
{
protected:
    float _switchTime;
    float _totalTime;
    Vector2u _scale;
    IntRect _currentImage;
    int type;//0 car, 1 truck, 2 bird, 3 dinausor
    int speed;//step per second, or seconds needed for 1 step
    bool isStop;
    Sprite object;
    Texture enemy;
    SoundBuffer _Bsound;
    Sound _sound;
public:
    void Move(bool reverse, float deltaTime);
    void stop();
    void resume();
    Sprite getObject();
    void output(ofstream& f);
    void setPosition(double x, double y);
    void sound();
    int getSpeed();
    void setSpeed(int speed);

    virtual ~CENEMY() {}
};