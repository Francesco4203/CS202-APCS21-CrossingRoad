#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
//#include "CANIMAL.h"
//#include "CPEOPLE.h"
//#include "CVEHICLE.h"
//#include "CGAME.h"
//#include "Header.h"
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;
using namespace sf;

const int WIDTH = 1500;
const int HEIGHT = 900;

#define max_menu 4
#define diff_menu 4
class CENEMY
{
protected:
    int type;//0 car, 1 truck, 2 bird, 3 dinausor
    int speed;//step per second, or seconds needed for 1 step
    bool isStop;
    Sprite object;
    Texture enemy;
    SoundBuffer _Bsound;
    Sound _sound;
public:
    void Move(bool reverse);
    void stop();
    void resume();
    Sprite getObject();
    void output(ofstream& f);
    void setPosition(double x, double y);
    void sound();
    int getSpeed();
    void setSpeed(int speed);
};

int CENEMY::getSpeed() {
    return speed;
}
void CENEMY::setSpeed(int speed) {
    this->speed = speed;
}

void CENEMY::sound() {
    _sound.play();
}

void CENEMY::setPosition(double x, double y) {
    object.setPosition(x, y);
}
void CENEMY::output(ofstream& f) {
    f << type << ' ' << speed << ' ' << isStop << ' ' << object.getPosition().x << ' ' << object.getPosition().y << '\n';
}
void CENEMY::stop() {
    isStop = true;
}
void CENEMY::resume() {
    isStop = false;
}
Sprite CENEMY::getObject() {
    return object;
}

void CENEMY::Move(bool reverse) {
    if (isStop) return;
    object.move((reverse ? -1 : 1) * (speed + 3) / 50.0, 0);
    if (object.getPosition().x >= 1500 && !reverse) {
        object.setPosition(-350, object.getPosition().y);
    }
    if (object.getPosition().x <= -200 && reverse) {
        object.setPosition(1500 + 350, object.getPosition().y);
    }
}

class CANIMAL : public CENEMY {

public:
    CANIMAL() = delete;//default NOT available
    CANIMAL(double x, double y, int mode, int randomFactor);
};

//Constructor set image for object

class CDINAUSOR : public CANIMAL {
    // image
public:
    CDINAUSOR() = delete;//default NOT available
    CDINAUSOR(int direction, double x, double y, int mode, int randomFactor);// 1 2 3 -> easy medium hard
};
class CBIRD : public CANIMAL {
    //image
public:
    CBIRD() = delete;//default NOT available
    CBIRD(int direction, double x, double y, int mode, int randomFactor);//1 2 3 -> easy medium hard;
};

CANIMAL::CANIMAL(double x, double y, int mode, int randomFactor) {
    speed = (mode == 1 ? 7 : (mode == 2 ? 10 : 13));
    isStop = 1;
    int shift = mode != 3 ? 900 + randomFactor : 400 + randomFactor;
    object.setPosition(x < 0 ? x + shift : x - shift, y);
    object.scale(0.3, 0.3);
}
CDINAUSOR::CDINAUSOR(int direction, double x, double y, int mode, int randomFactor) : CANIMAL(x, y, mode, randomFactor) {
    _Bsound.loadFromFile("Resource/Sound/dinausor.wav");
    _sound.setBuffer(_Bsound);
    if (direction == 2) enemy.loadFromFile("Resource/Rdinausor.png");
    else enemy.loadFromFile("Resource/dinausor.png");
    object.setTexture(enemy);
    type = 3;
}

CBIRD::CBIRD(int direction, double x, double y, int mode, int randomFactor) : CANIMAL(x, y, mode, randomFactor) {
    _Bsound.loadFromFile("Resource/Sound/bird.wav");
    _sound.setBuffer(_Bsound);
    if (direction == 2) enemy.loadFromFile("Resource/Rbird.png");
    else enemy.loadFromFile("Resource/bird.png");
    object.setTexture(enemy);
    type = 2;
}

class CVEHICLE : public CENEMY {
public:
    CVEHICLE() = delete;//default NOT available
    CVEHICLE(double x, double y, int mode, int randomFactor);
};

//Constructor set image for object

