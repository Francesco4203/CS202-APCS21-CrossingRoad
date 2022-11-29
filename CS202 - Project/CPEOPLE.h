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
#include "CENEMY.h"
using namespace std;
using namespace sf;
class CPEOPLE {
	Texture image;
	Sprite people;
	float speed = 20;
	bool mState; //live - die
public:
	CPEOPLE(int t);
	void move(Event&ev,sf::RenderWindow& window);
	bool isImpact(LINE* a);
	//bool isImpactA(const CANIMAL*&);
	bool isFinish();
	bool isDead();
	void draw(sf::RenderWindow& window);
};