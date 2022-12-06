#include "Header.h"
#define max_menu 4
#define diff_menu 4
using namespace std;
using namespace sf;
Menu::Menu(float w, float h)
{
	if (!font.loadFromFile("font/000OneTwoPunchBB-Regular.otf"))
	{
		std::cout << "no font loaded";
	}
	// New game
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::White);
	mainMenu[0].setString("New Game");
	mainMenu[0].setCharacterSize(70);
	mainMenu[0].setPosition(sf::Vector2f(w / 2 + 100, (h - 300) / (max_menu + 1) + 100));
	// Load Game
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color(255, 255, 255, 64));
	mainMenu[1].setString("Load Game");
	mainMenu[1].setCharacterSize(60);
	mainMenu[1].setPosition(sf::Vector2f(w / 2 + 100, (h - 300) / (max_menu + 1) * 2 + 150));
	// Setting
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color(255, 255, 255, 64));
	mainMenu[2].setString("Setting");
	mainMenu[2].setCharacterSize(60);
	mainMenu[2].setPosition(sf::Vector2f(w / 2 + 100, (h - 300) / (max_menu + 1) * 3 + 200));

	// Quit
	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(sf::Color(255, 255, 255, 64));
	mainMenu[3].setString("Quit");
	mainMenu[3].setCharacterSize(60);
	mainMenu[3].setPosition(sf::Vector2f(w / 2 + 100, (h - 300) / (max_menu + 1) * 4 + 250));

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

	//setting
	setting[0].setFont(font);
	setting[0].setFillColor(sf::Color::White);
	setting[0].setString("There is nothing here yet.\nPress enter to return\nto the main menu");
	setting[0].setCharacterSize(30);
	setting[0].setPosition(sf::Vector2f(w / 2 - 100, h / (max_menu + 1) * 1));

	mainMenuSelected = 0;
	menuNumber = 0;
};
void Menu::draw(sf::RenderWindow& window)
{
	switch (menuNumber)
	{
	case 0: //main menu
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
		window.draw(setting[0]);
		break;
	case 3: //game
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
			mainMenu[mainMenuSelected].setCharacterSize(60); //change the previous item's size
			mainMenuSelected--; //move to the upper item
			if (mainMenuSelected == -1)
			{
				mainMenuSelected = max_menu - 1;
			}
			mainMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 255));	//change the new item's color
			mainMenu[mainMenuSelected].setCharacterSize(70); //change the new item's size
		}
		break;
	case 1:
		if (mainMenuSelected - 1 >= -1) //check if not on the first item (new game)
		{
			difficultyMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 120)); //change the pervious item's color
			difficultyMenu[mainMenuSelected].setCharacterSize(60);
			mainMenuSelected--; //move to the upper item
			if (mainMenuSelected == -1)
			{
				mainMenuSelected = diff_menu - 1;
			}
			difficultyMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 255));	//change the new item's color
			difficultyMenu[mainMenuSelected].setCharacterSize(70);
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
			mainMenu[mainMenuSelected].setCharacterSize(60); //change the previous item's size
			mainMenuSelected++; //move to the lower item
			if (mainMenuSelected == max_menu)
			{
				mainMenuSelected = 0;
			}
			mainMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 255));	//change the new item's color
			mainMenu[mainMenuSelected].setCharacterSize(70); //change the new item's size

		}
		break;
	case 1:
		if (mainMenuSelected + 1 <= diff_menu) //check if not on the last item (exit)
		{
			difficultyMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 120)); //change the pervious item's color
			difficultyMenu[mainMenuSelected].setCharacterSize(30);
			mainMenuSelected++; //move to the lower item
			if (mainMenuSelected == diff_menu)
			{
				mainMenuSelected = 0;
			}
			difficultyMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 255));	//change the new item's color
			difficultyMenu[mainMenuSelected].setCharacterSize(35);
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
	if (!menubgT.loadFromFile("texture/menubg.png"))
	{
		cout << "load failed" << endl;
		system("pause");
	}
	menubgS.setTexture(menubgT);
	menubgS.scale({ 1.88, 1.5 });
};

void MenuSprite::drawBG(sf::RenderWindow& window)
{
	window.draw(menubgS);
}

MenuSprite::~MenuSprite() {};
