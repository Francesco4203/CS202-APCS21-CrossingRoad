#include "SaveGameState.h"

SaveGameState::SaveGameState(RenderWindow* app, stack<State*>* states, GameState* game) : State(app, states) {
	this->game = game;
	
	texture.loadFromFile("Resource/menusave.png");
	background.setTexture(texture);

	font.loadFromFile("font/astrolyt.ttf");
	inputFile.setFont(font);
	inputFile.scale(1.5, 1.5);
	inputFile.setFillColor(Color::Red);
	inputFile.setPosition(350, 580);
}
SaveGameState::~SaveGameState() {

}

void SaveGameState::saveGame(string fileName) {
    string path = "Saved Game/" + fileName;
    
    ofstream f(path);

    f << game->person->getIsMan() << '\n';
    f << game->mode << ' ' << game->map.size() << '\n';
    for (int i = 0; i < game->map.size(); i++) game->map[i]->output(f);
    for (int i = 0; i < game->time.size(); i++) {
        f << game->time[i].second - game->time[i].first << '\n';
        f << game->map[i]->getLight().getTime() << '\n';
        f << game->map[i]->getLight().getState() << '\n';
    }
    game->person->output(f);
    f << clock() - game->start << '\n';
    f << game->totalPauseTime << "\n";

    f.close();
}

void SaveGameState::resumeSound() {

}
void SaveGameState::endState() {
	quit = true;
}

void SaveGameState::update() {
    while (app->pollEvent(ev)) {
        if (ev.type == Event::TextEntered) {
            if (ev.text.unicode == 13) {
                if (getInput.length() == 0) {
                    return;
                }
                else {
                    saveGame(getInput);
                    endState();
                }
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
void SaveGameState::render() {
	app->draw(background);
	app->draw(inputFile);
}