#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "LevelUpState.h"
#include "GameWinState.h"
#include "BUTTON.h"
#include "CTRAFFIC.h"
#include "CPEOPLE.h"
#include <ctime>

class PopUpPauseGame
{
public:
	PopUpPauseGame(CPEOPLE person, int mode);
	~PopUpPauseGame();

	void render(RenderWindow* app);

private:
	Texture texture;
	Sprite background;

	Font font;
	Text lv;

	Texture Tperson;
	Sprite person;
	map<string, Button*> buttons;

	friend class GameState;
};

class GameState : public State
{
public:
	GameState(RenderWindow* app, stack <State*>* states);
	GameState(RenderWindow* app, stack <State*>* states, string directory);
	~GameState();

	void gameSet();
	bool loadGame(string directory);

	void endState();
	void resumeSound();

	void gameOver();
	bool isFinishExplosion();

	void update();
	void render();

private:
	Texture Tbackground;
	Sprite background;

	Texture TfinishLine;
	Sprite finishLine;

	Texture TgameOver;
	Sprite gameOverImage;

	SoundBuffer BsoundGameOver;
	Sound soundGameOver;

	SoundBuffer BsoundGame;
	Sound soundGame;

	IntRect _currentImageExplosion;
	Vector2u _scaleExplosion;
	Texture Texplosion;
	Sprite explosion;

	SoundBuffer BsoundExplosion;
	Sound soundExplosion;

	Texture Tlevel;
	Sprite level;

	Text levelText;
	Font levelFont;

	vector<LINE*> map;
	vector<pair<clock_t, clock_t>> time;

	CPEOPLE* person = new CPEOPLE(0.1f, 150.0f);

	bool isPlaying;
	bool isWin;
	bool isFinishGameOverScene;

	float delta_time = 0.0f;
	float switchTimeExplosion = 0.1f;
	float totalTimeExplosion = 0.0f;

	int mode;
	Clock timer;
	clock_t start;
	clock_t pauseTime;
	int totalPauseTime;

	Button* nav;
	PopUpPauseGame* popup;

	friend class SaveGameState;
};