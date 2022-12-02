#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
//#include "CANIMAL.h"
//#include "CPEOPLE.h"
//#include "CVEHICLE.h"
//#include "CGAME.h"
#include "Header.h"
#include <ctime>

using namespace std;
using namespace sf;

const int WIDTH = 1500;
const int HEIGHT = 800;

class CENEMY
{
protected:
    int speed;//step per second, or seconds needed for 1 step
    bool isStop;
    Sprite object;
    Texture enemy;
public:
    void Move(bool reverse);
    void stop();
    void resume();
    Sprite getObject();
};

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
    CANIMAL(int x, int y, int mode);
};

//Constructor set image for object

class CDINAUSOR : public CANIMAL {
    // image
public:
    CDINAUSOR() = delete;//default NOT available
    CDINAUSOR(int x, int y, int mode);// 1 2 3 -> easy medium hard
};
class CBIRD : public CANIMAL {
    //image
public:
    CBIRD() = delete;//default NOT available
    CBIRD(int x, int y, int mode);//1 2 3 -> easy medium hard;
};

CANIMAL::CANIMAL(int x, int y, int mode) {
    speed = (mode == 1 ? 7 : (mode == 2 ? 10 : 13));
    isStop = 1;
    object.setPosition(x, y);
    object.scale(0.3, 0.3);
}
CDINAUSOR::CDINAUSOR(int x, int y, int mode) : CANIMAL(x, y, mode) {
    if (x > 0) enemy.loadFromFile("Resource/Rdinausor.png");
    else enemy.loadFromFile("Resource/dinausor.png");
    object.setTexture(enemy);
}

CBIRD::CBIRD(int x, int y, int mode) : CANIMAL(x, y, mode) {
    if (x > 0) enemy.loadFromFile("Resource/Rbird.png");
    else enemy.loadFromFile("Resource/bird.png");
    object.setTexture(enemy);
}

class CVEHICLE : public CENEMY {
public:
    CVEHICLE() = delete;//default NOT available
    CVEHICLE(int x, int y, int mode);
};

//Constructor set image for object

class CTRUCK : public CVEHICLE {
    // image
public:
    CTRUCK() = delete;//default NOT available
    CTRUCK(int x, int y, int mode);//1 2 3 -> easy medium hard
};
class CCAR : public CVEHICLE {
    // image
public:
    CCAR() = delete;//default NOT available
    CCAR(int x, int y, int mode);//1 2 3 -> easy medium hard
};

CVEHICLE::CVEHICLE(int x, int y, int mode) {
    speed = (mode == 1 ? 7 : (mode == 2 ? 10 : 13));
    isStop = 1;
    object.setPosition(x, y);
    object.scale(0.3, 0.3);
}
CTRUCK::CTRUCK(int x, int y, int mode) : CVEHICLE(x, y, mode) {
    if (x > 0) enemy.loadFromFile("Resource/Rtruck.png");
    else enemy.loadFromFile("Resource/truck.png");
    object.setTexture(enemy);
}

CCAR::CCAR(int x, int y, int mode) : CVEHICLE(x, y, mode) {
    if (x > 0) enemy.loadFromFile("Resource/Rcar.png");
    else enemy.loadFromFile("Resource/car.png");
    object.setTexture(enemy);
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
    void setPosition(int x, int y);
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

public:
    LINE() = delete;//default NOT available
    LINE(int y, int dirction, bool isLane, int mode);// 1 2 3 - easy medium hard
    vector<CENEMY*> getVectorList() { return this->list; };
    LIGHT& getLight();
    Sprite getSpriteLine();
    void stop();
    void draw(sf::RenderWindow& window, pair<clock_t, clock_t>& time);
};

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

void LIGHT::setPosition(int x, int y) {
    light.setPosition(x, y);
}