class CTRUCK : public CVEHICLE {
    // image
public:
    CTRUCK() = delete;//default NOT available
    CTRUCK(int direction, double x, double y, int mode, int randomFactor);//1 2 3 -> easy medium hard
};
class CCAR : public CVEHICLE {
    // image
public:
    CCAR() = delete;//default NOT available
    CCAR(int direction, double x, double y, int mode, int randomFactor);//1 2 3 -> easy medium hard
};

CVEHICLE::CVEHICLE(double x, double y, int mode, int randomFactor) {
    speed = (mode == 1 ? 7 : (mode == 2 ? 10 : 13));
    isStop = 1;
    int shift = mode != 3 ? 900 + randomFactor : 400 + randomFactor;
    object.setPosition(x < 0 ? x + shift : x - shift, y);
    object.scale(0.3, 0.3);
}

CTRUCK::CTRUCK(int direction, double x, double y, int mode, int randomFactor) : CVEHICLE(x, y, mode, randomFactor) {
    _Bsound.loadFromFile("Resource/Sound/truck.wav");
    _sound.setBuffer(_Bsound);
    if (direction == 2) enemy.loadFromFile("Resource/Rtruck.png");
    else enemy.loadFromFile("Resource/truck.png");
    object.setTexture(enemy);
    type = 1;
}

CCAR::CCAR(int direction, double x, double y, int mode, int randomFactor) : CVEHICLE(x, y, mode, randomFactor) {
    _Bsound.loadFromFile("Resource/Sound/car.wav");
    _sound.setBuffer(_Bsound);
    if (direction == 2) enemy.loadFromFile("Resource/Rcar.png");
    else enemy.loadFromFile("Resource/car.png");
    object.setTexture(enemy);
    type = 0;
}
class LIGHT {
private:
    string redPath = "Resource/red_light.png";
    string yellowPath = "Resource/yellow_light.png";
    string greenPath = "Resource/green_light.png";
    int time;
    int state;//1 red - 2 yellow - 3 green
    int red, yellow, green;//time of a state, 2-3s for yellow
    int mode;
    Texture red_light;
    Texture green_light;
    Texture yellow_light;
    Sprite light;
public:
    LIGHT() = delete;//default NOT available
    LIGHT(int mode);// 1 2 3 - easy medium hard

    int getTime();
    int getState();
    Sprite getSpriteLight();
    void changeLight();
    void setPosition(double x, double y);
    int getMode();
};


class LINE {
private:
    vector <CENEMY*> list;
    string lanePath = "Resource/lane.png";
    string grassPath = "Resource/grass.png";
    LIGHT light;
    int direction;//1 left --> right; 2 left <-- right
    Texture Tline;
    Sprite line;
    bool isLane;
public:
    LINE() = delete;//default NOT available
    LINE(int y, int dirction, bool isLane, int mode);// 1 2 3 - easy medium hard
    vector<CENEMY*> getVectorList() { return this->list; };
    LIGHT& getLight();
    Sprite getSpriteLine();
    void stop();
    void draw(sf::RenderWindow& window, pair<clock_t, clock_t>& time);
    void output(ofstream& f);
    int getMode();
    void setEnemy(vector<CENEMY*> enemyList);
    ~LINE();
};
int LIGHT::getMode() {
    return mode;
}
void LINE::setEnemy(vector<CENEMY*> enemyList) {
    for (int i = 0; i < list.size(); i++) delete list[i];
    list = enemyList;
}
int LINE::getMode() {
    return light.getMode();
}
void LINE::output(ofstream & f) {
    f << direction << ' ' << isLane << ' ' << list.size() << ' ' << getMode() << '\n';
    for (int i = 0; i < list.size(); i++) list[i]->output(f);
}
LINE::~LINE() {
    for (int i = 0; i < list.size(); i++) delete list[i];
}
LIGHT::LIGHT(int mode) {
    red_light.loadFromFile(redPath);
    yellow_light.loadFromFile(yellowPath);
    green_light.loadFromFile(greenPath);
    light.setTexture(green_light);
    light.scale(0.3, 0.3);
    time = 2 * (4 - mode);
    this->mode = mode;
    state = 3;
}

int LIGHT::getTime() {
    return time;
}
int LIGHT::getState() {
    return state;
}
Sprite LIGHT::getSpriteLight() {
    return light;
}

