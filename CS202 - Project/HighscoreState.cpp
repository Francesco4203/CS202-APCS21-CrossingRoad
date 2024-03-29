#include "HighscoreState.h"

HighscoreState::HighscoreState(RenderWindow* app, stack<State*>* states, int time, string name) 
: State(app, states), name(name), time(time)
{
	int vol;
	ifstream fin("Data/current_volume");
	fin >> vol;
	fin.close();

	Bsound.loadFromFile("Resource/Sound/highscore.wav");
	sound.setBuffer(Bsound);
	sound.setVolume(vol*10);
	sound.setLoop(false);
	sound.play();

	board = new SCOREBOARD();
	board->load();
	add();

	undo = new Button("Resource/sub_load_game_btn", 0, 900 - 60, 60, 60, "undo_btn", false);
	clear = new Button("R�ource/sub_highscore_btn", 1300, 700, 281, 75, "clear_board_btn", false);
}
HighscoreState::HighscoreState(RenderWindow* app, stack<State*>* states) : State(app, states) {
	int vol;
	ifstream fin("Data/current_volume");
	fin >> vol;
	fin.close();

	Bsound.loadFromFile("Resource/Sound/highscore.wav");
	sound.setBuffer(Bsound);
	sound.setVolume(vol*10);
	sound.setLoop(false);
	sound.play();
	
	board = new SCOREBOARD();
	board->load();
	time = INT_MAX;
	name = "";

	undo = new Button("Resource/sub_load_game_btn", 0, 900 - 60, 60, 60, "undo_btn", false);
	clear = new Button("Resource/sub_highscore_btn", 953, 130, 281, 75, "clear_board_btn", false);

}
HighscoreState::~HighscoreState() {
	delete board;
	delete undo;
	delete clear;
}

void HighscoreState::add() {
	board->add(time, name);
}
void HighscoreState::endState() {
	quit = true;
}

void HighscoreState::resumeSound() {
	
}

void HighscoreState::update() {
	this->updateMousePositions();
	undo->update(this->mousePosView);
	clear->update(this->mousePosView);
	if (undo->isPressed()) {
		board->save();
		sound.stop();
		endState();
	}
	if (clear->isPressed()) {
		board->clear();
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		board->save();
		sound.stop();
		endState();
	}
}
void HighscoreState::render() {
	board->show(app);
	undo->render(app);
	clear->render(app);
}