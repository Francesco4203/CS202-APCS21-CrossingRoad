#pragma once
#include "State.h"
#include "GameState.h"
#include "dirent.h"
#include "BUTTON.h"
#include <fstream>

class PopUp
{
public:
	PopUp(string fileName);
	~PopUp();

	void render(RenderWindow* app);

private:
	Texture texture;
	Sprite background;

	Font font;
	Text name;
	Text lv;

	string stringName;
	map<string, Button*> buttons;

	friend class LoadGameState;
};

class LoadGameState : public State
{
private:
	Texture Tbg;
	Sprite bg;
	
	Texture TarrowDown;
	Texture TarrowUp;
	Sprite arrowDown;
	Sprite arrowUp;

	Font font;

	PopUp* popup;

	int display_size = 6;
	int top;
	Event ev;

	vector<string> fileList;
	map< string, pair<int, Button*>> fileButtons;

	Button* undo;
public:
	LoadGameState(RenderWindow* app, stack<State*>* states);
	~LoadGameState();

	void resumeSound();
	void endState();

	void updateButtons();
	void update();
	void render();
};

vector<string> getListFileName(string directory);