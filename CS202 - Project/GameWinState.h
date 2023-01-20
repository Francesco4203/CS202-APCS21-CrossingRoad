#pragma once
#include "State.h"
#include "BUTTON.h"
#include "HighscoreState.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
class GameWinState : public State
{
private:
	Texture texture;
	Sprite background;

	SoundBuffer Bsound;
	Sound sound;

	Font font;
	Text inputFile;

	string getInput;
	String inputText;
	
	int maxChar = 30;
	bool isDone = false;

	int time;
	sf::Event ev;

	Button* undo;

public:
	GameWinState(RenderWindow* app, stack<State*>* states, int time);
	~GameWinState();

	void resumeSound();
	void endState();

	void update();
	void render();
};

