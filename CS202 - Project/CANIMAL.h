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
protected:
	int speed;//step per second, or seconds needed for 1 step
	bool isStop;
	Sprite object;
	Texture animal;
public:
	virtual void Tell();//sound during game? dunno
	CANIMAL() = delete;//default NOT available
	CANIMAL(int x, int y, int mode);
	virtual void Move(bool reverse) = 0;
	void stop();//stop when red light
	void resume();//move again when green light
	Sprite getObject();
};

//Constructor set image for object

class CDINAUSOR : public CANIMAL {
	// image
public:
	CDINAUSOR() = delete;//default NOT available
	CDINAUSOR(int x, int y, int mode);// 1 2 3 -> easy medium hard
	void Move(bool reverse);//if reverse, move right to left
};
class CBIRD : public CANIMAL {
	//image
public:
	CBIRD() = delete;//default NOT available
	CBIRD(int x, int y, int mode);//1 2 3 -> easy medium hard;
	void Move(bool reverse);//if reverse, move right to left
};