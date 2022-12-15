﻿#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include <ctime>
#include <chrono>
#include <thread>
#include "MENU.h"
#include "CANIMAL.h"
#include "CPEOPLE.h"
#include "CVEHICLE.h"
#include "CTRAFFIC.h"
#include "CENEMY.h"
using namespace std;
using namespace sf;
class CGAME {
    SoundBuffer BlevelUp;
    Sound levelUp;
    Texture TlevelUp;
    Sprite SlevelUp;
    SoundBuffer Bsound;
    SoundBuffer BgameOverSound;
    Sound sound;
    vector<LINE*> map;
    vector<pair<clock_t, clock_t>> time;
    RenderWindow window;
    bool win, isPlaying;
    Sprite level;
    Texture levelImage;
    Text levelText;
    Font levelFont;
    Texture Tbackground;
    Sprite background;
    Texture TgameOver;
    Sprite gameOver;
    CPEOPLE Person = CPEOPLE(0.3f, 150.0f);
public:
    int mode;
    CGAME();
    ~CGAME();
    void GameWin(sf::RenderWindow& window);
    void GameOver(sf::RenderWindow& window);
    void menu();
    void gameSet();
    void playSession(Event& event);
    void playGame();
    void output(ofstream& f);
    bool input(ifstream& f);
    bool loadGame();
};