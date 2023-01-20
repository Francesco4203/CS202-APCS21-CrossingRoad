#include "GameState.h"
#include "SaveGameState.h"

GameState::GameState(RenderWindow* app, stack <State*>* states) : State(app, states) {
	this->mode = 1;
	isFinishGameOverScene = false;
	isPlaying = true;
	isWin = true;
	
	Tbackground.loadFromFile("Resource/background.png");
	background.setTexture(Tbackground);
	background.setPosition(0, 0);
	background.setScale(1.18, 1.11);

	TfinishLine.loadFromFile("Resource/finish_line.png");
	finishLine.setTexture(TfinishLine);
	finishLine.scale(1, 0.7);
	finishLine.setPosition(0, 0);

	TgameOver.loadFromFile("Resource/Gameover2.png");
	gameOverImage.setTexture(TgameOver);
	gameOverImage.scale(1.0f, 1.0f);
	gameOverImage.setPosition(500, 200);

	int vol;
	ifstream fin("Data/current_volume");
	fin >> vol;
	fin.close();

	BsoundGameOver.loadFromFile("Resource/Sound/gameOver.wav");
	soundGameOver.setBuffer(BsoundGameOver);
	soundGameOver.setVolume(vol*10);
	soundGameOver.setLoop(false);

	BsoundGame.loadFromFile("Resource/Sound/gameSound.wav");
	soundGame.setBuffer(BsoundGame);
	soundGame.setVolume(vol*10);
	soundGame.setLoop(true);
	soundGame.play();

	Texplosion.loadFromFile("Resource/explosion2.png");
	explosion.setTexture(Texplosion);
	_currentImageExplosion.width = Texplosion.getSize().x / 4;
	_currentImageExplosion.height = Texplosion.getSize().y / 4;
	_scaleExplosion.x = 0;
	_scaleExplosion.y = 0;
	explosion.setTextureRect(_currentImageExplosion);

	BsoundExplosion.loadFromFile("Resource/Sound/explosion.wav");
	soundExplosion.setBuffer(BsoundExplosion);
	soundExplosion.setVolume(vol*10);

	Tlevel.loadFromFile("Resource/Baselv.png");
	level.setTexture(Tlevel);
	level.setPosition(0, 780);

	levelFont.loadFromFile("font/astrolyt.ttf");

	levelText.setFont(levelFont);
	levelText.setFillColor(sf::Color(0, 200, 0));
	levelText.setPosition(700, 820);
	levelText.scale(1.3, 1.3);

	gameSet();
	start = clock();
	totalPauseTime = 0;

	nav = new Button("Resource/navigation_btn", 1500 - 910, 900 - 90, 60, 60, "navigation_btn", false);
	popup = NULL;
}
GameState::GameState(RenderWindow* app, stack <State*>* states, string directory) : State(app, states) {
	this->mode = 1;
	isFinishGameOverScene = false;
	isPlaying = true;
	isWin = true;

	Tbackground.loadFromFile("Resource/background.png");
	background.setTexture(Tbackground);
	background.setPosition(0, 0);
	background.setScale(1.18, 1.11);

	TfinishLine.loadFromFile("Resource/finish_line.png");
	finishLine.setTexture(TfinishLine);
	finishLine.scale(1, 0.7);
	finishLine.setPosition(0, 0);

	TgameOver.loadFromFile("Resource/Gameover2.png");
	gameOverImage.setTexture(TgameOver);
	gameOverImage.scale(1.0f, 1.0f);
	gameOverImage.setPosition(500, 200);

	int vol;
	ifstream fin("Data/current_volume");
	fin >> vol;
	fin.close();

	BsoundGameOver.loadFromFile("Resource/Sound/gameOver.wav");
	soundGameOver.setBuffer(BsoundGameOver);
	soundGameOver.setVolume(vol*10);
	soundGameOver.setLoop(false);

	BsoundGame.loadFromFile("Resource/Sound/gameSound.wav");
	soundGame.setBuffer(BsoundGame);
	soundGame.setVolume(vol*10);
	soundGame.setLoop(true);
	soundGame.play();

	Texplosion.loadFromFile("Resource/explosion2.png");
	explosion.setTexture(Texplosion);
	_currentImageExplosion.width = Texplosion.getSize().x / 4;
	_currentImageExplosion.height = Texplosion.getSize().y / 4;
	_scaleExplosion.x = 0;
	_scaleExplosion.y = 0;
	explosion.setTextureRect(_currentImageExplosion);

	BsoundExplosion.loadFromFile("Resource/Sound/explosion.wav");
	soundExplosion.setBuffer(BsoundExplosion);
	soundExplosion.setVolume(vol*10);

	Tlevel.loadFromFile("Resource/Baselv.png");
	level.setTexture(Tlevel);
	level.setPosition(0, 780);

	levelFont.loadFromFile("font/astrolyt.ttf");

	levelText.setFont(levelFont);
	levelText.setFillColor(sf::Color(0, 200, 0));
	levelText.setPosition(700, 820);
	levelText.scale(1.3, 1.3);

	loadGame(directory);

	nav = new Button("Resource/navigation_btn", 1500 - 910, 900 - 90, 60, 60, "navigation_btn", false);
	popup = NULL;
}
GameState::~GameState() {
	delete person;

	for (int i = 0; i < map.size(); i++) {
		delete map[i];
	}
	map.clear();

	delete nav;
	delete popup;
}

