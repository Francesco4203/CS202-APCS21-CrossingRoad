#pragma once
#include "State.h"
#include <SFML/Audio.hpp>

class LevelUpState : public State
{
private:
	Texture texture;
	Sprite background;

	SoundBuffer Bsound;
	Sound sound;

	float totalTime = 0.0f;
	float endStateTime = 2.0f;

	Clock timer;

public:
	LevelUpState(RenderWindow* app, stack <State*>* states, bool isMan);
	~LevelUpState();

	void endState();
	void resumeSound();

	void update();
	void render();
};

