#pragma once
#include "MENU.h"
#define max_menu 5
#define diff_menu 5
using namespace std;
using namespace sf;
Menu::Menu(float w, float h)
{
	if (!font.loadFromFile("font/000OneTwoPunchBB-Regular.otf"))
	{
		std::cout << "no font loaded";
	}
	int mmoffset = 500;
	int mmoffset2 = 450;
	int transparency = 120;
	textsize = 40;

	// New game
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::White);
	mainMenu[0].setString("New Game");
	mainMenu[0].setCharacterSize(textsize + 5);
	mainMenu[0].setPosition(sf::Vector2f(w / 2 - 100, (h - mmoffset) / (max_menu + 1) + mmoffset2));
	// Load Game
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color(255, 255, 255, transparency));
	mainMenu[1].setString("Load Game");
	mainMenu[1].setCharacterSize(textsize);
	mainMenu[1].setPosition(sf::Vector2f(w / 2 - 100, (h - mmoffset) / (max_menu + 1) * 2 + mmoffset2));
	// Setting
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color(255, 255, 255, transparency));
	mainMenu[2].setString("Setting");
	mainMenu[2].setCharacterSize(textsize);
	mainMenu[2].setPosition(sf::Vector2f(w / 2 - 100, (h - mmoffset) / (max_menu + 1) * 3 + mmoffset2));
	// Highscore
	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(sf::Color(255, 255, 255, transparency));
	mainMenu[3].setString("High Score");
	mainMenu[3].setCharacterSize(textsize);
	mainMenu[3].setPosition(sf::Vector2f(w / 2 - 100, (h - mmoffset) / (max_menu + 1) * 4 + mmoffset2));
	// Quit
	mainMenu[4].setFont(font);
	mainMenu[4].setFillColor(sf::Color(255, 255, 255, transparency));
	mainMenu[4].setString("Quit");
	mainMenu[4].setCharacterSize(textsize);
	mainMenu[4].setPosition(sf::Vector2f(w / 2 - 100, (h - mmoffset) / (max_menu + 1) * 5 + mmoffset2));

	int dmoffset = 100;

	// Easy
	difficultyMenu[0].setFont(font);
	difficultyMenu[0].setFillColor(sf::Color::White);
	difficultyMenu[0].setString("Easy");
	difficultyMenu[0].setCharacterSize(35);
	difficultyMenu[0].setPosition(sf::Vector2f(w / 2 - 100, (h - 200) / (diff_menu + 1) + dmoffset));
	// Medium
	difficultyMenu[1].setFont(font);
	difficultyMenu[1].setFillColor(sf::Color(255, 255, 255, 64));
	difficultyMenu[1].setString("Medium");
	difficultyMenu[1].setCharacterSize(30);
	difficultyMenu[1].setPosition(sf::Vector2f(w / 2 - 100, (h - 200) / (diff_menu + 1) * 2 + dmoffset));
	// Hard
	difficultyMenu[2].setFont(font);
	difficultyMenu[2].setFillColor(sf::Color(255, 255, 255, 64));
	difficultyMenu[2].setString("Hard");
	difficultyMenu[2].setCharacterSize(30);
	difficultyMenu[2].setPosition(sf::Vector2f(w / 2 - 100, (h - 200) / (diff_menu + 1) * 3 + dmoffset));

	// Return
	difficultyMenu[3].setFont(font);
	difficultyMenu[3].setFillColor(sf::Color(255, 255, 255, 64));
	difficultyMenu[3].setString("Return");
	difficultyMenu[3].setCharacterSize(30);
	difficultyMenu[3].setPosition(sf::Vector2f(w / 2 - 100, (h - 200) / (diff_menu + 1) * 4 + dmoffset));

	mainMenuSelected = 0;
	menuNumber = 0;
};
void Menu::draw(sf::RenderWindow& window, CPEOPLE a)
{
	MenuSprite menusprite;
	switch (menuNumber)
	{
	case 0: //main menu
		menusprite.drawBG(window);
		for (int i = 0; i < max_menu; i++)
		{
			window.draw(mainMenu[i]);
		}
		//cout << "menu1" << endl;
		break;
	case 1: //difficulty menu

		for (int i = 0; i < diff_menu; i++)
		{
			window.draw(difficultyMenu[i]);
		}
		break;
		//cout << "menu2" << endl;

	case 2: //setting
		menusprite.drawBGBlank(window);
		if (MenuSetting(window, a) == 3) {
			menuNumber = 3;
			window.clear();
			draw(window, a);
		}
		break;
	case 3: //game
		menusprite.drawBGBlank(window);
		if (MenuSetting2(window, a) == 2) {
			menuNumber = 2;
			window.clear();
			draw(window, a);
		}
		break;
	case 4: //load game
		break;
	}

};
void Menu::moveUp()
{
	switch (menuNumber)
	{
	case 0:
		if (mainMenuSelected - 1 >= -1) //check if not on the first item (new game)
		{
			mainMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 120)); //change the previous item's color
			mainMenu[mainMenuSelected].setCharacterSize(textsize); //change the previous item's size
			mainMenuSelected--; //move to the upper item
			if (mainMenuSelected == -1)
			{
				mainMenuSelected = max_menu - 1;
			}
			mainMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 255));	//change the new item's color
			mainMenu[mainMenuSelected].setCharacterSize(textsize + 5); //change the new item's size
		}
		break;
	case 1:
		if (mainMenuSelected - 1 >= -1) //check if not on the first item (new game)
		{
			difficultyMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 120)); //change the pervious item's color
			difficultyMenu[mainMenuSelected].setCharacterSize(textsize);
			mainMenuSelected--; //move to the upper item
			if (mainMenuSelected == -1)
			{
				mainMenuSelected = diff_menu - 1;
			}
			difficultyMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 255));	//change the new item's color
			difficultyMenu[mainMenuSelected].setCharacterSize(textsize + 5);
		}
		break;
	case 2: //setting
		break;
	case 3: //game
		break;
	case 4: //load game
		break;
	}
};
void Menu::moveDown()
{
	switch (menuNumber)
	{
	case 0:
		if (mainMenuSelected + 1 <= max_menu) //check if not on the last item (exit)
		{
			mainMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 120)); //change the pervious item's color
			mainMenu[mainMenuSelected].setCharacterSize(textsize); //change the previous item's size
			mainMenuSelected++; //move to the lower item
			if (mainMenuSelected == max_menu)
			{
				mainMenuSelected = 0;
			}
			mainMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 255));	//change the new item's color
			mainMenu[mainMenuSelected].setCharacterSize(textsize + 5); //change the new item's size

		}
		break;
	case 1:
		if (mainMenuSelected + 1 <= diff_menu) //check if not on the last item (exit)
		{
			difficultyMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 120)); //change the pervious item's color
			difficultyMenu[mainMenuSelected].setCharacterSize(textsize);
			mainMenuSelected++; //move to the lower item
			if (mainMenuSelected == diff_menu)
			{
				mainMenuSelected = 0;
			}
			difficultyMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 255));	//change the new item's color
			difficultyMenu[mainMenuSelected].setCharacterSize(textsize + 5);
		}
		break;
	case 2: //setting
		break;
	case 3: //game
		break;
	case 4: //load game
		break;
	}
}

