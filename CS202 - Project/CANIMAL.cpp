#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "CANIMAL.h"
#include "CPEOPLE.h"
#include "CANIMAL.h"
#include "CGAME.h"
#include "CTRAFFIC.h"
using namespace std;
using namespace sf;

void CANIMAL::stop() {
	isStop = true;
}
void CANIMAL::resume() {
	isStop = false;
}
Sprite CANIMAL::getObject() {
	return object;
}
CANIMAL::CANIMAL(int x, int y, int mode) {
	speed = (mode == 1 ? 5 : (mode == 2 ? 7 : 10));
	isStop = 1;
	object.setPosition(x, y);
	object.scale(0.3, 0.3);
}
CDINAUSOR::CDINAUSOR(int x, int y, int mode) : CANIMAL(x, y, mode) {
	if (x > 0) animal.loadFromFile("Resource/Rdinausor.png");
	else animal.loadFromFile("Resource/dinausor.png");
	object.setTexture(animal);
}
void CDINAUSOR::Move(bool reverse) {
	if (isStop) return;
	object.move((reverse ? -1 : 1) * (speed + 3) / 50.0, 0);
	if (object.getPosition().x >= 1500 && !reverse) {
		object.setPosition(-350, object.getPosition().y);
	}
	if (object.getPosition().x <= -200 && reverse) {
		object.setPosition(1500 + 350, object.getPosition().y);
	}
}
CBIRD::CBIRD(int x, int y, int mode) : CANIMAL(x, y, mode) {
	if (x > 0) animal.loadFromFile("Resource/Rbird.png");
	else animal.loadFromFile("Resource/bird.png");
	object.setTexture(animal);
}
void CBIRD::Move(bool reverse) {
	if (isStop) return;
	object.move((reverse ? -1 : 1) * (speed + 3) / 50.0, 0);
	if (object.getPosition().x >= 1500 && !reverse) {
		object.setPosition(-350, object.getPosition().y);
	}
	if (object.getPosition().x <= -200 && reverse) {
		object.setPosition(1500 + 350, object.getPosition().y);
	}
}