void GameState::gameSet() {
	person->setPosition(750, 700);
	person->update(3, 0);

	if (mode <= 3) levelText.setString("LEVEL " + to_string(mode));
	else levelText.setString("CRAZY LEVEL");
	levelText.setFillColor(Color(255, 255, 0, 255));
	for (int i = 0; i < map.size(); i++) {
		delete map[i];
	}
	map.clear();
	for (int i = 0; i < 2 + (mode > 3 ? 3 : mode); i++) {
		int isLane = rand() % 2;
		int direction = rand() % 2;
		int easier = rand() % 4;
		LINE* a = new LINE(50 + (mode == 1 ? 250 : (mode == 2 ? 175 : 150)) * i, direction + 1, isLane, min(3, mode + !easier));
		map.push_back(a);
	}
	if (mode > 3) {
		for (int i = 0; i < map.size(); ++i) {
			for (int j = 0; j < map[i]->getVectorList().size(); ++j) {
				map[i]->getVectorList()[j]->setSpeed(map[i]->getVectorList()[j]->getSpeed() * 2);
			}
		}
	}
	time = vector<pair<clock_t, clock_t>>((mode > 3 ? 3 : mode) + 2);
	for (int i = 0; i < (mode > 3 ? 3 : mode) + 2; ++i) {
		time[i].first = clock() + rand() % 10 * CLOCKS_PER_SEC;
		time[i].second = clock() + rand() % 10 * CLOCKS_PER_SEC;
	}
}

bool GameState::loadGame(string directory) {
	ifstream f(directory);
	bool isMan;
	f >> isMan;
	if (!isMan) person->setPeople(0.1f, 150.0f, 2);
	f >> mode;
	int map_size;
	f >> map_size;
	if (mode <= 3) levelText.setString("LEVEL " + to_string(mode));
	else levelText.setString("CRAZY LEVEL");
	levelText.setFillColor(Color(255, 255, 0, 255));

	for (int i = 0; i < 2 + (mode > 3 ? 3 : mode); i++) {
		int isLane, direction, list_size, laneMode;
		f >> direction >> isLane >> list_size >> laneMode;
		LINE* newLine = new LINE(50 + (mode == 1 ? 250 : (mode == 2 ? 175 : 150)) * i, direction, isLane, laneMode);
		vector<CENEMY*> list;
		for (int j = 0; j < list_size; j++) {
			CENEMY* a = 0;
			int type, speed, isStop;
			double x, y;
			f >> type >> speed >> isStop >> x >> y;
			if (type == 0) a = new CCAR(direction, x, y, laneMode, 0);
			else if (type == 1) a = new CTRUCK(direction, x, y, laneMode, 0);
			else if (type == 2) a = new CBIRD(direction, x, y, laneMode, 0);
			else if (type == 3) a = new CDINAUSOR(direction, x, y, laneMode, 0);
			if (isStop) a->stop();
			a->setPosition(x, y);
			list.push_back(a);
		}
		newLine->setEnemy(list);
		map.push_back(newLine);
	}
	if (mode > 3) {
		for (int i = 0; i < map.size(); ++i) {
			for (int j = 0; j < map[i]->getVectorList().size(); ++j) {
				map[i]->getVectorList()[j]->setSpeed(map[i]->getVectorList()[j]->getSpeed() * 2);
			}
		}
	}
	time = vector<pair<clock_t, clock_t>>((mode > 3 ? 3 : mode) + 2);
	for (int i = 0; i < time.size(); i++) {
		clock_t delta;
		f >> delta;
		time[i].first = clock();
		time[i].second = time[i].first + delta;
		int time, state;
		f >> time >> state;
		if (state == 2) map[i]->getLight().changeLight();
		if (state == 1) map[i]->getLight().changeLight(), map[i]->getLight().changeLight();
		map[i]->getLight().time = time;
	}
	double x, y;
	f >> x >> y;
	person->setPosition(x, y);
	person->update(3, 0);
	f >> start;
	f >> totalPauseTime;
	start = clock() - start;
	f.close();
	return true;
}

void GameState::endState() {
	quit = true;
}

void GameState::gameOver() {
	explosion.setPosition(person->getSprite().getPosition().x - 65,
		person->getSprite().getPosition().y - 60);
	
	totalTimeExplosion += delta_time;
	if (totalTimeExplosion >= switchTimeExplosion) {
		totalTimeExplosion = 0;
		++_scaleExplosion.x;
		if (_scaleExplosion.x == 4 && _scaleExplosion.y != 3) {
			_scaleExplosion.x = 0;
			++_scaleExplosion.y;
		}
		if (_scaleExplosion.x == 4 && _scaleExplosion.y == 3) {
			++_scaleExplosion.y;
		}
		if (_scaleExplosion.x != 4 && _scaleExplosion.y != 4) {
			_currentImageExplosion.left = _scaleExplosion.x * _currentImageExplosion.width;
			_currentImageExplosion.top = _scaleExplosion.y * _currentImageExplosion.height;
			explosion.setTextureRect(_currentImageExplosion);
		}
	}
}