void Menu::changeMenu(int i)
{
	menuNumber = i;
}
int Menu::selectedMenu()
{
	return mainMenuSelected;
};
Menu::~Menu()
{

};

MenuSprite::MenuSprite()
{
	if (!menubgT.loadFromFile("texture/menubg.png") || !menubgBlankT.loadFromFile("texture/menubgBlank.png"))
	{
		cout << "load failed" << endl;
		system("pause");
	}
	menubgS.setTexture(menubgT);
	menubgBlankS.setTexture(menubgBlankT);
};

void MenuSprite::drawBG(sf::RenderWindow& window)
{
	window.draw(menubgS);
}

void MenuSprite::drawBGBlank(sf::RenderWindow& window) {
	window.draw(menubgBlankS);
}

void Menu::OutputText(sf::RenderWindow& window, string s, int corX, int corY, sf::Color a, int scale) {
	Text cur;
	cur.setFont(font);
	cur.setFillColor(a);
	cur.setString(s);
	cur.setCharacterSize(scale);
	cur.setPosition(sf::Vector2f(corX, corY)); /* 800 - 600 = w/h*/
	window.draw(cur);
}
int PressPage() {
	if (Keyboard::isKeyPressed(Keyboard::Num1)) return 2;
	if (Keyboard::isKeyPressed(Keyboard::Num2)) return 3;
}
int Menu::MenuSetting2(sf::RenderWindow& window, CPEOPLE a) {
	OutputText(window, "GAME RULE", 550, 50, sf::Color::White, 70);
	if (Keyboard::isKeyPressed(Keyboard::Num1)) return 2;
	return -1;
}
int Menu::MenuSetting(sf::RenderWindow& window, CPEOPLE a) {
	OutputText(window, "PRESS THE BUTTON TEST", 600, 150, sf::Color::Black, 30);
	OutputText(window, "GAME SETTING", 550, 50, sf::Color::White, 70);
	Texture TAWSD, TW, TA, TS, TD, TL, PL, TSG, TAW, TWD, TAS, TSD;
	int cor_XK = 200, cor_XY = 200;
	TAWSD.loadFromFile("Resource/AWSD.png");
	TW.loadFromFile("Resource/keyboardW.png");
	TA.loadFromFile("Resource/keyboardA.png");
	TS.loadFromFile("Resource/keyboardS.png");
	TD.loadFromFile("Resource/keyboardD.png");
	TL.loadFromFile("Resource/L.png");
	TSG.loadFromFile("Resource/SaveGame.png");
	TAW.loadFromFile("Resource/AW.png");
	TWD.loadFromFile("Resource/WD.png");
	TAS.loadFromFile("Resource/AS.png");
	TSD.loadFromFile("Resource/SD.png");
	sf::Sprite AWSD, W, A, S, D, L, L2, SG, AW, WD, AS, SD;
	AWSD.setTexture(TAWSD);
	AWSD.setPosition(cor_XK, cor_XY);
	AWSD.setScale(0.2f, 0.2f);
	L.setTexture(TL);
	L.setPosition(cor_XK + 125, cor_XY + 250);
	L.setScale(0.2f, 0.2f);
	window.draw(L);
	window.draw(AWSD);
	a.setPosition(1100, 150);
	a.update(3, 0);
	a.getSprite().setScale(4, 4);
	float deltaTime = 0.0f;
	Clock clock;
	deltaTime = clock.restart().asSeconds();
	a.move(deltaTime);
	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
		W.setTexture(TW);
		W.setPosition(cor_XK, cor_XY);
		W.setScale(0.2f, 0.2f);
		window.draw(W);
		//Move Up (we can another function for text only void OutputText(window, string))
	}
	if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
		S.setTexture(TS);
		S.setPosition(cor_XK, cor_XY);
		S.setScale(0.2f, 0.2f);
		window.draw(S);
	}
	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
		A.setTexture(TA);
		A.setPosition(cor_XK, cor_XY);
		A.setScale(0.2f, 0.2f);
		window.draw(A);
	}
	if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
		D.setTexture(TD);
		D.setPosition(cor_XK, cor_XY);
		D.setScale(0.2f, 0.2f);
		window.draw(D);
	}
	if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A)) {
		OutputText(window, "MOVE UP LEFT", 700, 200, sf::Color::Black, 50);
		AW.setTexture(TAW);
		AW.setPosition(cor_XK, cor_XY);
		AW.setScale(0.2f, 0.2f);
		window.draw(AW);
	}
	else {
		if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D)) {
			OutputText(window, "MOVE UP RIGHT", 700, 200, sf::Color::Black, 50);
			WD.setTexture(TWD);
			WD.setPosition(cor_XK, cor_XY);
			WD.setScale(0.2f, 0.2f);
			window.draw(WD);
		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::S)) {
				OutputText(window, "MOVE DOWN LEFT", 700, 200, sf::Color::Black, 50);
				AS.setTexture(TAS);
				AS.setPosition(cor_XK, cor_XY);
				AS.setScale(0.2f, 0.2f);
				window.draw(AS);
			}
			else {
				if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) {
					OutputText(window, "MOVE DOWN RIGHT", 700, 200, sf::Color::Black, 50);
					SD.setTexture(TSD);
					SD.setPosition(cor_XK, cor_XY);
					SD.setScale(0.2f, 0.2f);
					window.draw(SD);
				}
			}
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
		OutputText(window, "MOVE UP", 700, 200, sf::Color::Black, 50);
	}
	else {
		if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
			OutputText(window, "MOVE DOWN", 700, 200, sf::Color::Black, 50);
		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
				OutputText(window, "MOVE LEFT", 700, 200, sf::Color::Black, 50);
			}
			else {
				if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
					OutputText(window, "MOVE Right", 700, 200, sf::Color::Black, 50);
				}
			}
		}

	}
	if (Keyboard::isKeyPressed(Keyboard::L)) {
		PL.loadFromFile("Resource/KeyboardL.png");
		L2.setTexture(PL);
		L2.setPosition(cor_XK + 125, cor_XY + 250);
		L2.setScale(0.2f, 0.2f);
		SG.setTexture(TSG);
		SG.setPosition(750, cor_XY + 200);
		SG.setScale(0.3f, 0.3f);
		window.draw(L2);
		window.draw(SG);
	}
	a.draw(window);
	if (Keyboard::isKeyPressed(Keyboard::Num2)) return 3;
	return -1;
}
MenuSprite::~MenuSprite() {};
