#include "SettingState.h"
#include <fstream>

PopUpPage1::PopUpPage1(bool isMan) {
	if (isMan) {
		texture.loadFromFile("Resource/Mch.png");
	}
	else {
		texture.loadFromFile("Resource/FMch.png");
	}
	background.setTexture(texture);
	background.setPosition(430, 450);
	background.setScale(0.3f, 0.3f);

	exit = new Button("Resource/sub_load_game_btn/pop_up_exit_btn", background.getPosition().x + 700 - 85, background.getPosition().y, 40, 40, "exit_btn", false);
}
PopUpPage1::~PopUpPage1() {
	delete exit;
}

void PopUpPage1::render(RenderWindow* app) {
	app->draw(background);
	exit->render(app);
}

SettingState1::SettingState1(RenderWindow* app, stack<State*>* states, Music* sound) :State(app, states) {
	texture.loadFromFile("Resource/BG.png");
	background.setTexture(texture);

	font.loadFromFile("font/astrolyt.ttf");
	title.setFont(font);
	title.setString("CHARACTER SELECTION");
	title.setPosition(270, 0);
	title.setFillColor(Color::White);
	title.setCharacterSize(70);

	this->sound = sound;

	this->buttons["man"] = new Button("Resource/sub_setting_btn/page1/man_btn", 410, 100, 216, 306, "man_btn", false);
	this->buttons["woman"] = new Button("Resource/sub_setting_btn/page1/woman_btn", 410 + 480, 100, 216, 306, "woman_btn", false);
	this->buttons["undo"] = new Button("Resource/sub_setting_btn/page1/undo_btn", 0, 900 - 60, 60, 60, "undo_btn", false);
	this->buttons["redo"] = new Button("Resource/sub_setting_btn/page1/redo_btn", 80, 900 - 60, 60, 60, "redo_btn", false);
	
	popup = NULL;
}
SettingState1::~SettingState1() {
	for (auto& it : this->buttons)
	{
		delete it.second;
	}
	if (popup) 
	delete popup;
}

void SettingState1::resumeSound() {

}
void SettingState1::endState() {
	quit = true;
}

void SettingState1::update() {
	this->updateMousePositions();
	if (!popup) {
		for (auto& it : buttons) {
			it.second->update(mousePosView);
		}
		if (this->buttons["man"]->isPressed()) {
			popup = new PopUpPage1(true);
			ofstream fout("Data/character_path");
			fout << "Resource/man.png";
			fout.close();
		}
		if (this->buttons["woman"]->isPressed()) {
			popup = new PopUpPage1(false);
			ofstream fout("Data/character_path");
			fout << "Resource/woman.png";
			fout.close();
		}
		if (this->buttons["undo"]->isPressed()) {
			endState();
		}
		if (this->buttons["redo"]->isPressed()) {
			states->push(new SettingState2(app, states, sound));
		}
	}
	else {
		popup->exit->update(mousePosView);
		if (popup->exit->isPressed()) {
			delete popup;
			popup = NULL;
		}
	}
}
void SettingState1::render() {
	app->draw(background);
	app->draw(title);

	for (auto& it : buttons) {
		it.second->render(app);
	}

	if (popup) {
		popup->render(app);
	}
}

