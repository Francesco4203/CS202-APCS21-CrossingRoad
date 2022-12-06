#pragma once
#include "INCLUDING.h"

using namespace std;
using namespace sf;

class CENEMY
{
protected:
    int type;//0 car, 1 truck, 2 bird, 3 dinausor
    int speed;//step per second, or seconds needed for 1 step
    bool isStop;
    Sprite object;
    Texture enemy;
public:
    void Move(bool reverse);
    void stop();
    void resume();
    Sprite getObject();
    void output(ofstream& f);
    void setPosition(double x, double y);
};