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
class CGAME {
	vector<LINE*> map;
	int mode;
	vector<pair<clock_t, clock_t>> time;
	bool win;
	bool isPlaying;
public:
	CGAME();
	void gameSet();
	void newGame();
	void playGame();
};