SettingState2::SettingState2(RenderWindow* app, stack<State*>* states, Music* sound) : State(app, states) {
	texture.loadFromFile("Resource/BG.png");
	background.setTexture(texture);

	font.loadFromFile("font/astrolyt.ttf");
	title.setFont(font);
	title.setString("GAME SETTING");
	title.setPosition(450, 0);
	title.setFillColor(Color::White);
	title.setCharacterSize(70);
	subTitle.setFont(font);
	subTitle.setString("PRESS THE BUTTON TO TEST");
	subTitle.setPosition(500, 100);
	subTitle.setFillColor(Color::Black);
	subTitle.setCharacterSize(30);
	description.setFont(font);
	description.setString("");
	description.setPosition(700, 200);
	description.setFillColor(Color(121, 162, 107));
	description.setCharacterSize(30);

	TAWSD.loadFromFile("Resource/AWSD.png");
	TW.loadFromFile("Resource/keyboardW.png");
	TA.loadFromFile("Resource/keyboardA.png");
	TS.loadFromFile("Resource/keyboardS.png");
	TD.loadFromFile("Resource/keyboardD.png");
	TAW.loadFromFile("Resource/AW.png");
	TWD.loadFromFile("Resource/WD.png");
	TAS.loadFromFile("Resource/AS.png");
	TSD.loadFromFile("Resource/SD.png");
	TZX.loadFromFile("Resource/XZ.png");
	TPZ.loadFromFile("Resource/PZX.png");
	TPX.loadFromFile("Resource/PXZ.png");
	TC.loadFromFile("Resource/C.png");
	TPC.loadFromFile("Resource/CP.png");
	
	AWSD.setTexture(TAWSD);
	AWSD.setPosition(cor_XK, cor_XY);
	AWSD.setScale(0.2f, 0.2f);
	XZ.setTexture(TZX);
	XZ.setScale(0.2f, 0.2f);
	XZ.setPosition(cor_XK - 50, cor_XY + 380);
	C.setTexture(TC);
	C.setScale(0.2f, 0.2f);
	C.setPosition(cor_XK + 300, cor_XY + 380);

	PZ.setTexture(TPZ);
	PZ.setScale(0.0f, 0.0f);
	PZ.setPosition(cor_XK - 50, cor_XY + 380);
	PX.setTexture(TPX);
	PX.setScale(0.0f, 0.0f);
	PX.setPosition(cor_XK - 50, cor_XY + 380);
	PC.setTexture(TPC);
	PC.setScale(0.0f, 0.0f);
	PC.setPosition(cor_XK + 300, cor_XY + 380);
	W.setTexture(TW);
	W.setPosition(cor_XK, cor_XY);
	W.setScale(0.0f, 0.0f);	
	S.setTexture(TS);
	S.setPosition(cor_XK, cor_XY);
	S.setScale(0.0f, 0.0f);
	A.setTexture(TA);
	A.setPosition(cor_XK, cor_XY);
	A.setScale(0.0f, 0.0f);
	D.setTexture(TD);
	D.setPosition(cor_XK, cor_XY);
	D.setScale(0.0f, 0.0f);
	
	Tvolume.loadFromFile("Resource/volume_bar_animation.png");
	volume.setTexture(Tvolume);
	_currentImage.width = Tvolume.getSize().x / 11;
	_currentImage.height = Tvolume.getSize().y;
	ifstream fin("Data/current_volume");
	fin >> _scale.x;
	fin.close();
	_scale.y = 0;
	_currentImage.left = _scale.x * _currentImage.width;
	_currentImage.top = _scale.y * _currentImage.height;
	volume.setTextureRect(_currentImage);
	volume.setPosition(700, 600);

	person->setPosition(1000, 150);
	person->update(0, 0);
	person->getSprite().setScale(4, 4);

	this->sound = sound;

	this->buttons["undo"] = new Button("Resource/sub_setting_btn/page1/undo_btn", 0, 900 - 60, 60, 60, "undo_btn", false);
	this->buttons["redo"] = new Button("Resource/sub_setting_btn/page1/redo_btn", 80, 900 - 60, 60, 60, "redo_btn", false);
}
SettingState2::~SettingState2() {
	for (auto& it : this->buttons)
	{
		delete it.second;
	}
	delete person;
}

void SettingState2::resumeSound() {

}
void SettingState2::endState() {
	quit = true;
}

