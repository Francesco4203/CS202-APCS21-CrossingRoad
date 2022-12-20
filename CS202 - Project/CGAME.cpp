﻿#include "CGAME.h"
using namespace std;
using namespace sf;
const int WIDTH = 1500;
const int HEIGHT = 900;
bool CGAME::loadGame() {
    ifstream f("Saved Game.txt");
    bool valid = input(f);
    f.close();
    if (valid) {
        ofstream fout("Saved Game.txt");
        fout.clear();
        fout << 0;
        fout.close();
        return true;
    }
    return false;
}
bool CGAME::input(ifstream& f) {
    int valid;
    f >> valid;
    if (!valid) return false;
    f >> mode;
    int map_size;
    f >> map_size;
    if (mode <= 3) levelText.setString("LEVEL " + to_string(mode));
    else levelText.setString("CRAZY LEVEL");
    levelText.setFillColor(Color(255, 255, 0, 255));
    for (int i = 0; i < map.size(); i++) delete map[i];
    map.clear();
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
                map[i]->getVectorList()[j]->setSpeed(map[i]->getVectorList()[j]->getSpeed() * 5);
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
    Person.setPosition(x, y);
    Person.update(3, 0);
    return true;
}
void CGAME::output(ofstream& f) {
    f << 1 << '\n';
    f << mode << ' ' << map.size() << '\n';
    for (int i = 0; i < map.size(); i++) map[i]->output(f);
    for (int i = 0; i < time.size(); i++) {
        f << time[i].second - time[i].first << '\n';
        f << map[i]->getLight().time << '\n';
        f << map[i]->getLight().state << '\n';
    }
    Person.output(f);
}
CGAME::CGAME() {
    for (int i = 0; i < map.size(); i++) delete map[i];
    map.clear();
    mode = 1;
    window.create(VideoMode(WIDTH, HEIGHT), "Crossing Road Game!");
    win = 1;
    isPlaying = 0;
    TlevelUp.loadFromFile("Resource/levelup.png");
    SlevelUp.setTexture(TlevelUp);
    SlevelUp.scale(1.0f, 1.0f);
    SlevelUp.setPosition(0, 0);
    levelImage.loadFromFile("Resource/Baselv.png");
    level.setTexture(levelImage);
    level.setPosition(0, 800);
    levelFont.loadFromFile("font/000OneTwoPunchBB-Regular.otf");
    levelText.setFont(levelFont);
    levelText.setFillColor(Color(255, 255, 0, 255));
    levelText.setPosition(900, 820);
    levelText.scale(1.3, 1.3);
    Tbackground.loadFromFile("Resource/background.png");
    background.setTexture(Tbackground);
    background.setPosition(0, 0);
    background.setScale(1.18, 1.11);
    BlevelUp.loadFromFile("Resource/Sound/levelUp.wav");
    BgameOverSound.loadFromFile("Resource/Sound/gameOver.wav");
    Bsound.loadFromFile("Resource/Sound/SugarCookie.wav");
    TgameOver.loadFromFile("Resource/Gameover2.png");
    gameOver.setTexture(TgameOver);
    gameOver.scale(1.0f, 1.0f);
    gameOver.setPosition(500, 200);
    levelUp.setBuffer(BlevelUp);
    sound.setBuffer(Bsound);
    sound.setLoop(true);
    sound.setVolume(70.f);
    sound.play();
    //levelText.setColor(Color(100, 100, 100, 100));
}

CGAME::~CGAME() {
    for (int i = 0; i < map.size(); i++) {
        delete map[i];
    }
    map.clear();
}

void CGAME::GameWin(sf::RenderWindow& window) {

}

void CGAME::GameOver(CENEMY* enemy, sf::RenderWindow& window) {
    sound.pause();
    float switchTime = 0.1f;
    float totalTime = 0;
    IntRect _currentImage;
    Vector2u _scale;
    Texture Texplosion;
    Sprite explosion;
    Texplosion.loadFromFile("Resource/explosion2.png");
    _currentImage.width = Texplosion.getSize().x / 4;
    _currentImage.height = Texplosion.getSize().y / 4;
    _scale.x = 0;
    _scale.y = 0;
    explosion.setTexture(Texplosion);
    explosion.setTextureRect(_currentImage);
    explosion.setPosition(Person.getSprite().getPosition().x - Person.getSprite().getGlobalBounds().width*2,
        Person.getSprite().getPosition().y - Person.getSprite().getGlobalBounds().height*2);
    float deltaTime = 0.0f;
    Clock clock;
    SoundBuffer Bexplosion;
    Sound Explosion;
    Bexplosion.loadFromFile("Resource/Sound/explosion.wav");
    Explosion.setBuffer(Bexplosion);
    Explosion.play();
    while (_scale.x != 4 && _scale.y != 4) {
        window.clear();
        window.draw(background);
        window.draw(level);
        window.draw(levelText);
        Texture Finish_line;
        Finish_line.loadFromFile("Resource/finish_line.png");
        sf::Sprite line(Finish_line);
        line.scale(1, 0.7);
        line.setPosition(0, 0);
        window.draw(line);
        for (int i = 0; i < 2 + (mode > 3 ? 3 : mode); i++) {
            window.draw(map[i]->getSpriteLine());
            for (int j = 0; j < map[i]->getVectorList().size(); ++j) {
                window.draw(map[i]->getVectorList()[j]->getObject());
            }
            if (map[i]->getIsLane()) window.draw(map[i]->getLight().getSpriteLight());
        }
        window.draw(explosion);
        deltaTime = clock.restart().asSeconds();
        totalTime += deltaTime;
        if (totalTime >= switchTime) {
            totalTime = 0;
            ++_scale.x;
            if (_scale.x == 4 && _scale.y != 3) {
                _scale.x = 0;
                ++_scale.y;
            }
            if (_scale.x == 4 && _scale.y == 3) {
                ++_scale.y;
            }
            if (_scale.x != 4 && _scale.y != 4) {
                _currentImage.left = _scale.x * _currentImage.width;
                _currentImage.top = _scale.y * _currentImage.height;
                explosion.setTextureRect(_currentImage);
                window.draw(explosion);
            }
            window.display();
        }
    }
    sound.setBuffer(BgameOverSound);
    sound.setLoop(false);
    sound.play();
    window.draw(gameOver);
}
void CGAME::menu() {
    int menuNumber = 0;
    Menu menu(1500, 900);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.moveUp();
                    break;
                case sf::Keyboard::Down:
                    menu.moveDown();
                    break;
                case sf::Keyboard::Enter:
                    //cout << "enter" << endl;
                    switch (menuNumber)
                    {
                    case 0: // main menu
                        switch (menu.selectedMenu())
                        {
                        case 0: //new game
                            gameSet();
                            playSession(event);
                            break;
                        case 1: //load game
                            //insert code load game heres
                            if (loadGame())
                                playSession(event);
                            break;
                        case 2: //setting
                            menuNumber = 2;
                            menu.changeMenu(2);
                            break;
                        case 3:
                            window.close();
                        }
                        break;
                    case 2: // setting
                        menuNumber = 0;
                        menu.changeMenu(0);
                        break;
                    case 3: // game

                        break;
                    case 4: // load game
                        break;
                    }
                }
            }
        }
        window.clear();
        menu.draw(window, Person);
        window.display();
    }
}

