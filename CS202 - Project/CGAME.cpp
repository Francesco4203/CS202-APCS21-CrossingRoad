#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "CANIMAL.h"
#include "CPEOPLE.h"
#include "CVEHICLE.h"
#include "CGAME.h"
#include "CTRAFFIC.h"
#include "CENEMY.h"

using namespace std;
using namespace sf;

CGAME::CGAME() {
    map.clear();
    mode = 1;
    win = isPlaying = 0;
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
    RenderWindow window(VideoMode(1500, 800), "Crossing Road Game!");
    while (window.isOpen()) {
        Event ev;
        while (window.pollEvent(ev)) {

        }
        window.clear();
        
        for (int i = 0; i < 2 + mode; i++) {
            map[i]->draw(window, time[i]);
        }

        window.display();
    }
}