#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "CANIMAL.h"
#include "CPEOPLE.h"
#include "CVEHICLE.h"
#include "CGAME.h"
#include "CTRAFFIC.h"
#include "CENEMY.h"

using namespace std;
using namespace sf;
CPEOPLE::CPEOPLE(int t) {
    if (t == 1) {
        people.scale(0.1, 0.1);
        people.setPosition(750, 700);
        image.loadFromFile("Resource/man.png");
        people.setTexture(image);
    }
}
void CPEOPLE::move(Event& ev, sf::RenderWindow& window) {
    switch (ev.type)
    {
    case sf::Event::Closed:
        window.close();
        break;

    case sf::Event::KeyPressed:
        switch (ev.key.code)
        {
        case sf::Keyboard::W:
            if (people.getPosition().y - speed >= 0) people.move(0.f, -speed);
            break;
        case sf::Keyboard::S:
            if (people.getPosition().y + speed <= 700) people.move(0.f, speed);
            break;
        case sf::Keyboard::A:
            if (people.getPosition().x - speed >= 0) people.move(-speed, 0.f);
            break;
        case sf::Keyboard::D:
            if (people.getPosition().x + speed <= 1450) people.move(speed, 0.f);
            break;
        }
        break;
    }
}
bool CPEOPLE::isImpact(const CVEHICLE*&) {

}
/*bool CPEOPLE::isImpactA(const CANIMAL*&) {

}*/
bool CPEOPLE::isFinish() {

}
bool CPEOPLE::isDead() {

}
void CPEOPLE::draw(sf::RenderWindow& window) {
    window.draw(this->people);
}