void LIGHT::changeLight() {
    if (state == 1) {
        state = 3;
        light.setTexture(green_light);
        time = 2 * (4 - mode) + rand() % 5;
        return;
    }
    if (state == 2) {
        state = 1;
        light.setTexture(red_light);
        time = 2 * (4 - mode) + rand() % 3;
        return;
    }
    time = 2 * (4 - mode);
    state = 2;
    light.setTexture(yellow_light);
}

void LIGHT::setPosition(double x, double y) {
    light.setPosition(x, y);
}

LINE::LINE(int y, int direction, bool isLane, int mode) : light(mode) {
    if (isLane) Tline.loadFromFile(lanePath);
    else Tline.loadFromFile(grassPath);
    this->isLane = isLane;
    line.setTexture(Tline);
    line.setPosition(0, y);
    this->direction = direction;
    int randomFactor = rand() % 200;
    if (direction == 1) {
        list.clear();
        int num = mode + 4;
        if (isLane) {
            CENEMY* enemy = NULL;
            while (num > 0) {
                int type = rand() % 2;
                if (type) enemy = new CCAR(direction, num * (-275), y, mode, randomFactor);
                else enemy = new CTRUCK(direction, num * (-275), y, mode, randomFactor);
                list.push_back(enemy);
                num--;
            }
        }
        else {
            CENEMY* enemy = NULL;
            while (num > 0) {
                int type = rand() % 2;
                if (type) enemy = new CBIRD(direction, num * (-250), y, mode, randomFactor);
                else enemy = new CDINAUSOR(direction, num * (-250), y, mode, randomFactor);
                list.push_back(enemy);
                num--;
            }
        }

        light.setPosition(WIDTH - 120, y - 30);
    }
    else {
        list.clear();
        int num = mode + 4;
        if (isLane) {
            CENEMY* enemy = NULL;
            while (num > 0) {
                int type = rand() % 2;
                if (type) enemy = new CCAR(direction, 1500 + num * 275, y, mode, randomFactor);
                else enemy = new CTRUCK(direction, 1500 + num * 275, y, mode, randomFactor);
                list.push_back(enemy);
                num--;
            }
        }
        else {
            CENEMY* enemy = NULL;
            while (num > 0) {
                int type = rand() % 2;
                if (type) enemy = new CBIRD(direction, 1500 + num * 250, y, mode, randomFactor);
                else enemy = new CDINAUSOR(direction, 1500 + num * 250, y, mode, randomFactor);
                list.push_back(enemy);
                num--;
            }
        }
        light.setPosition(-50, y - 30);
    }
}
class CPEOPLE {
    Vector2u _scale;
    IntRect _currentImage;
    Texture _Tplayer;
    Sprite _player;
    float _switchTime;
    float _totalTime;
    float _speed = 30;
    int _direction;
    bool _mState; //live - die
    friend class CGAME;
public:
    CPEOPLE(float switchTime, float speed);
    void move(float deltaTime);
    void update(int direction, float deltaTime);
    bool isImpact(LINE* a);
    bool isFinish(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void setPosition(double x, double y);
    void output(ofstream& f);
    Sprite& getSprite();
};
Sprite& CPEOPLE::getSprite() {
    return this->_player;
}
void CPEOPLE::output(ofstream& f) {
    f << _player.getPosition().x << ' ' << _player.getPosition().y << '\n';
}
void CPEOPLE::setPosition(double x, double y) {
    _player.setPosition(x, y);
}
CPEOPLE::CPEOPLE(float switchTime, float speed) {
    _Tplayer.loadFromFile("Resource/man.png");
    _currentImage.width = _Tplayer.getSize().x / 4;
    _currentImage.height = _Tplayer.getSize().y / 4;
    _player.setTexture(_Tplayer);
    _player.setTextureRect(_currentImage);
    _switchTime = switchTime;
    _speed = speed;
    _totalTime = 0;
    _scale.x = 0;
    _scale.y = 0;
}
void CPEOPLE::move(float deltaTime) {
    float dis = deltaTime * _speed;
    if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
        if (_player.getPosition().y - dis >= 0) _player.move(Vector2f(0, -dis));
        _direction = 3;
        update(_direction, deltaTime);
    }
    if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
        if (_player.getPosition().y + dis <= 700) _player.move(sf::Vector2f(0, dis));
        _direction = 0;
        update(_direction, deltaTime);
    }
    if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
        if (_player.getPosition().x - dis >= 0) _player.move(Vector2f(-dis, 0));
        _direction = 1;
        update(_direction, deltaTime);
    }
    if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
        if (_player.getPosition().x + dis <= 1450) _player.move(Vector2f(dis, 0));
        _direction = 2;
        update(_direction, deltaTime);
    }
}
void CPEOPLE::update(int direction, float deltaTime) {
    _scale.y = direction;
    _totalTime += deltaTime;
    if (_totalTime >= _switchTime) {
        _totalTime = 0;
        ++_scale.x;
        if (_scale.x == 4) {
            _scale.x = 0;
        }
    }
    _currentImage.left = _scale.x * _currentImage.width;
    _currentImage.top = _scale.y * _currentImage.height;
    _player.setTextureRect(_currentImage);
}
bool CPEOPLE::isFinish(sf::RenderWindow& window) {
    Texture Finish_line;
    Finish_line.loadFromFile("Resource/line.png");
    sf::Sprite line(Finish_line);
    line.scale(4, 0.1);
    line.setPosition(10, 10);
    window.draw(line);
    if (_player.getGlobalBounds().intersects(line.getGlobalBounds())) {
         return true;
    }
    return false;
}
void CPEOPLE::draw(sf::RenderWindow& window) {
    window.draw(this->_player);
}
bool CPEOPLE::isImpact(LINE* a) {
    for (int i = 0; i < a->getVectorList().size(); i++) {
        auto player_fix = _player.getGlobalBounds();
        if (a->getVectorList()[i]->getObject().getGlobalBounds().intersects(player_fix)) {
            a->getVectorList()[i]->sound();
            return true;
        }
    }
    return false;
}

