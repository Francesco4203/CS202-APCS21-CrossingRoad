#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include <ctime>
#include <chrono>
#include <thread>
#include "MENU.h"
#include "CANIMAL.h"
#include "CPEOPLE.h"
#include "CVEHICLE.h"
#include "CTRAFFIC.h"
#include "CENEMY.h"
using namespace std;
using namespace sf;
class SCOREBOARD {
	Texture texture;
	Sprite object;
	vector<pair<clock_t, string>> top;
	vector<pair<Texture, Sprite>> score;
public:

};