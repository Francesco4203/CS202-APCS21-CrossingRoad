#pragma once
#include "State.h"
#include "SCOREBOARD.h"
#include "BUTTON.h"

class HighscoreState : public State
{
private:
	SCOREBOARD* board;
	Button* undo;
	Button* clear;

	int time;
	string name;

	SoundBuffer Bsound;
	Sound sound;
public:
	HighscoreState(RenderWindow* app, stack<State*>* states, int time, string name);
	HighscoreState(RenderWindow* app, stack<State*>* states);
	~HighscoreState();

	void add();
	void endState();

	void resumeSound();

	void update();
	void render();
};

