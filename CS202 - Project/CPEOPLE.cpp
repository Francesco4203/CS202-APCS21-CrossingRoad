#include "CPEOPLE.h"

using namespace std;
using namespace sf;

void CPEOPLE::output(ofstream& f) {
    f << _player.getPosition().x << ' ' << _player.getPosition().y << '\n';
}
void CPEOPLE::setPosition(double x, double y) {
    _player.setPosition(x, y);
}
CPEOPLE::CPEOPLE(float switchTime, float speed) {
    string characterPath;
    ifstream fin("Data/character_path");
    fin >> characterPath;
    fin.close();
    if (characterPath == "Resource/man.png") isMan = true;
    else isMan = false;
    _Tplayer.loadFromFile(characterPath);
    _currentImage.width = _Tplayer.getSize().x / 4;
    _currentImage.height = _Tplayer.getSize().y / 4;
    _player.setTexture(_Tplayer);
    _player.setTextureRect(_currentImage);
    _switchTime = switchTime;
    _speed = speed;
    _totalTime = 0;
    _scale.x = 0;
    _scale.y = 0;
    isDie = false;
}
void CPEOPLE::setPeople(float switchTime, float speed, int t) {
    if (t == 1) {
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
    if (t == 2) {
        _Tplayer.loadFromFile("Resource/woman.png");
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
}
void CPEOPLE::move(float deltaTime) {
    if (isDie) return;
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
bool CPEOPLE::isFinish(Sprite& finishLine) {
    if (Collision::PixelPerfectTest(_player, finishLine)) {
        return true;
    }
    return false;
}
void CPEOPLE::draw(sf::RenderWindow& window) {
    window.draw(this->_player);
}
CENEMY* CPEOPLE::isImpact(LINE* a) {
    //auto player_fix = _player;
    //player_fix.scale(0.8, 0.8);
    for (int i = 0; i < a->getVectorList().size(); i++) {
        //auto object_fix = a->getVectorList()[i]->getObject();
        //object_fix.scale(0.8, 0.8);
        //if (object_fix.getGlobalBounds().intersects(player_fix.getGlobalBounds())) {
        if (Collision::PixelPerfectTest(_player, a->getVectorList()[i]->getObject())) {
            a->getVectorList()[i]->sound();
            isDie = true;
            return a->getVectorList()[i];
        }
    }
    return NULL;
}

Sprite& CPEOPLE::getSprite() {
    return this->_player;
}

bool CPEOPLE::getIsMan() {
    return isMan;
}