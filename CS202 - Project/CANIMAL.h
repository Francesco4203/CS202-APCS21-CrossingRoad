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
class CANIMAL {
	int mX, mY;
	int speed;//step per second, or seconds needed for 1 step
public:
	virtual void Move(int, int);
	virtual void Tell();//sound during game? dunno
	CANIMAL() = delete;//default NOT available
	CANIMAL(int mode);
	~CANIMAL();
	virtual void Move(int, int);
	virtual void stop();//stop when red light
	virtual void resume();//move again when green light
};

//Constructor set image for object

class CDINAUSOR : public CANIMAL {
	// image
public:
	CDINAUSOR() = delete;//default NOT available
	CDINAUSOR(int mode);// 1 2 3 -> easy medium hard
};
class CBIRD : public CANIMAL {
	//image
public:
	CBIRD() = delete;//default NOT available
	CBIRD(int mode);//1 2 3 -> easy medium hard;
};