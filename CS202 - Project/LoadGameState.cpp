#include "LoadGameState.h"

LoadGameState::LoadGameState(RenderWindow* app, stack<State*>* states) :
State(app, states)
{
	fileList = getListFileName("Saved Game");
    for (int i = 0; i < fileList.size(); ++i) {
        this->fileButtons[fileList[i]] = new Button("Resource/sub_load_game_btn/sub_load_game_btn", 287, 250 + i * 100, 926, 90, fileList[i], true);
    }
	undo = new Button("Resource/sub_load_game_btn", 0, 900 - 60, 60, 60, "undo_btn", false);

	Tbg.loadFromFile("Resource/select.png");
	bg.setTexture(Tbg);

	TarrowDown.loadFromFile("Resource/arrow_down.png");
	TarrowUp.loadFromFile("Resource/arrow_up.png");
	arrowDown.setTexture(TarrowDown);
	arrowUp.setTexture(TarrowUp);
	arrowDown.setPosition(1185, 815);
	arrowUp.setPosition(1185, 250);

	font.loadFromFile("font/astrolyt.ttf");

	popup = NULL;
	top = 0;
}
LoadGameState::~LoadGameState() {
	for (auto& it : this->fileButtons)
	{
		delete it.second;
	}
	delete undo;
	delete popup;
}

void LoadGameState::resumeSound() {

}
void LoadGameState::endState() {
	quit = true;
}

void LoadGameState::updateButtons() {
	if (!popup) {
		for (auto& it : this->fileButtons)
		{
			it.second->update(this->mousePosView);
		}
		undo->update(this->mousePosView);
		if (undo->isPressed()) {
			endState();
		}
		for (int i = top; i < min(top + display_size,(int) fileList.size()); ++i) {
			if (this->fileButtons[fileList[i]]->isPressed())
			{
				popup = new PopUp(fileList[i]);
			}
		}
		while (app->pollEvent(ev))
		{
			if (ev.type == Event::MouseWheelMoved) {
				if (ev.mouseWheel.delta > 0 && top > 0 && fileList.size() > display_size) {
					top--;
					for (int i = 0; i < fileList.size(); ++i) {
						fileButtons[fileList[i]]->setPosition(fileButtons[fileList[i]]->getPosition().x, fileButtons[fileList[i]]->getPosition().y + 100);
					}
				}
				if (ev.mouseWheel.delta < 0 && top < fileList.size() - display_size && fileList.size() > display_size) {
					top++;
					for (int i = 0; i < fileList.size(); ++i) {
						fileButtons[fileList[i]]->setPosition(fileButtons[fileList[i]]->getPosition().x, fileButtons[fileList[i]]->getPosition().y - 100);
					}
				}
			}
		}
	}
	else {
		for (auto& it : this->popup->buttons)
		{
			it.second->update(this->mousePosView);
		}
		if (popup->buttons["continue"]->isPressed()) {
			this->states->push(new GameState(app, states, "Saved Game/" + popup->stringName));
			endState();
		}
		if (popup->buttons["delete"]->isPressed()) {
			remove(("Saved Game/" + popup->stringName).c_str());
			for (auto it = fileList.begin(); it != fileList.end(); ++it) {
				if (*it == popup->stringName) {
					fileList.erase(it);
					break;
				}
			}
			for (map<string, Button*>::iterator it = fileButtons.begin(); it != fileButtons.end(); ++it) {
				if (it->first == popup->stringName) {
					auto tmp = it;
					it++;
					if (it == fileButtons.end() && top > 0) {
						fileButtons.erase(tmp);
						top--;
						for (map<string, Button*>::iterator it1 = fileButtons.begin(); it1 != fileButtons.end(); ++it1) {
							it1->second->setPosition(it1->second->getPosition().x, it1->second->getPosition().y + 100);
						}
					}
					else {
						fileButtons.erase(tmp);
						for (; it != fileButtons.end(); ++it) {
							it->second->setPosition(it->second->getPosition().x, it->second->getPosition().y - 100);
						}
					}
					break;
				}
			}
			delete popup;
			popup = NULL;
		}
		if (popup && popup->buttons["exit"]->isPressed()) {
			delete popup;
			popup = NULL;
		}
	}
}

void LoadGameState::update() {
	this->updateMousePositions();
	this->updateButtons();
}
void LoadGameState::render() {
    app->draw(bg);
	for (int i = top; i < min(top + display_size,(int) fileList.size()); ++i) {
		fileButtons[fileList[i]]->render(app);
	}

	undo->render(app);

	if (top > 0 && fileList.size() > display_size) {
		app->draw(arrowUp);
	}
	if (top < fileList.size() - display_size && fileList.size() > display_size) {
		app->draw(arrowDown);
	}

	if (popup) {
		popup->render(app);
	}
}

PopUp::PopUp(string fileName) {
	texture.loadFromFile("Resource/menupopup.png");
	background.setTexture(texture);
	background.setPosition((1500 - 700) / 2, (900 - 320) / 2);

	font.loadFromFile("font/astrolyt.ttf");
	lv.setFont(font);
	lv.setFillColor(Color::White);
	lv.setPosition(background.getPosition().x + 50, background.getPosition().y + 100);
	name.setFont(font);
	name.setFillColor(Color::White);
	name.setPosition(background.getPosition().x + 50, background.getPosition().y + 25);
	ifstream fin("Saved Game/" + fileName);
	int tmp;
	for (int i = 1; i <= 2; ++i) fin >> tmp;
	fin.close();
	string stringLv = "Level: ";
	if (tmp <= 3) stringLv.push_back(tmp + 48);
	else stringLv += "Crazy";
	lv.setString(stringLv);
	name.setString(fileName);
	stringName = fileName;

	this->buttons["continue"] = new Button("Resource/sub_load_game_btn/pop_up_continue_btn", background.getPosition().x + 50, background.getPosition().y + 200, 283, 76, "continue_btn", false);
	this->buttons["delete"] = new Button("Resource/sub_load_game_btn/pop_up_delete_btn", background.getPosition().x + 370, background.getPosition().y + 200, 283, 76, "delete_btn", false);
	this->buttons["exit"] = new Button("Resource/sub_load_game_btn/pop_up_exit_btn",background.getPosition().x + 700 - 38, background.getPosition().y, 40, 40, "exit_btn", false);
}
PopUp::~PopUp() {
	for (auto& it : this->buttons)
	{
		delete it.second;
	}
}

void PopUp::render(RenderWindow* app) {
	app->draw(background);
	app->draw(name);
	app->draw(lv);
	for (auto& it : this->buttons)
	{
		it.second->render(app);
	}
}

vector<string> getListFileName(string directory) {
	DIR* dr;
	struct dirent* en;
	dr = opendir((directory + "/").c_str());
	vector<string> fileName;
	int trash = 0;
	if (dr) {
		while ((en = readdir(dr)) != NULL) {
			if (trash++ >= 2)
				fileName.push_back(en->d_name);
		}
		closedir(dr);
	}
	return fileName;
}