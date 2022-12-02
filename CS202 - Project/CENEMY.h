#pragma once
#include "INCLUDING.h"

using namespace std;
using namespace sf;

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