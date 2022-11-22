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
	int speed;//step per second, or seconds needed for 1 step
	Sprite object;
public:
	CVEHICLE() = delete;//default NOT available
	CVEHICLE(int mode);
	virtual void Move();
	virtual void stop();//stop when red light
	virtual void resume();//move again when green light
};

//Constructor set image for object

class CTRUCK : public CVEHICLE { 
	// image
public:
	CTRUCK() = delete;//default NOT available
	CTRUCK(int mode);//1 2 3 -> easy medium hard
	~CTRUCK();//1 2 3 -> easy medium hard
};
class CCAR : public CVEHICLE {
	// image
public:
	CCAR() = delete;//default NOT available
	CCAR(int mode);//1 2 3 -> easy medium hard
	~CCAR();
};
