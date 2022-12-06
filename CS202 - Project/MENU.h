#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace sf;
#define max_menu 4
#define diff_menu 4
class Menu
{
public:
	Menu(float w, float h);
	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	int selectedMenu();
	void changeMenu(int i);
	~Menu();
private:
	int mainMenuSelected;
	int menuNumber;
	sf::Font font;
	sf::Text mainMenu[max_menu];
	sf::Text difficultyMenu[diff_menu];
	sf::Text setting[1];
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