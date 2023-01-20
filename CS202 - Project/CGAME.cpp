#include "CGAME.h"

void CGAME::initWindow()
{
    string title = "CROSSING ROAD GAME";

    VideoMode Size(1500, 900);
    this->app = new RenderWindow(Size, title);
}
void CGAME::initStates()
{
    this->states.push(new MainMenuState(this->app, &this->states));
}

// Constructor functions
CGAME::CGAME()
{
    this->initWindow();
    this->initStates();
}
CGAME::~CGAME()
{
    delete this->app;
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

void CGAME::updateSFMLEvents()
{
    while (this->app->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == Event::Closed)
            this->app->close();
        if (this->sfEvent.type == Event::KeyPressed) {
        }
    }
}

void CGAME::update()
{
    if (!this->states.empty())
    {
        if (!this->states.top()->getQuit())
            this->states.top()->update();
        if (this->states.top()->getQuit()) {
            delete this->states.top();
            this->states.pop();
            this->states.top()->resumeSound();
        }
    }
    this->updateSFMLEvents();
}

void CGAME::render()
{
    this->app->clear();
    if (!this->states.empty())
        this->states.top()->render();
    else
    {
        this->app->close();
    }
    this->app->display();
}

void CGAME::run()
{
    while (this->app->isOpen())
    {
        this->update();
        this->render();
    }
}