#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>
#include "CPEOPLE.h"
#include "CGAME.h"
#include "BUTTON.h"

using namespace std;
using namespace sf;
#define max_menu 5
#define diff_menu 5
class Menu
{
public:
	Menu(float w, float h, CGAME* game);
	void draw(sf::RenderWindow& window, CPEOPLE a);
	void moveUp();
	void moveDown();
	int MenuSettingChara(sf::RenderWindow& window);
	int MenuSetting(sf::RenderWindow& window, CPEOPLE a);
	int MenuSetting2(sf::RenderWindow& window, CPEOPLE a);
	int selectedMenu();
	void changeMenu(int i);
	void OutputText(sf::RenderWindow& window, string s, int corX, int corY, sf::Color a, int scale);
	void MenuMouseDetect(sf::RenderWindow& window);
	int textsize;
	~Menu();
private:
	int mainMenuSelected;
	int menuNumber;
	sf::Font font;
	Button mainMenu[max_menu];
	sf::Text difficultyMenu[diff_menu];
	Texture Tvolume;
	Sprite volume;
	IntRect _currentImage;
	Vector2u _scale;
	CGAME* _game;
	Texture TAWSD, TW, TA, TS, TD, TL, PL, TSG, TAW, TWD, TAS, TSD, TZX, TPZ, TPX, TC, TPC, TSetting_2;
	Sprite AWSD, W, A, S, D, L, L2, SG, AW, WD, AS, SD, XZ, PZ, PX, C, PC, Setting_2;

	friend class CGAME;
};

class MenuSprite
{
private:
	sf::Texture menubgT;
	sf::Sprite menubgS;
	sf::Texture menubgBlankT;
	sf::Sprite menubgBlankS;

public:
	MenuSprite();
	void drawBG(sf::RenderWindow& window);
	void drawBGBlank(sf::RenderWindow& window);
	~MenuSprite();
};

