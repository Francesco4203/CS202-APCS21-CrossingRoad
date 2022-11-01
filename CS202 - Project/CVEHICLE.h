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
class CVEHICLE {
	int mX, mY;
public:
	virtual void Move(int, int);
	//...
};
class CTRUCK : public CVEHICLE {
public:
	//...
};
class CCAR : public CVEHICLE {
public:
	//...
};