#include "LevelUpState.h"
#include <fstream>

LevelUpState::LevelUpState(RenderWindow* app, stack <State*>* states, bool isMan) : State(app, states) {
	if (isMan) {
		texture.loadFromFile("Resource/levelup_man.png");
	}
	else {
		texture.loadFromFile("Resource/levelup_woman.png");
	}
	background.setTexture(texture);

	int vol;
	ifstream fin("Data/current_volume");
	fin >> vol;
	fin.close();

	Bsound.loadFromFile("Resource/Sound/levelUp.wav");
	sound.setBuffer(Bsound);
	sound.setVolume(vol*10);
	sound.play();
}

LevelUpState::~LevelUpState() {

}

void LevelUpState::endState() {
	quit = true;
}

void LevelUpState::resumeSound() {

}

void LevelUpState::update() {
	totalTime += timer.getElapsedTime().asSeconds();;
	timer.restart();
	if (totalTime >= endStateTime) {
		endState();
	}
}

void LevelUpState::render() {
	app->draw(background);
}