LIGHT& LINE::getLight() { return light; }
Sprite LINE::getSpriteLine() { return line; }

void LINE::stop() {
    for (auto p : list) {
        p->stop();
    }
}

void LINE::draw(sf::RenderWindow& window, pair<clock_t, clock_t>& time) {
    time.second = clock();
    if ((time.second - time.first) / CLOCKS_PER_SEC >= light.getTime()) {
        light.changeLight();
        time.first = clock();
    }
    window.draw(line);

    for (auto p : list) {
        p->resume();
        if (this->getLight().getState() == 1 && isLane) p->stop();
        p->Move(direction == 2);
        window.draw(p->getObject());
    }

    if (isLane) window.draw(this->getLight().getSpriteLight());
}
class Menu
{
public:
    Menu(float w, float h);
    void draw(sf::RenderWindow& window, CPEOPLE a);
    void MenuSetting(sf::RenderWindow& window, CPEOPLE a);
    void moveUp();
    void moveDown();
    int selectedMenu();
    void changeMenu(int i);
    void OutputText(sf::RenderWindow& window, string s, int corX, int corY, sf::Color a, int scale);
    ~Menu();
private:
    int mainMenuSelected;
    int menuNumber;
    sf::Font font;
    sf::Text mainMenu[max_menu];
    sf::Text difficultyMenu[diff_menu];
};

class MenuSprite
{
private:
    sf::Texture menubgT;
    sf::Sprite menubgS;
public:
    MenuSprite();
    void drawBG(sf::RenderWindow& window);
    ~MenuSprite();
};

