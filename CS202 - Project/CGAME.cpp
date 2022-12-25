#include "CGAME.h"
using namespace std;
using namespace sf;
const int WIDTH = 1500;
const int HEIGHT = 900;
string CGAME::textBox(Sprite& bg) {
    Font font;
    if (!font.loadFromFile("font/arial.ttf"))
    {
        std::cout << "no font loaded";
    }
    string getInput;
    Text inputFile;
    String inputText;
    inputFile.setFont(font);
    inputFile.scale(1.5, 1.5);
    inputFile.setFillColor(Color::Red);
    inputFile.setPosition(350, 580);
    Event ev;
    while (window.pollEvent(ev));
    int maxChar = 30;
    while (window.isOpen()) {
        bool done = false;
        while (window.pollEvent(ev)) {
            if (ev.type == Event::TextEntered) {
                if (ev.text.unicode == 13) { //enter
                    done = true;
                    break;
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
            if (ev.type == Event::Closed) {
                window.close();
                break;
            }
        }
        window.clear();
        window.draw(bg);
        window.draw(inputFile);
        window.display();
        if (done) break;
    }
    return getInput;
}
bool CGAME::loadGame() {
    auto fileList = getFileName("Saved Game");
    //string getTextBox = textBox(backgroundLoad);
    Font font;
    font.loadFromFile("font/arial.ttf");
    Texture Tbg;
    Sprite bg;
    Tbg.loadFromFile("Resource/select.png");
    bg.setTexture(Tbg);    
    int cur = 0, n = fileList.size();
    int display_size = 6;
    int left = 0, right = min(5, n - 1);
    vector<Text> select(display_size);
    for (int i = 0; i < display_size; i++) {
        select[i].setFont(font);
        select[i].setCharacterSize(50);
        select[i].setFillColor(Color::Yellow);
        select[i].setPosition(700, 250 + i * 100);
        select[i].setString("abcde");
    }
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                break;
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Down) cur = min(n - 1, cur + 1);
                else if (event.key.code == Keyboard::Up) cur = max(0, cur - 1);
                else if (event.key.code == Keyboard::Enter) {
                    if (n) {
                        ifstream f("Saved Game/" + fileList[cur]);
                        input(f);
                        f.close();
                        remove(fileList[cur].c_str());
                        return true;
                    }
                }
                else if (event.key.code == Keyboard::Escape) return false;
            }
        }
        window.clear();
        window.draw(bg);
        if (n) {
            if (cur > right) left++, right++;
            if (cur < left) left--, right--;
            for (int i = 0; i < display_size; i++) {
                select[i].setString((i + left < n ? fileList[i + left] : ""));
                select[i].setFillColor(Color::Yellow);
            }
            select[cur - left].setFillColor(Color::Red);
            for (int i = 0; i < display_size; i++) {
                window.draw(select[i]);
            }
        }
        window.display();
    }
    //int countSub = 0;
    //for (auto c : getTextBox) countSub += c == '/';
    //if (!countSub) getTextBox = "Data/" + getTextBox;
    //ifstream f(getTextBox);
    //if (!f.good()) {
    //    f.close();
    //    return false;
    //}
    //input(f);
    //f.close();
    //remove(getTextBox.c_str());
    //return true;
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
    f >> start;
    start = clock() - start;
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
    f << clock() - start << '\n';
}
CGAME::CGAME() {
    scoreboard.load();
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
    level.setPosition(0, 780);
    levelFont.loadFromFile("font/astrolyt.ttf");
    levelText.setFont(levelFont);
    levelText.setFillColor(sf::Color(0, 200, 0));
    levelText.setPosition(700, 820);
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
    TbackgroundWin.loadFromFile("Resource/menuvictory.png");
    backgroundWin.setTexture(TbackgroundWin);
    backgroundWin.setPosition(0, 0);
    TbackgroundSave.loadFromFile("Resource/menusave.png");
    backgroundSave.setTexture(TbackgroundSave);
    backgroundSave.setPosition(0, 0);
    TbackgroundLoad.loadFromFile("Resource/menuload.png");
    backgroundLoad.setTexture(TbackgroundLoad);
    backgroundLoad.setPosition(0, 0);
    levelUp.setBuffer(BlevelUp);
    sound.setBuffer(Bsound);
    sound.setLoop(true);
    sound.setVolume(70.f);
    sound.play();
    //levelText.setColor(Color(100, 100, 100, 100));
}

CGAME::~CGAME() {
    scoreboard.save();
    for (int i = 0; i < map.size(); i++) {
        delete map[i];
    }
    map.clear();
}

void CGAME::GameWin() {
    int deltaTime = (clock() - start) / CLOCKS_PER_SEC;
    string getTextBox = textBox(backgroundWin);
    scoreboard.add(deltaTime, getTextBox);
    scoreboard.show(window);
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
                            start = clock();
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
                        case 3: //high score
                            scoreboard.show(window);
                            break;
                        case 4:
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
        if (mode == 5 && win) {
            GameWin();
            break;
        }
        if (esc) break;
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
    esc = false;
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
            if (ev.key.code == Keyboard::Escape) {
                esc = true;
                return;
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
        if (Person.isFinish(window) && mode != 4) {
            window.draw(SlevelUp);
            levelUp.play();
            win = 1;
            window.display();
            Clock delay;
            delay.restart();
            while (delay.getElapsedTime().asSeconds() < 2.0f);
            return;
        }
        else if (Person.isFinish(window) && mode == 4) {
            win = 1;
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
    string getTextBox = textBox(backgroundSave);
    int countSub = 0;
    for (auto c : getTextBox) countSub += c == '/';
    if (!countSub) getTextBox = "Saved Game/" + getTextBox;
    ofstream f(getTextBox);
    output(f);
    f.close();
}
vector<string> CGAME::getFileName(string directory) {
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