#pragma once
#include "INCLUDING.h"
using namespace std;
using namespace sf;
class CGAME {
	vector<LINE*> map;
	int mode;
	vector<pair<clock_t, clock_t>> time;
	bool win;
	bool isPlaying;
	RenderWindow window;
public:
	CGAME();
	void menu();
	void GameOver(sf::RenderWindow& window);
	void gameSet();
	void newGame();
	void playGame();
};