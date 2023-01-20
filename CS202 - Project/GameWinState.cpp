#include "GameWinState.h"

GameWinState::GameWinState(RenderWindow* app, stack<State*>* states, int time) : State(app, states) {
	texture.loadFromFile("Resource/menuvictory.png");
	background.setTexture(texture);

    int vol;
    ifstream fin("Data/current_volume");
    fin >> vol;
    fin.close();

	Bsound.loadFromFile("Resource/Sound/gameWin.wav");
	sound.setBuffer(Bsound);
    sound.setVolume(vol*10);
	sound.play();
	sound.setLoop(false);

	font.loadFromFile("font/astrolyt.ttf");
	inputFile.setFont(font);
	inputFile.scale(1.5, 1.5);
	inputFile.setFillColor(Color::Red);
	inputFile.setPosition(350, 580);
    
    this->time = time;
    undo = new Button("Resource/sub_load_game_btn", 0, 900 - 60, 60, 60, "undo_btn", false);
}
GameWinState::~GameWinState() {
    delete undo;
}

void GameWinState::resumeSound() {

}
void GameWinState::endState() {
	quit = true;
}

void GameWinState::update() {
    this->updateMousePositions();
    undo->update(this->mousePosView);
    if (undo->isPressed()) {
        endState();
    }
    while (app->pollEvent(ev)) {
        if (ev.type == Event::TextEntered) {
            if (ev.text.unicode == 13) {
                if (getInput.length() == 0) {
                    states->push(new HighscoreState(app, states));
                }
                else {
                    states->push(new HighscoreState(app, states, time, getInput));
                }
                endState();
            }
            else if (32 <= ev.text.unicode && ev.text.unicode <= 126 && getInput.length() <= maxChar) { //printable
                getInput += ev.text.unicode;
                inputText += ev.text.unicode;
                inputFile.setString(inputText);
            }
            else if (ev.text.unicode == 8 && getInput.length() >= 1) { //backspace
                getInput.pop_back();
                inputText.erase(inputText.getSize() - 1);
                inputFile.setString(inputText);
            }
        }
    }
}
void GameWinState::render() {
    app->draw(background);
    app->draw(inputFile);
    undo->render(app);
}