Menu::Menu(float w, float h)
{
    if (!font.loadFromFile("font/000OneTwoPunchBB-Regular.otf"))
    {
        std::cout << "no font loaded";
    }
    // New game
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(sf::Color::White);
    mainMenu[0].setString("New Game");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setPosition(sf::Vector2f(w / 2 + 100, (h - 300) / (max_menu + 1) + 100));
    // Load Game
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(sf::Color(255, 255, 255, 64));
    mainMenu[1].setString("Load Game");
    mainMenu[1].setCharacterSize(60);
    mainMenu[1].setPosition(sf::Vector2f(w / 2 + 100, (h - 300) / (max_menu + 1) * 2 + 150));
    // Setting
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(sf::Color(255, 255, 255, 64));
    mainMenu[2].setString("Setting");
    mainMenu[2].setCharacterSize(60);
    mainMenu[2].setPosition(sf::Vector2f(w / 2 + 100, (h - 300) / (max_menu + 1) * 3 + 200));

    // Quit
    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(sf::Color(255, 255, 255, 64));
    mainMenu[3].setString("Quit");
    mainMenu[3].setCharacterSize(60);
    mainMenu[3].setPosition(sf::Vector2f(w / 2 + 100, (h - 300) / (max_menu + 1) * 4 + 250));

    int dmoffset = 100;

    // Easy
    difficultyMenu[0].setFont(font);
    difficultyMenu[0].setFillColor(sf::Color::White);
    difficultyMenu[0].setString("Easy");
    difficultyMenu[0].setCharacterSize(35);
    difficultyMenu[0].setPosition(sf::Vector2f(w / 2 - 100, (h - 200) / (diff_menu + 1) + dmoffset));
    // Medium
    difficultyMenu[1].setFont(font);
    difficultyMenu[1].setFillColor(sf::Color(255, 255, 255, 64));
    difficultyMenu[1].setString("Medium");
    difficultyMenu[1].setCharacterSize(30);
    difficultyMenu[1].setPosition(sf::Vector2f(w / 2 - 100, (h - 200) / (diff_menu + 1) * 2 + dmoffset));
    // Hard
    difficultyMenu[2].setFont(font);
    difficultyMenu[2].setFillColor(sf::Color(255, 255, 255, 64));
    difficultyMenu[2].setString("Hard");
    difficultyMenu[2].setCharacterSize(30);
    difficultyMenu[2].setPosition(sf::Vector2f(w / 2 - 100, (h - 200) / (diff_menu + 1) * 3 + dmoffset));

    // Return
    difficultyMenu[3].setFont(font);
    difficultyMenu[3].setFillColor(sf::Color(255, 255, 255, 64));
    difficultyMenu[3].setString("Return");
    difficultyMenu[3].setCharacterSize(30);
    difficultyMenu[3].setPosition(sf::Vector2f(w / 2 - 100, (h - 200) / (diff_menu + 1) * 4 + dmoffset));

    Texture AWSD;
    /*AWSD.loadFromFile("Resource/Picture2.png");
    setting[0].setTexture(AWSD);
    setting[0].setPosition(0, 0);*/

    mainMenuSelected = 0;
    menuNumber = 0;
};
void Menu::OutputText(sf::RenderWindow& window, string s, int corX, int corY, sf::Color a, int scale) {
    Text cur;
    cur.setFont(font);
    cur.setFillColor(a);
    cur.setString(s);
    cur.setCharacterSize(scale);
    cur.setPosition(sf::Vector2f(corX, corY)); /* 800 - 600 = w/h*/
    window.draw(cur);
}
void Menu::MenuSetting(sf::RenderWindow& window, CPEOPLE a) {
    OutputText(window, "PRESS THE BUTTON TEST",600, 150, sf::Color::Black,30);
    OutputText(window, "GAME SETTING", 550, 50, sf::Color::White,70);
    Texture TAWSD, TW, TA, TS, TD, TL, PL, TSG, TAW, TWD, TAS, TSD;
    int cor_XK = 200, cor_XY = 200;
    TAWSD.loadFromFile("Resource/AWSD.png");
    TW.loadFromFile("Resource/keyboardW.png");
    TA.loadFromFile("Resource/keyboardA.png");
    TS.loadFromFile("Resource/keyboardS.png");
    TD.loadFromFile("Resource/keyboardD.png");
    TL.loadFromFile("Resource/L.png");
    TSG.loadFromFile("Resource/SaveGame.png");
    TAW.loadFromFile("Resource/AW.png");
    TWD.loadFromFile("Resource/WD.png");
    TAS.loadFromFile("Resource/AS.png");
    TSD.loadFromFile("Resource/SD.png");
    sf::Sprite AWSD, W, A, S, D, L, L2, SG, AW, WD, AS, SD;
    AWSD.setTexture(TAWSD);
    AWSD.setPosition(cor_XK, cor_XY);
    AWSD.setScale(0.2f, 0.2f);
    L.setTexture(TL);
    L.setPosition(cor_XK + 125, cor_XY + 250);
    L.setScale(0.2f, 0.2f);
    window.draw(L);
    window.draw(AWSD);
    a.setPosition(1100, 150);
    a.update(3, 0);
    a.getSprite().setScale(4, 4);
    float deltaTime = 0.0f;
    Clock clock;
    deltaTime = clock.restart().asSeconds();
    a.move(deltaTime);
    if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
        W.setTexture(TW);
        W.setPosition(cor_XK, cor_XY);
        W.setScale(0.2f, 0.2f);
        window.draw(W);
        //Move Up (we can another function for text only void OutputText(window, string))
    }
    if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
        S.setTexture(TS);
        S.setPosition(cor_XK, cor_XY);
        S.setScale(0.2f, 0.2f);
        window.draw(S);
    }
    if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
        A.setTexture(TA);
        A.setPosition(cor_XK, cor_XY);
        A.setScale(0.2f, 0.2f);
        window.draw(A);
    }
    if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
        D.setTexture(TD);
        D.setPosition(cor_XK, cor_XY);
        D.setScale(0.2f, 0.2f);
        window.draw(D);
    }
    if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A)) {
        OutputText(window, "MOVE UP LEFT", 700, 200, sf::Color::Black, 50);
        AW.setTexture(TAW);
        AW.setPosition(cor_XK, cor_XY);
        AW.setScale(0.2f, 0.2f);
        window.draw(AW);
    }
    else {
        if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D)) {
            OutputText(window, "MOVE UP RIGHT", 700, 200, sf::Color::Black, 50);
            WD.setTexture(TWD);
            WD.setPosition(cor_XK, cor_XY);
            WD.setScale(0.2f, 0.2f);
            window.draw(WD);
        }
        else {
            if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::S)) {
                OutputText(window, "MOVE DOWN LEFT", 700, 200, sf::Color::Black, 50);
                AS.setTexture(TAS);
                AS.setPosition(cor_XK, cor_XY);
                AS.setScale(0.2f, 0.2f);
                window.draw(AS);
            }
            else{
                if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) {
                    OutputText(window, "MOVE DOWN RIGHT", 700, 200, sf::Color::Black, 50);
                    SD.setTexture(TSD);
                    SD.setPosition(cor_XK, cor_XY);
                    SD.setScale(0.2f, 0.2f);
                    window.draw(SD);
                }
            }
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
        OutputText(window, "MOVE UP", 700, 200, sf::Color::Black,50);
    }
    else {
        if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
            OutputText(window, "MOVE DOWN", 700, 200, sf::Color::Black,50);
        }
        else {
            if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
                OutputText(window, "MOVE LEFT", 700, 200, sf::Color::Black,50);
            }
            else {
                if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {
                    OutputText(window, "MOVE Right", 700, 200, sf::Color::Black,50);
                }
            }
        }

    }
    if (Keyboard::isKeyPressed(Keyboard::L)) {
        PL.loadFromFile("Resource/KeyboardL.png");
        L2.setTexture(PL);
        L2.setPosition(cor_XK + 125, cor_XY + 250);
        L2.setScale(0.2f, 0.2f);
        SG.setTexture(TSG);
        SG.setPosition(750, cor_XY + 200);
        SG.setScale(0.3f, 0.3f);
        window.draw(L2);
        window.draw(SG);
    }
    a.draw(window);

}
void Menu::draw(sf::RenderWindow& window, CPEOPLE a)
{
    switch (menuNumber)
    {
    case 0: //main menu
        for (int i = 0; i < max_menu; i++)
        {
            window.draw(mainMenu[i]);
        }
        //cout << "menu1" << endl;
        break;
    case 1: //difficulty menu

        for (int i = 0; i < diff_menu; i++)
        {
            window.draw(difficultyMenu[i]);
        }
        break;
        //cout << "menu2" << endl;

    case 2: //setting
        MenuSetting(window, a);
        break;
    case 3: //game
        break;
    case 4: //load game
        break;
    }

};
void Menu::moveUp()
{
    switch (menuNumber)
    {
    case 0:
        if (mainMenuSelected - 1 >= -1) //check if not on the first item (new game)
        {
            mainMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 120)); //change the previous item's color
            mainMenu[mainMenuSelected].setCharacterSize(60); //change the previous item's size
            mainMenuSelected--; //move to the upper item
            if (mainMenuSelected == -1)
            {
                mainMenuSelected = max_menu - 1;
            }
            mainMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 255));	//change the new item's color
            mainMenu[mainMenuSelected].setCharacterSize(70); //change the new item's size
        }
        break;
    case 1:
        if (mainMenuSelected - 1 >= -1) //check if not on the first item (new game)
        {
            difficultyMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 120)); //change the pervious item's color
            difficultyMenu[mainMenuSelected].setCharacterSize(60);
            mainMenuSelected--; //move to the upper item
            if (mainMenuSelected == -1)
            {
                mainMenuSelected = diff_menu - 1;
            }
            difficultyMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 255));	//change the new item's color
            difficultyMenu[mainMenuSelected].setCharacterSize(70);
        }
        break;
    case 2: //setting
        break;
    case 3: //game
        break;
    case 4: //load game
        break;
    }
};
void Menu::moveDown()
{
    switch (menuNumber)
    {
    case 0:
        if (mainMenuSelected + 1 <= max_menu) //check if not on the last item (exit)
        {
            mainMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 120)); //change the pervious item's color
            mainMenu[mainMenuSelected].setCharacterSize(60); //change the previous item's size
            mainMenuSelected++; //move to the lower item
            if (mainMenuSelected == max_menu)
            {
                mainMenuSelected = 0;
            }
            mainMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 255));	//change the new item's color
            mainMenu[mainMenuSelected].setCharacterSize(70); //change the new item's size

        }
        break;
    case 1:
        if (mainMenuSelected + 1 <= diff_menu) //check if not on the last item (exit)
        {
            difficultyMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 120)); //change the pervious item's color
            difficultyMenu[mainMenuSelected].setCharacterSize(30);
            mainMenuSelected++; //move to the lower item
            if (mainMenuSelected == diff_menu)
            {
                mainMenuSelected = 0;
            }
            difficultyMenu[mainMenuSelected].setFillColor(sf::Color(255, 255, 255, 255));	//change the new item's color
            difficultyMenu[mainMenuSelected].setCharacterSize(35);
        }
        break;
    case 2: //setting
        break;
    case 3: //game
        break;
    case 4: //load game
        break;
    }
}

