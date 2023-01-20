#pragma once
#include "State.h"
#include "BUTTON.h"
#include "CPEOPLE.h"

class PopUpPage1 {
public:
	PopUpPage1(bool isMan);
	~PopUpPage1();

	void render(RenderWindow* app);

private:
	Texture texture;
	Sprite background;

	Button* exit;

	friend class SettingState1;
};

class SettingState1 : public State
{
private:
	Texture texture;
	Sprite background;

	Music* sound;

	map<string, Button*> buttons;
	PopUpPage1* popup;

	Font font;
	Text title;
public:
	SettingState1(RenderWindow* app, stack<State*>* states, Music* sound);
	~SettingState1();

	void resumeSound();
	void endState();

	void update();
	void render();
};

class SettingState2 : public State
{
private:
	Texture texture;
	Sprite background;

	map<string, Button*> buttons;
	Texture TAWSD, TW, TA, TS, TD, TAW, TWD, TAS, TSD, TZX, TPZ, TPX, TC, TPC;
	Sprite AWSD, W, A, S, D, AW, WD, AS, SD, XZ, PZ, PX, C, PC;

	Texture Tvolume;
	Sprite volume;
	IntRect _currentImage;
	Vector2u _scale;

	Font font;
	Text title;
	Text subTitle;
	Text description;

	CPEOPLE* person = new CPEOPLE(0.1f, 150.0f);
	int cor_XK = 200, cor_XY = 200;

	Music* sound;
	Event ev;
public:
	SettingState2(RenderWindow* app, stack<State*>* states, Music* sound);
	~SettingState2();

	void resumeSound();
	void endState();

	void update();
	void render();
};

class SettingState3 : public State
{
private:
	Texture texture;
	Sprite background;

	Texture Trule;
	Sprite rule;

	Button* undo;

	Font font;
	Text title;
public:
	SettingState3(RenderWindow* app, stack<State*>* states);
	~SettingState3();

	void resumeSound();
	void endState();

	void update();
	void render();
};