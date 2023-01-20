#pragma once

#include "MainMenuState.h"

using namespace std;
using namespace sf;

class CGAME {
private:
	RenderWindow* app;
	Event sfEvent;
	stack<State*> states;

    void initWindow();
    void initStates();
public:
    CGAME();
    virtual ~CGAME();
    // Functions
    void updateSFMLEvents();
    void update();
    void render();
    void run();
};