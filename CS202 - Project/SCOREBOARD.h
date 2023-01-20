#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;
using namespace sf;
class SCOREBOARD {
	Texture texture;
	Sprite object;
	vector<pair<int, string>> topscore;
	Font font;
	vector<Text> playerName, playTime;
public:
	SCOREBOARD();
	void add(int time, string name);
	void show(RenderWindow* app);
	void load();
	void save();
};