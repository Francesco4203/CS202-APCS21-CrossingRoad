#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "CENEMY.h"

using namespace std;
using namespace sf;
class CVEHICLE : public CENEMY {
public:
    CVEHICLE() = delete;//default NOT available
    CVEHICLE(double x, double y, int mode, int randomFactor);
};

//Constructor set image for object

class CTRUCK : public CVEHICLE {
    // image
public:
    CTRUCK() = delete;//default NOT available
    CTRUCK(int direction, double x, double y, int mode, int randomFactor);//1 2 3 -> easy medium hard

    ~CTRUCK() {}
};
class CCAR : public CVEHICLE {
    // image
public:
    CCAR() = delete;//default NOT available
    CCAR(int direction, double x, double y, int mode, int randomFactor);//1 2 3 -> easy medium hard

    ~CCAR() {}
};