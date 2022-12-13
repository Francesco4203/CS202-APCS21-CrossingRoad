#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>
#include "CPEOPLE.h"
using namespace std;
using namespace sf;
#define max_menu 4
#define diff_menu 4
class Menu
{
public:
	Menu(float w, float h);
	void draw(sf::RenderWindow& window, CPEOPLE a);
	void moveUp();
	void moveDown();
	void MenuSetting(sf::RenderWindow& window, CPEOPLE a);
	int selectedMenu();
	void changeMenu(int i);
	void OutputText(sf::RenderWindow& window, string s, int corX, int corY, sf::Color a, int scale);
	~Menu();
private:
	int mainMenuSelected;
	int menuNumber;
	sf::Font font;
	sf::Text mainMenu[max_menu];
	sf::Text difficultyMenu[diff_menu];
};

class MenuSprite
{
private:
	sf::Texture menubgT;
	sf::Sprite menubgS;
public:
	MenuSprite();
	void drawBG(sf::RenderWindow& window);
	~MenuSprite();
};

