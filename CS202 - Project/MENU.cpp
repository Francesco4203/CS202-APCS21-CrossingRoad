#pragma once
#include "MENU.h"
#define max_menu 5
#define diff_menu 5
using namespace std;
using namespace sf;
Menu::Menu(float w, float h, CGAME* game)
{
	if (!font.loadFromFile("font/astrolyt.ttf"))
	{
		std::cout << "no font loaded";
	}
	int mmoffset = 500;
	int mmoffset2 = 450;
	int transparency = 120;
	textsize = 30;

	// New game
	mainMenu[0].SetAll("NEW GAME", textsize + 5, { 300,60 }, sf::Color{ 0, 0, 0, 0 }, (sf::Color(255, 255, 255, transparency)), font);
	mainMenu[0].setPos(sf::Vector2f(w / 2 - 100, (h - mmoffset) / (max_menu + 1)  + mmoffset2));
	// Load Game
	mainMenu[1].SetAll("LOAD GAME", textsize + 5, { 300,60 }, sf::Color{ 0, 0, 0, 0 }, (sf::Color(255, 255, 255, transparency)), font);
	mainMenu[1].setPos(sf::Vector2f(w / 2 - 100, (h - mmoffset) / (max_menu + 1)*2  + mmoffset2));
	// Setting
	mainMenu[2].SetAll("SETTING", textsize + 5, { 300,60 }, sf::Color{ 0, 0, 0, 0 }, (sf::Color(255, 255, 255, transparency)), font);
	mainMenu[2].setPos(sf::Vector2f(w / 2 - 100, (h - mmoffset) / (max_menu + 1) *3 + mmoffset2));
	// Highscore
	mainMenu[3].SetAll("HIGHSCORE", textsize + 5, { 300,60 }, sf::Color{ 0, 0, 0, 0 }, (sf::Color(255, 255, 255, transparency)), font);
	mainMenu[3].setPos(sf::Vector2f(w / 2 - 100, (h - mmoffset) / (max_menu + 1) * 4 + mmoffset2));
	// Quit
	mainMenu[4].SetAll("QUIT", textsize + 5, { 300,60 }, sf::Color{ 0, 0, 0, 0 }, (sf::Color(255, 255, 255, transparency)), font);
	mainMenu[4].setPos(sf::Vector2f(w / 2 - 100, (h - mmoffset) / (max_menu + 1) * 5 + mmoffset2));

	mainMenuSelected = 0;
	menuNumber = 0;

	Tvolume.loadFromFile("Resource/volume_bar_animation.png");
	volume.setTexture(Tvolume);
	_currentImage.width = Tvolume.getSize().x / 11;
	_currentImage.height = Tvolume.getSize().y;
	_scale.x = 10;
	_scale.y = 0;
	_currentImage.left = _scale.x * _currentImage.width;
	_currentImage.top = _scale.y * _currentImage.height;
	volume.setTextureRect(_currentImage);
	volume.setPosition(700, 600);
	
	_game = game;
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
			mainMenu[i].DrawButton(window);
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
		if (MenuSettingChara(window) == 3) {
			menuNumber = 3;
			window.clear();
			draw(window, a);
		}
		else {
			if (MenuSettingChara(window) == 4) {
				menuNumber = 4;
				window.clear();
				draw(window, a);
			}
		}
		break;
	case 3: //game
		menusprite.drawBGBlank(window);
		if (MenuSetting(window, a) == 4) {
			menuNumber = 4;
			window.clear();
			draw(window, a);
		}
		else {
			if (MenuSetting(window, a) == 2) {
				menuNumber = 2;
				window.clear();
				draw(window, a);
			}
		}
		break;
	case 4: //Character
		menusprite.drawBGBlank(window);
		if (MenuSetting2(window, a) == 2) {
			menuNumber = 2;
			window.clear();
			draw(window, a);
		}
		else {
			if (MenuSetting2(window, a) == 3) {
				menuNumber = 3;
				window.clear();
				draw(window, a);
			}
		}
		break;
	}

};
void Menu::MenuMouseDetect(sf::RenderWindow& window) {
	for (int i = 0; i < max_menu; i++) {
		if (mainMenu[i].isMO(window)) {
			mainMenu[i].setTColor(sf::Color(255, 255, 255, 255));
			mainMenu[i].setBG(sf::Color::Black);
			mainMenuSelected = i;
		}
		else {
			mainMenu[i].setTColor(sf::Color(255, 255, 255, 120));
			mainMenu[i].setBG(sf::Color{ 0, 0, 0, 0 });
		}
	}
}
void Menu::moveUp()
{
	switch (menuNumber)
	{
	case 0:
		if (mainMenuSelected - 1 >= -1) //check if not on the first item (new game)
		{
			mainMenu[mainMenuSelected].setTColor(sf::Color(255, 255, 255, 120));
			mainMenu[mainMenuSelected].setBG(sf::Color{ 0, 0, 0, 0 });//change the previous item's color
			mainMenu[mainMenuSelected].setST(textsize+5); //change the previous item's size
			mainMenuSelected--; //move to the upper item
			if (mainMenuSelected == -1)
			{
				mainMenuSelected = max_menu - 1;
			}
			mainMenu[mainMenuSelected].setTColor(sf::Color(255, 255, 255, 255));	//change the new item's color
			mainMenu[mainMenuSelected].setBG(sf::Color::Black);
			mainMenu[mainMenuSelected].setST(textsize + 5); //change the new item's size
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
			mainMenu[mainMenuSelected].setTColor(sf::Color(255, 255, 255, 120)); //change the pervious item's color
			mainMenu[mainMenuSelected].setBG(sf::Color{ 0, 0, 0, 0 });
			mainMenu[mainMenuSelected].setST(textsize+5); //change the previous item's size
			mainMenuSelected++; //move to the lower item
			if (mainMenuSelected == max_menu)
			{
				mainMenuSelected = 0;
			}
			mainMenu[mainMenuSelected].setTColor(sf::Color(255, 255, 255, 255));
			mainMenu[mainMenuSelected].setBG(sf::Color::Black);//change the new item's color
			mainMenu[mainMenuSelected].setST(textsize + 5); //change the new item's size

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
	if (!menubgT.loadFromFile("texture/menubg.png") || !menubgBlankT.loadFromFile("Resource/BG.png"))
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
	Texture Cur;
	Cur.loadFromFile("Resource/BG1.png");
	Sprite TBG_Lay;
	TBG_Lay.setTexture(Cur);
	window.draw(TBG_Lay);
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
	if (Keyboard::isKeyPressed(Keyboard::Num3)) return 4;
}
int Menu::MenuSettingChara(sf::RenderWindow & window) {
	OutputText(window, "CHARACTER SELECTION", 270, 0, sf::Color::White, 70);
	OutputText(window, "Page 1", 50, 850, sf::Color::White, 30);

	if (Keyboard::isKeyPressed(Keyboard::F)) {
		_game->SetPp(0.1f, 150.0f, 2);
	}
	if (Keyboard::isKeyPressed(Keyboard::M)) {
		_game->SetPp(0.1f, 150.0f, 1);
	}
	return PressPage();
	return -1;
}
int Menu::MenuSetting2(sf::RenderWindow& window, CPEOPLE a) {
	OutputText(window, "GAME RULE", 480, 0, sf::Color::White, 70);
	OutputText(window, "Page 3", 50, 850, sf::Color::White, 30);
	Texture TSetting_2;
	TSetting_2.loadFromFile("Resource/Setting_Page2.png");
	sf::Sprite Setting_2;
	Setting_2.setTexture(TSetting_2);
	Setting_2.setPosition(150, 120);
	Setting_2.setScale(0.4f, 0.4f);
	window.draw(Setting_2);
	return PressPage();
	return -1;
}
int Menu::MenuSetting(sf::RenderWindow& window,CPEOPLE a) {
	OutputText(window, "PRESS THE BUTTON TO TEST", 500, 100, sf::Color::Black, 30);
	OutputText(window, "GAME SETTING", 450, 0, sf::Color::White, 70);
	Texture TAWSD, TW, TA, TS, TD, TL, PL, TSG, TAW, TWD, TAS, TSD, TZX, TPZ, TPX, TC, TPC;
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
	TZX.loadFromFile("Resource/XZ.png");
	TPZ.loadFromFile("Resource/PZX.png");
	TPX.loadFromFile("Resource/PXZ.png");
	TC.loadFromFile("Resource/C.png");
	TPC.loadFromFile("Resource/CP.png");
	sf::Sprite AWSD, W, A, S, D, L, L2, SG, AW, WD, AS, SD, XZ, PZ, PX,C, PC;

	AWSD.setTexture(TAWSD);
	AWSD.setPosition(cor_XK, cor_XY);
	AWSD.setScale(0.2f, 0.2f);
	L.setTexture(TL);
	L.setPosition(cor_XK + 125, cor_XY + 250);
	L.setScale(0.2f, 0.2f);
	XZ.setTexture(TZX);
	XZ.setScale(0.2f, 0.2f);
	XZ.setPosition(cor_XK - 50, cor_XY + 380);
	C.setTexture(TC);
	C.setScale(0.2f, 0.2f);
	C.setPosition(cor_XK + 300, cor_XY + 380);
	window.draw(L);
	window.draw(XZ);
	window.draw(AWSD);
	window.draw(C);
	a.setPosition(1100, 150);
	a.update(3, 0);
	a.getSprite().setScale(4, 4);
	float deltaTime = 0.0f;
	Clock clock;
	deltaTime = clock.restart().asSeconds();
	a.move(deltaTime);

	window.draw(volume);
	if (Keyboard::isKeyPressed(Keyboard::Z) && _scale.x > 1) {
		PZ.setTexture(TPZ);
		PZ.setScale(0.2f, 0.2f);
		PZ.setPosition(cor_XK - 50, cor_XY + 380);
		_scale.x--;
		_currentImage.left = _scale.x * _currentImage.width;
		volume.setTextureRect(_currentImage);
		window.draw(PZ);
		window.draw(volume);
		_game->adjustVolume(-1);
	}
	if (Keyboard::isKeyPressed(Keyboard::X) && _scale.x < 10) {
		PX.setTexture(TPX);
		PX.setScale(0.2f, 0.2f);
		PX.setPosition(cor_XK - 50, cor_XY + 380);
		_scale.x++;
		_currentImage.left = _scale.x * _currentImage.width;
		volume.setTextureRect(_currentImage);
		window.draw(PX);
		window.draw(volume);
		_game->adjustVolume(1);
	}
	if (Keyboard::isKeyPressed(Keyboard::C)) {
		PC.setTexture(TPC);
		PC.setScale(0.2f, 0.2f);
		PC.setPosition(cor_XK + 300, cor_XY + 380);
		_scale.x = 0;
		_currentImage.left = _scale.x * _currentImage.width;
		volume.setTextureRect(_currentImage);
		window.draw(PC);
		window.draw(volume);
		_game->adjustVolume(0);
	}

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
		OutputText(window, "MOVE UP LEFT", 700, 200, sf::Color::Black, 30);
		AW.setTexture(TAW);
		AW.setPosition(cor_XK, cor_XY);
		AW.setScale(0.2f, 0.2f);
		window.draw(AW);
	}
	else {
		if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D)) {
			OutputText(window, "MOVE UP RIGHT", 700, 200, sf::Color::Black, 30);
			WD.setTexture(TWD);
			WD.setPosition(cor_XK, cor_XY);
			WD.setScale(0.2f, 0.2f);
			window.draw(WD);
		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::S)) {
				OutputText(window, "MOVE DOWN LEFT", 700, 200, sf::Color::Black, 30);
				AS.setTexture(TAS);
				AS.setPosition(cor_XK, cor_XY);
				AS.setScale(0.2f, 0.2f);
				window.draw(AS);
			}
			else {
				if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) {
					OutputText(window, "MOVE DOWN RIGHT", 700, 200, sf::Color::Black, 30);
					SD.setTexture(TSD);
					SD.setPosition(cor_XK, cor_XY);
					SD.setScale(0.2f, 0.2f);
					window.draw(SD);
				}
			}
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
		OutputText(window, "MOVE UP", 700, 200, sf::Color::Black, 30);
	}
	else {
		if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
			OutputText(window, "MOVE DOWN", 700, 200, sf::Color::Black, 30);
		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
				OutputText(window, "MOVE LEFT", 700, 200, sf::Color::Black, 30);
			}
			else {
				if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
					OutputText(window, "MOVE RIGHT", 700, 200, sf::Color::Black, 30);
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
	OutputText(window, "Page 2 - Switch page by press the according number.", 50, 850, sf::Color::White, 30);
	return PressPage();
	return -1;
}
MenuSprite::~MenuSprite() {};
