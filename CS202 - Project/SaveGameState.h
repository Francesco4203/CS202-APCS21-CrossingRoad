#pragma once
#include "GameState.h"
#include "HighscoreState.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <fstream>

class SaveGameState : public State
{
private:
	Texture texture;
	Sprite background;

	Font font;
	Text inputFile;

	string getInput;
	String inputText;

	int maxChar = 30;

	GameState* game;
	sf::Event ev;

public:
	SaveGameState(RenderWindow* app, stack<State*>* states, GameState* game);
	~SaveGameState();

	void saveGame(string fileName);

	void resumeSound();
	void endState();

	void update();
	void render();
};

