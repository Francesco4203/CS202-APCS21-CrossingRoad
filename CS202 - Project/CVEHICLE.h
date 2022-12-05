#pragma once
#include "INCLUDING.h"

using namespace std;
using namespace sf;

class CVEHICLE : public CENEMY {
public:
    CVEHICLE() = delete;//default NOT available
    CVEHICLE(int x, int y, int mode, int randomFactor);
};

//Constructor set image for object

class CTRUCK : public CVEHICLE {
    // image
public:
    CTRUCK() = delete;//default NOT available
    CTRUCK(int x, int y, int mode, int randomFactor);//1 2 3 -> easy medium hard
};
class CCAR : public CVEHICLE {
    // image
public:
    CCAR() = delete;//default NOT available
    CCAR(int x, int y, int mode, int randomFactor);//1 2 3 -> easy medium hard
};