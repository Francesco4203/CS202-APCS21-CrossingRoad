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
protected:
	int speed;//step per second, or seconds needed for 1 step
	bool isStop;
	Sprite object;
	Texture vehicle;
public:
	CVEHICLE() = delete;//default NOT available
	CVEHICLE(int x, int y, int mode);
	virtual void Move() = 0;
	void stop();//stop when red light
	void resume();//move again when green light
	Sprite getObject();
};

//Constructor set image for object

class CTRUCK : public CVEHICLE { 
	// image
public:
	CTRUCK() = delete;//default NOT available
	CTRUCK(int x, int y, int mode);//1 2 3 -> easy medium hard
	void Move();
	~CTRUCK();//1 2 3 -> easy medium hard
};
class CCAR : public CVEHICLE {
	// image
public:
	CCAR() = delete;//default NOT available
	CCAR(int x, int y, int mode);//1 2 3 -> easy medium hard
	void Move();
	~CCAR();
};