bool GameState::isFinishExplosion() {
	if (_scaleExplosion.x == 4 && _scaleExplosion.y == 4) return true;
	return false;
}

void GameState::update() {

	this->updateMousePositions();
	if (!popup) {
		delta_time = timer.restart().asSeconds();
		person->move(delta_time);
		if (isPlaying) {
			nav->update(mousePosView);
			if (nav->isPressed()) {
				popup = new PopUpPauseGame(*person, mode);
				pauseTime = clock();
			}
			for (auto& it : map) {
				if (person->isImpact(it)) {
					for (int i = 0; i < 2 + (mode > 3 ? 3 : mode); i++) {
						map[i]->stopForever();
					}
					isWin = false;
					isPlaying = false;
					soundExplosion.play();
				}
			}
		}
		if (!isWin && !isFinishExplosion()) {
			gameOver();
		}
		if (!isPlaying && !isWin && isFinishGameOverScene && isFinishExplosion()) {
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				endState();
			}
		}
		if (person->isFinish(finishLine) && mode <= 3) {
			this->states->push(new LevelUpState(app, states, this->person->getIsMan()));
			mode++;
			gameSet();
		}
		if (person->isFinish(finishLine) && mode == 4) {
			soundGame.stop();
			this->states->push(new GameWinState(app, states, (clock() - start) / CLOCKS_PER_SEC - totalPauseTime));
			endState();
		}
	}
	else {
		for (int i = 0; i < 2 + (mode > 3 ? 3 : mode); i++) {
			map[i]->stopForever();
		}
		for (auto& it : this->popup->buttons)
		{
			it.second->update(this->mousePosView);
		}
		if (popup->buttons["back to menu"]->isPressed()) {
			endState();
		}
		if (popup->buttons["save game"]->isPressed()) {
			this->states->push(new SaveGameState(app, states, this));
			endState();
		}
		if (popup->buttons["exit"]->isPressed()) {
			delete popup;
			popup = NULL;
			totalPauseTime += (clock() - pauseTime) / CLOCKS_PER_SEC;
			for (int i = 0; i < 2 + (mode > 3 ? 3 : mode); i++) {
				map[i]->resume();
			}
		}
	}
}
void GameState::render() {
	app->draw(background);
	app->draw(finishLine);
	app->draw(level);
	app->draw(levelText);
	for (int i = 0; i < 2 + (mode > 3 ? 3 : mode); i++) {
		map[i]->draw(*app, time[i], delta_time);
	}
	person->draw(*app);
	if (!isWin) {
		if (soundGame.getStatus() != soundGame.Stopped) {
			soundGame.stop();
		}
		if (!isFinishExplosion()) app->draw(explosion);
		else {
			if (!isFinishGameOverScene && soundGameOver.getStatus() != soundGameOver.Playing) {
				soundGameOver.play();
				isFinishGameOverScene = true;
			}
			app->draw(gameOverImage);
		}
	}
	nav->render(app);
	if (popup) {
		popup->render(app);
	}
}

void GameState::resumeSound() {

}

PopUpPauseGame::PopUpPauseGame(CPEOPLE person, int mode) {
	texture.loadFromFile("Resource/menupopup.png");
	background.setTexture(texture);
	background.setPosition((1500 - 700) / 2, (900 - 320) / 2);

	person.update(0, 0.0f);
	this->person = person.getSprite();
	this->person.setPosition(background.getPosition().x + 260, background.getPosition().y + 100);

	font.loadFromFile("font/astrolyt.ttf");
	lv.setFont(font);
	lv.setFillColor(Color::White);
	lv.setPosition(this->person.getPosition().x + 50, this->person.getPosition().y + 20);
	string stringLv = "Level: ";
	if (mode <= 3) stringLv.push_back(mode + 48);
	else stringLv += "Crazy";
	lv.setString(stringLv);

	this->buttons["back to menu"] = new Button("Resource/navigation_btn/back_to_menu_btn", background.getPosition().x + 50, background.getPosition().y + 200, 283, 76, "back_to_menu_btn", false);
	this->buttons["save game"] = new Button("Resource/navigation_btn/save_game_btn", background.getPosition().x + 370, background.getPosition().y + 200, 283, 76, "save_game_btn", false);
	this->buttons["exit"] = new Button("Resource/navigation_btn/exit_btn", background.getPosition().x + 700 - 38, background.getPosition().y, 40, 40, "exit_btn", false);
}
PopUpPauseGame::~PopUpPauseGame() {
	for (auto& it : this->buttons)
	{
		delete it.second;
	}
}

void PopUpPauseGame::render(RenderWindow* app) {
	app->draw(background);
	app->draw(person);
	app->draw(lv);
	for (auto& it : this->buttons)
	{
		it.second->render(app);
	}
}