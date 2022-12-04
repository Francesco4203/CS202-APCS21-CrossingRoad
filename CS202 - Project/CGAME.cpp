#include "INCLUDING.h"
using namespace std;
using namespace sf;

CGAME::CGAME() {
    map.clear();
    mode = 1;
	win = 1;
	isPlaying = 0;
    window.create(VideoMode(1500, 800), "Crossing Road Game!");
}
void CGAME::GameOver(sf::RenderWindow& window) {
	Texture Gameover;
	Gameover.loadFromFile("Resource/Gameover2.png");
	sf::Sprite GO(Gameover);
	GO.scale(1.0f, 1.0f);
	GO.setPosition(500, 200);
	window.draw(GO);
}
void CGAME::menu() {
	int menuNumber = 0;
	Menu menu(800, 600);
	MenuSprite menusprite;
    while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.moveUp();
					break;
				case sf::Keyboard::Down:
					menu.moveDown();
					break;
				case sf::Keyboard::Enter:
					//cout << "enter" << endl;
					switch (menuNumber)
					{
					case 0: // main menu
						switch (menu.selectedMenu())
						{
						case 0: //new game
							menuNumber = 1;
							menu.changeMenu(1);
							break;
						case 1: //load game
							//insert code load game here
							menuNumber = 4;
							menu.changeMenu(4);
							break;
						case 2: //setting
							menuNumber = 2;
							menu.changeMenu(2);
							break;
						case 3:
							window.close();
						}
						break;
					case 2: // setting
						menuNumber = 0;
						menu.changeMenu(0);
						break;
					case 3: // game
						while (win) {
							isPlaying = 1;
							newGame();
							mode = min(3, mode + 1);
						}
						while (window.pollEvent(event));
						isPlaying = 0;
						win = mode = 1;
						break;
					case 4: // load game
						break;
					}
				}
			}
		}
		window.clear();
		menusprite.drawBG(window);
		menu.draw(window);
		window.display();
    }
}
void CGAME::newGame() {
    gameSet();
    playGame();
}
void CGAME::gameSet() {
    isPlaying = 1;
    for (auto& c : map) delete c;
    map.clear();
    for (int i = 0; i < 2 + mode; i++) {
        int isLane = rand() % 2;
        int direction = rand() % 2;
        int easier = rand() % 4;
        LINE* a = new LINE(50 + 120 * i, direction + 1, isLane, min(3, mode + !easier));
        map.push_back(a);
    }
    time = vector<pair<clock_t, clock_t>>(mode + 2);
    for (int i = 0; i < mode + 2; ++i) {
        time[i].first = clock() + rand() % 10 * CLOCKS_PER_SEC;
        time[i].second = clock() + rand() % 10 * CLOCKS_PER_SEC;
    }
    for (int i = 0; i < 2 + mode; i++) {
        int isLane = rand() % 2;
        int direction = rand() % 2;
        int easier = rand() % 4;
        LINE* a = new LINE(50 + 150 * i, direction + 1, isLane, min(3, mode + !easier));
        map.push_back(a);
    }
}
void CGAME::playGame() {
    CPEOPLE Person(0.3f, 100.0f);
    Clock clock;
    float deltaTime = 0.0f;
    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        Person.move(deltaTime);
        window.clear();
		for (int i = 0; i < 2 + mode; i++) {
			if (Person.isImpact(map[i])) {
				win = 0;
				GameOver(window);
				break;
			}
		}
		if (Person.isFinish(window)) {
			win = 1;
			return;
		}
		Person.draw(window);
		window.display();
		if (win == 0) {
			this_thread::sleep_for(1s);
			return;
		}
    }
}