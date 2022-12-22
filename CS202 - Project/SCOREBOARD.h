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
	vector<pair<int, string>> topscore;
	Font font;
	vector<Text> playerName, playTime;
public:
	SCOREBOARD() {
		texture.loadFromFile("resource/menuscoreboard.png");
		object.setTexture(texture);
		object.setPosition(0, 0);
		playerName = playTime = vector<Text>(6);
		font.loadFromFile("font/000OneTwoPunchBB-Regular.otf");
		topscore.clear();
		for (int i = 0; i < 6; i++) {
			playerName[i].setFont(font);
			playerName[i].setFillColor(Color::Yellow);
			playTime[i].setFont(font);
			playTime[i].setFillColor(Color::Yellow);
			playerName[i].setPosition(600, 290 + 100 * i);
			playTime[i].setPosition(1050, 290 + 100 * i);
		}
	}
	void add(int time, string name) {
		topscore.push_back({ time, name });
		sort(topscore.begin(), topscore.end());
		while (topscore.size() > 6) topscore.pop_back();
		for (int i = 0; i < topscore.size(); i++) {
			playerName[i].setString(topscore[i].second);
			playTime[i].setString(to_string(topscore[i].first) + "s");
		}
	}
	void show(RenderWindow& window) {
		while (window.isOpen()) {
			bool close = false;
			Event event;
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
				}
				if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
					close = true;
				}
			}
			window.clear();
			window.draw(object);
			for (int i = 0; i < playerName.size(); i++) {
				window.draw(playerName[i]);
				window.draw(playTime[i]);
			}
			window.display();
			if (close) {
				break;
			}
		}
	}
	void load() {
		ifstream f("scoreboard.txt");
		int n;
		f >> n;
		for (int i = 0; i < n; i++) {
			int time;
			string name;
			f >> time >> name;
			add(time, name);
		}
		f.close();
	}
	void save() {
		ofstream f("scoreboard.txt");
		f << topscore.size() << '\n';
		for (auto c : topscore) {
			f << c.first << ' ' << c.second << '\n';
		}
		f.close();
	}
};