LINE::LINE(int y, int direction, bool isLane, int mode) : light(mode) {
    if (isLane) Tline.loadFromFile(lanePath);
    else Tline.loadFromFile(grassPath);

    line.setTexture(Tline);
    line.setPosition(0, y);
    this->direction = direction;
    if (direction == 1) {
        list.clear();
        int num = mode + 3;
        if (isLane) {
            CVEHICLE* vehicle = NULL;
            while (num > 0) {
                int type = rand() % 2;
                if (type) vehicle = new CCAR(num * (-250), y, mode);
                else vehicle = new CTRUCK(num * (-250), y, mode);
                list.push_back(vehicle);
                num--;
            }
        }
        else {
            CANIMAL* animal = NULL;
            while (num > 0) {
                int type = rand() % 2;
                if (type) animal = new CBIRD(num * (-250), y, mode);
                else animal = new CDINAUSOR(num * (-250), y, mode);
                list.push_back(animal);
                num--;
            }
        }

        light.setPosition(WIDTH - 120, y - 30);
    }
    else {
        list.clear();
        int num = mode + 3;
        if (isLane) {
            CVEHICLE* vehicle = NULL;
            while (num > 0) {
                int type = rand() % 2;
                if (type) vehicle = new CCAR(1500 + num * 250, y, mode);
                else vehicle = new CTRUCK(1500 + num * 250, y, mode);
                list.push_back(vehicle);
                num--;
            }
        }
        else {
            CENEMY* enemy = NULL;
            while (num > 0) {
                int type = rand() % 2;
                if (type) enemy = new CBIRD(1500 + num * 250, y, mode);
                else enemy = new CDINAUSOR(1500 + num * 250, y, mode);
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
};

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
    _player.setPosition(750, 700);
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
        if (_player.getGlobalBounds().intersects(a->getVectorList()[i]->getObject().getGlobalBounds())) {
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
        if (this->getLight().getState() == 1) p->stop();
        p->Move(direction == 2);
        window.draw(p->getObject());
    }

    window.draw(this->getLight().getSpriteLight());
}
class CGAME {
    vector<LINE*> map;
    vector<pair<clock_t, clock_t>> time;
    RenderWindow window;
    bool win, isPlaying;
public:
    int mode;
    CGAME();
    void menu();
    void gameSet();
    void newGame();
    void playGame();
};
CGAME::CGAME() {
    map.clear();
    mode = 1;
    window.create(VideoMode(1500, 800), "Crossing Road Game!");
    win = 1;
    isPlaying = 0;
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
                                mode = min(3, mode + 1);
                            }
                            while (window.pollEvent(event));
                            isPlaying = 0;
                            win = mode = 1;
                            break;
                        case 1: //load game
                            //insert code load game here
                            menuNumber = 4;
                            menu.changeMenu(4);
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
        menu.draw(window);
        window.display();
    }
}
void CGAME::newGame() {
    gameSet();
    playGame();
}
void CGAME::gameSet() {
    map.clear();
    for (int i = 0; i < 2 + mode; i++) {
        int isLane = rand() % 2;
        int direction = rand() % 2;
        int easier = rand() % 4;
        LINE* a = new LINE(50 + 150 * i, direction + 1, isLane, min(3, mode + !easier));
        map.push_back(a);
    }
    time = vector<pair<clock_t, clock_t>>(mode + 2);
    for (int i = 0; i < mode + 2; ++i) {
        time[i].first = clock() + rand() % 10 * CLOCKS_PER_SEC;
        time[i].second = clock() + rand() % 10 * CLOCKS_PER_SEC;
    }
    for (int i = 0; i < 2 + mode; i++) {
        int isLane = rand() % 2;
        int direction = rand() % 2;
        int easier = rand() % 4;
        LINE* a = new LINE(50 + 150 * i, direction + 1, isLane, min(3, mode + !easier));
        map.push_back(a);
    }
}
void CGAME::playGame() {
    //window.setFramerateLimit(700);
    CPEOPLE Person(0.3f, 150.0f);
    Clock clock;
    float deltaTime = 0.0f;
    while (window.isOpen() && isPlaying) {
        deltaTime = clock.restart().asSeconds();
        Person.move(deltaTime);
        window.clear();
        for (int i = 0; i < 2 + mode; i++) {
            map[i]->draw(window, time[i]);
        }
        for (int i = 0; i < 2 + mode; i++) {
            if (Person.isImpact(map[i])){
                win = 0;
                return;
            }
        }
        if (Person.isFinish(window)) {
            win = 1;
            return;
        }
        Person.draw(window);
        window.display();
    }
}
int main()
{
    srand(time(NULL));
    CGAME game;
    game.mode = 1;
    game.menu();
    return 0;
}