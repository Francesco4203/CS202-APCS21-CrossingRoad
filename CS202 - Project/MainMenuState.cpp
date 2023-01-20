#include "MainMenuState.h"

void MainMenuState::initBackground()
{
    this->texture.loadFromFile("Resource/BG1.png");
    this->background.setTexture(texture);
}

void MainMenuState::initButtons()
{
    this->buttons["NEW_GAME_BTN"] = new Button("Resource/new_game_btn", (app->getSize().x - 299.0) / 2, 500, 299, 60, "new_game_btn", false);
    this->buttons["LOAD_GAME_BTN"] = new Button("Resource/load_game_btn", (app->getSize().x - 299.0) / 2, 560, 299, 60, "load_game_btn", false);
    this->buttons["SETTING_BTN"] = new Button("Resource/setting_btn", (app->getSize().x - 299.0) / 2, 620, 299, 60, "setting_btn", false);
    this->buttons["HIGHSCORE_BTN"] = new Button("Resource/highscore_btn", (app->getSize().x - 299.0) / 2, 680, 299, 60, "highscore_btn", false);
    this->buttons["QUIT_BTN"] = new Button("Resource/quit_btn", (app->getSize().x - 299.0) / 2, 740, 299, 60, "quit_btn", false);
}

void MainMenuState::initSounds()
{
    int vol;
    ifstream fin("Data/current_volume");
    fin >> vol;
    fin.close();

    if (!this->theme.openFromFile("Resource/Sound/SugarCookie.wav"))
        cout << "COULD NOT LOAD THEME MUSIC" << endl;
    this->theme.setLoop(true);
    this->theme.setVolume(vol*10);
    this->theme.play();
}

MainMenuState::MainMenuState(RenderWindow* app, stack<State*>* states)
    :State(app, states)
{
    this->initBackground();
    this->initButtons();
    this->initSounds();
}
MainMenuState ::~MainMenuState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

void MainMenuState::endState() {

}

void MainMenuState::updateButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }
    if (this->buttons["NEW_GAME_BTN"]->isPressed())
    {
        this->theme.stop();
        this->states->push(new GameState(this->app, this->states));
    }
    
    if (this->buttons["LOAD_GAME_BTN"]->isPressed())
    {
        this->theme.pause();
        this->states->push(new LoadGameState(app, states));
    }

    if (this->buttons["SETTING_BTN"]->isPressed())
    {
        this->states->push(new SettingState1(app, states, &theme));
    }

    if (this->buttons["HIGHSCORE_BTN"]->isPressed())
    {
        theme.pause();
        this->states->push(new HighscoreState(this->app, this->states));
    }

    if (this->buttons["QUIT_BTN"]->isPressed())
    {
        this->app->close();
    }

}

void MainMenuState::update()
{
    this->updateMousePositions();
    this->updateButtons();
}

void MainMenuState::resumeSound() {
    theme.play();
}

void MainMenuState::renderButtons()
{
    for (auto& it : this->buttons)
    {
        it.second->render(app);
    }
}

void MainMenuState::render()
{
    app->draw(this->background);
    this->renderButtons();
}