void Menu::changeMenu(int i)
{
    menuNumber = i;
}
int Menu::selectedMenu()
{
    return mainMenuSelected;
};
Menu::~Menu()
{

};

MenuSprite::MenuSprite()
{
    if (!menubgT.loadFromFile("texture/menubg.png"))
    {
        cout << "load failed" << endl;
        system("pause");
    }
    menubgS.setTexture(menubgT);
    menubgS.scale({ 1.88, 1.5 });
};

void MenuSprite::drawBG(sf::RenderWindow& window)
{
    window.draw(menubgS);
}

MenuSprite::~MenuSprite() {};
class CGAME {
    SoundBuffer BlevelUp;
    Sound levelUp;
    SoundBuffer Bsound;
    SoundBuffer BgameOverSound;
    Sound sound;
    vector<LINE*> map;
    vector<pair<clock_t, clock_t>> time;
    RenderWindow window;
    bool win, isPlaying;
    Sprite level;
    Texture levelImage;
    Text levelText;
    Font levelFont;
    Texture Tbackground;
    Sprite background;
    Texture TgameOver;
    Sprite gameOver;
    CPEOPLE Person = CPEOPLE(0.3f, 150.0f);
public:
    int mode;
    CGAME();
    void GameOver(sf::RenderWindow& window);
    void winGame(sf::RenderWindow& window);
    void menu();
    void gameSet();
    void newGame();
    void playGame();
    void output(ofstream& f);
    void input(ifstream& f);
    void loadGame();
};

