#pragma once
#include "INCLUDING.h"
using namespace std;
using namespace sf;
class CGAME {
    vector<LINE*> map;
    vector<pair<clock_t, clock_t>> time;
    RenderWindow window;
    bool win, isPlaying;
    Sprite level;
    Texture levelImage;
    Text levelText;
    Font levelFont;
    CPEOPLE Person = CPEOPLE(0.3f, 150.0f);
public:
    int mode;
    CGAME();
    void GameOver(sf::RenderWindow& window);
    void menu();
    void gameSet();
    void newGame();
    void playGame();
    void output(ofstream& f);
    void input(ifstream& f);
    void loadGame();
};