void CGAME::playSession(Event& event) {
    while (win && window.isOpen()) {
        isPlaying = 1;
        playGame();
        mode++;
        if (mode == 5 && win) GameWin(window);
        if (mode <= 3) levelText.setString("LEVEL " + to_string(mode));
        else levelText.setString("CRAZY LEVEL");
        while (win == 0) {
            bool next = false;
            while (window.pollEvent(event)) {
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                    next = true;
                    break;
                }
            }
            if (next) {
                sound.setBuffer(Bsound);
                sound.setLoop(true);
                sound.setVolume(70.f);
                sound.play();
                break;
            }
        }
        gameSet();
    }
    isPlaying = 0;
    win = mode = 1;
}
void CGAME::gameSet() {
    Person.setPosition(750, 700);
    Person.update(3, 0);
    if (mode <= 3) levelText.setString("LEVEL " + to_string(mode));
    else levelText.setString("CRAZY LEVEL");
    levelText.setFillColor(Color(255, 255, 0, 255));
    for (int i = 0; i < map.size(); i++) delete map[i];
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
                map[i]->getVectorList()[j]->setSpeed(map[i]->getVectorList()[j]->getSpeed() * 5);
            }
        }
    }
    time = vector<pair<clock_t, clock_t>>((mode > 3 ? 3 : mode) + 2);
    for (int i = 0; i < (mode > 3 ? 3 : mode) + 2; ++i) {
        time[i].first = clock() + rand() % 10 * CLOCKS_PER_SEC;
        time[i].second = clock() + rand() % 10 * CLOCKS_PER_SEC;
    }
}
void CGAME::playGame() {
    //window.setFramerateLimit(700);
    Clock clock;
    float deltaTime = 0.0f;
    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        Person.move(deltaTime);
        Event ev;
        bool save = 0;
        while (window.pollEvent(ev)) {
            if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::L) {
                save = 1;
                levelText.setString("GAME SAVED");
                levelText.setFillColor(Color(255, 0, 0, 255));
            }
            if (ev.type == Event::Closed) {
                window.close();
                break;
            }
        }
        window.clear();
        window.draw(background);
        window.draw(level);
        window.draw(levelText);
        for (int i = 0; i < 2 + (mode > 3 ? 3 : mode); i++) {
            map[i]->draw(window, time[i], deltaTime);
        }
        for (int i = 0; i < 2 + (mode > 3 ? 3 : mode); i++) {
            auto enemy = Person.isImpact(map[i]);
            if (enemy) {
                win = 0;
                Person.draw(window);
                GameOver(enemy ,window);
                window.display();
                return;
            }
        }
        if (Person.isFinish(window)) {
            window.draw(SlevelUp);
            levelUp.play();
            win = 1;
            window.display();
            Clock delay;
            delay.restart();
            while (delay.getElapsedTime().asSeconds() < 2.0f);
            return;
        }
        Person.draw(window);
        if (save) {
            window.display();
            saveGame();
            win = 0;
            return;
        }
        window.display();
    }
}
void CGAME::saveGame() {
    Font font;
    if (!font.loadFromFile("font/arial.ttf"))
    {
        std::cout << "no font loaded";
    }
    string getInput;
    Text inputFile;
    String inputText;
    inputFile.setFont(font);
    inputFile.setFillColor(Color::Red);
    Event ev;
    while (window.isOpen()) {
        bool done = false;
        while (window.pollEvent(ev)) {
            if (ev.type == Event::TextEntered) {
                if (ev.text.unicode == 13) {
                    done = true;
                    break;
                }
                else if (ev.text.unicode < 128) {
                    getInput += ev.text.unicode;
                    inputText += ev.text.unicode;
                    inputFile.setString(inputText);
                }
            }
            if (ev.type == Event::Closed) {
                window.close();
                break;
            }
        }
        window.clear();
        window.draw(inputFile);
        window.display();
        if (done) break;
    }
    ofstream f(getInput);
    output(f);
}