void CGAME::loadGame() {
    ifstream f("Saved Game.txt");
    input(f);
}
void CGAME::input(ifstream& f) {
    f >> mode;
    int map_size;
    f >> map_size;
    levelText.setString("LEVEL " + to_string(mode));
    levelText.setFillColor(Color(255, 255, 0, 255));
    map.clear();
    for (int i = 0; i < 2 + mode; i++) {
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
    time = vector<pair<clock_t, clock_t>>(mode + 2);
    for (int i = 0; i < time.size(); i++) f >> time[i].first >> time[i].second;
    double x, y;
    f >> x >> y;
    Person.setPosition(x, y);
    Person.update(3, 0);
}
void CGAME::output(ofstream& f) {
    f << mode << ' ' << map.size() << '\n';
    for (int i = 0; i < map.size(); i++) map[i]->output(f);
    for (int i = 0; i < time.size(); i++) f << time[i].first << ' ' << time[i].second << '\n';
    Person.output(f);
}
CGAME::CGAME() {
    map.clear();
    mode = 1;
    window.create(VideoMode(WIDTH, HEIGHT), "Crossing Road Game!");
    win = 1;
    isPlaying = 0;
    levelImage.loadFromFile("Resource/level.png");
    level.setTexture(levelImage);
    level.setPosition(0, 800);
    levelFont.loadFromFile("font/000OneTwoPunchBB-Regular.otf");
    levelText.setFont(levelFont);
    levelText.setFillColor(Color(255, 255, 0, 255));
    levelText.setPosition(660, 800);
    levelText.scale(2.0, 2.0);
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
void CGAME::GameOver(sf::RenderWindow& window) {
    sound.setBuffer(BgameOverSound);
    sound.setLoop(false);
    sound.play();
    window.draw(gameOver);
}
void CGAME::winGame(sf::RenderWindow& window) {
    
}
void CGAME::menu() {
    int menuNumber = 0;
    Menu menu(800, 600);
    MenuSprite menusprite;
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
                            while (win) {
                                isPlaying = 1;
                                newGame();
                                mode++;
                                if (mode == 5 && win) winGame(window);
                                if (mode <= 3) levelText.setString("LEVEL " + to_string(mode));
                                else levelText.setString("CRAZY LEVEL");
                                while (window.pollEvent(event));
                                while (win == 0) {
                                    bool next = false;
                                    while (window.pollEvent(event)) {
                                        if (event.type == Event::KeyPressed) {
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
                            }
                            isPlaying = 0;
                            win = mode = 1;
                            break;
                        case 1: //load game
                            //insert code load game heres
                            loadGame();
                            while (win) {
                                isPlaying = 1;
                                playGame();
                                mode++;
                                if (mode == 5 && win) winGame(window);
                                if (mode <= 3) levelText.setString("LEVEL " + to_string(mode));
                                else levelText.setString("CRAZY LEVEL");
                                gameSet();
                                while (window.pollEvent(event));
                                while (win == 0) {
                                    bool next = false;
                                    while (window.pollEvent(event)) {
                                        if (event.type == Event::KeyPressed) {
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
                            }
                            isPlaying = 0;
                            win = mode = 1;
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
                        while (win) {
                            newGame();
                            mode = min(3, mode + 1);
                        }
                        break;
                    case 4: // load game
                        break;
                    }
                }
            }
        }
        window.clear();
        menusprite.drawBG(window);
        menu.draw(window,Person);
        window.display();
    }
}

void CGAME::newGame() {
    gameSet();
    playGame();
}
void CGAME::gameSet() {
    Person.setPosition(750, 700);
    Person.update(3, 0);
    if (mode <= 3) levelText.setString("LEVEL " + to_string(mode));
    else levelText.setString("CRAZY LEVEL");
    levelText.setFillColor(Color(255, 255, 0, 255));
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
void CGAME::playGame() {
    window.setFramerateLimit(700);
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
        }
        window.clear();
        window.draw(background);
        window.draw(level);
        window.draw(levelText);
        for (int i = 0; i < 2 + (mode > 3 ? 3 : mode); i++) {
            map[i]->draw(window, time[i]);
        }
        for (int i = 0; i < 2 + (mode > 3 ? 3 : mode); i++) {
            if (Person.isImpact(map[i])){
                win = 0;
                Person.draw(window);
                GameOver(window);
                window.display();
                return;
            }
        }
        if (Person.isFinish(window)) {
            levelUp.play();
            win = 1;
            return;
        }
        Person.draw(window);
        window.display();
        if (save) {
            ofstream f("Saved Game.txt");
            output(f);
            win = 0;
            return;
        }
    }
}
int main()
{
    srand(time(NULL));
    CGAME game;
    game.menu();
    return 0;
}