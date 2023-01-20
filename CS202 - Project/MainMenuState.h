#pragma once
#include "BUTTON.h"
#include "State.h"
#include "GameState.h"
#include "HighscoreState.h"
#include "LoadGameState.h"
#include "SettingState.h"

using namespace std;
using namespace sf;

class MainMenuState : public State {
private:
    Texture texture;
    Sprite background;
    map<string, Button* > buttons;
    Music theme;

    void initBackground();
    void initButtons();
    void initSounds();

public:
    MainMenuState(RenderWindow* app, stack<State*>* states);
    virtual ~MainMenuState();

    void endState();
    void updateButtons();
    void update();

    void resumeSound();

    void render();
    void renderButtons();
};