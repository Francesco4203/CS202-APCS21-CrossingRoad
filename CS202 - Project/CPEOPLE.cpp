#include "INCLUDING.h"

using namespace std;
using namespace sf;
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
        /*player_fix.top -= 30;
        player_fix.left += 20;
        player_fix.height = 30;
        player_fix.width = 30;*/
        if (a->getVectorList()[i]->getObject().getGlobalBounds().intersects(player_fix)) {
            return true;
        }
    }
    return false;
}