void SettingState2::update() {
	this->updateMousePositions();
	for (auto& it : buttons) {
		it.second->update(mousePosView);
	}
	if (this->buttons["undo"]->isPressed()) {
		endState();
	}
	if (this->buttons["redo"]->isPressed()) {
		this->states->push(new SettingState3(app, states));
	}

	while (app->pollEvent(ev))
	{
		if (ev.type == Event::KeyPressed) {
			if (ev.key.code == Keyboard::Z && _scale.x > 1) {
				PZ.setScale(0.2f, 0.2f);
				_scale.x--;
				_currentImage.left = _scale.x * _currentImage.width;
				volume.setTextureRect(_currentImage);

				ofstream fout("Data/current_volume");
				fout << _scale.x;
				fout.close();
				
				sound->setVolume(_scale.x * 10);
			}
			if (Keyboard::isKeyPressed(Keyboard::X) && _scale.x < 10) {
				PX.setScale(0.2f, 0.2f);
				_scale.x++;
				_currentImage.left = _scale.x * _currentImage.width;
				volume.setTextureRect(_currentImage);

				ofstream fout("Data/current_volume");
				fout << _scale.x;
				fout.close();

				sound->setVolume(_scale.x * 10);
			}
			if (Keyboard::isKeyPressed(Keyboard::C)) {
				PC.setScale(0.2f, 0.2f);
				_scale.x = 0;
				_currentImage.left = _scale.x * _currentImage.width;
				volume.setTextureRect(_currentImage);

				ofstream fout("Data/current_volume");
				fout << _scale.x;
				fout.close();

				sound->setVolume(0);
			}

			if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
				W.setScale(0.2f, 0.2f);

				description.setString("MOVE UP");
				description.setFillColor(Color::Black);
				person->update(3, 0);
			}
			if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
				S.setTexture(TS);
				S.setPosition(cor_XK, cor_XY);
				S.setScale(0.2f, 0.2f);

				description.setString("MOVE DOWN");
				description.setFillColor(Color::Black);
				person->update(0, 0);
			}
			if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
				A.setTexture(TA);
				A.setPosition(cor_XK, cor_XY);
				A.setScale(0.2f, 0.2f);

				description.setString("MOVE LEFT");
				description.setFillColor(Color::Black);
				person->update(1, 0);
			}
			if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
				D.setTexture(TD);
				D.setPosition(cor_XK, cor_XY);
				D.setScale(0.2f, 0.2f);

				description.setString("MOVE RIGHT");
				description.setFillColor(Color::Black);
				person->update(2, 0);
			}
		}
		if (ev.type == Event::KeyReleased) {
			if (ev.key.code == Keyboard::Z) {
				PZ.setScale(0.0f, 0.0f);
			}
			if (ev.key.code == Keyboard::X) {
				PX.setScale(0.0f, 0.0f);
			}
			if (ev.key.code == Keyboard::C) {
				PC.setScale(0.0f, 0.0f);
			}
			if (ev.key.code == Keyboard::W || ev.key.code == Keyboard::Up) {
				W.setScale(0.0f, 0.0f);
				description.setFillColor(Color(121, 162, 107));
				person->update(0, 0);
			}
			if (ev.key.code == Keyboard::S || ev.key.code == Keyboard::Down) {
				S.setScale(0.0f, 0.0f);
				description.setFillColor(Color(121, 162, 107));
				person->update(0, 0);
			}
			if (ev.key.code == Keyboard::A || ev.key.code == Keyboard::Left) {
				A.setScale(0.0f, 0.0f);
				description.setFillColor(Color(121, 162, 107));
				person->update(0, 0);
			}
			if (ev.key.code == Keyboard::D || ev.key.code ==  Keyboard::Right) {
				D.setScale(0.0f, 0.0f);
				description.setFillColor(Color(121, 162, 107));
				person->update(0, 0);
			}
		}
	}
}
void SettingState2::render() {
	app->draw(background);
	app->draw(title);
	app->draw(subTitle);
	app->draw(description);
	app->draw(XZ);
	app->draw(AWSD);
	app->draw(C);
	person->draw(*app);
	app->draw(volume);
	app->draw(PZ);
	app->draw(PX);
	app->draw(PC);
	app->draw(W);
	app->draw(S);
	app->draw(A);
	app->draw(D);
	for (auto& it : buttons) {
		it.second->render(app);
	}
}

SettingState3::SettingState3(RenderWindow* app, stack<State*>* states) : State(app, states) {
	texture.loadFromFile("Resource/BG.png");
	background.setTexture(texture);

	Trule.loadFromFile("Resource/Setting_Page2.png");
	rule.setTexture(Trule);
	rule.setPosition(150, 120);
	rule.setScale(0.4f, 0.4f);

	font.loadFromFile("font/astrolyt.ttf");
	title.setFont(font);
	title.setFillColor(Color::White);
	title.setPosition(500, 0);
	title.setCharacterSize(70);
	title.setString("GAME RULE");

	undo = new Button("Resource/sub_setting_btn/page1/undo_btn", 0, 900 - 60, 60, 60, "undo_btn", false);
}
SettingState3::~SettingState3() {
	delete undo;
}

void SettingState3::resumeSound() {

}
void SettingState3::endState() {
	quit = true;
}

void SettingState3::update() {
	this->updateMousePositions();
	undo->update(mousePosView);
	if(undo->isPressed()) endState();
}
void SettingState3::render() {
	app->draw(background);
	app->draw(rule);
	app->draw(title);
	undo->render(app);
}