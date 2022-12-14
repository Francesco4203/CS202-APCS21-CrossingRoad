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
using namespace std;
using namespace sf;

class CANIMAL : public CENEMY   {

public:
    CANIMAL() = delete;//default NOT available
    CANIMAL(double x, double y, int mode, int randomFactor);
};

//Constructor set image for object

class CDINAUSOR : public CANIMAL {
    // image
public:
    CDINAUSOR() = delete;//default NOT available
    CDINAUSOR(int direction, double x, double y, int mode, int randomFactor);// 1 2 3 -> easy medium hard

    ~CDINAUSOR() {}
};
class CBIRD : public CANIMAL {
    //image
public:
    CBIRD() = delete;//default NOT available
    CBIRD(int direction, double x, double y, int mode, int randomFactor);//1 2 3 -> easy medium hard;

    ~CBIRD() {}
};