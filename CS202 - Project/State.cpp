#include "State.h"

State::State(RenderWindow* app, stack<State*>* states)
{
    this->app = app;
    this->states = states;
    this->quit = false;
    this->paused = false;
}

State::~State()
{
    
}

void State::pauseState() {
    this->paused = true;

}

void State::unpauseState() {
    this->paused = false;

}

void State::updateMousePositions()
{
    this->mousePosWindow = Mouse::getPosition(*this->app);
    this->mousePosView = this->app->mapPixelToCoords(mousePosWindow);
}

const bool& State::getQuit() const
{
    return this->quit;
}