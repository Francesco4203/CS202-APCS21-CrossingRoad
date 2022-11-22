#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "CANIMAL.h"
#include "CPEOPLE.h"
#include "CVEHICLE.h"
#include "CGAME.h"
#include "CTRAFFIC.h"
using namespace std;
using namespace sf;

void CVEHICLE::stop() {
	isStop = true;
}
void CVEHICLE::resume() {
	isStop = false;
}
Sprite CVEHICLE::getObject() {
	return object;
}
CVEHICLE::CVEHICLE(int x, int y, int mode) {
	speed = (mode == 1 ? 5 : (mode == 2 ? 7 : 10));
	isStop = 1;
	object.setPosition(x, y);
	object.scale(0.3, 0.3);
}
CTRUCK::CTRUCK(int x, int y, int mode) : CVEHICLE(x, y, mode) {
	vehicle.loadFromFile("Resource/truck.png");
	object.setTexture(vehicle);
	if (object.getPosition().x >= 1500) {
		object.setPosition(-200, object.getPosition().y);
	}
}
void CTRUCK::Move(bool reverse) {
	if (isStop) return;
	object.move((reverse ? -1 : 1) * (speed / 50.0), 0);
}
CCAR::CCAR(int x, int y, int mode) : CVEHICLE(x, y, mode) {
	vehicle.loadFromFile("Resource/car.png");
	object.setTexture(vehicle);
	if (object.getPosition().x >= 1500) {
		object.setPosition(-200, object.getPosition().y);
	}
}
void CCAR::Move(bool reverse) {
	if (isStop) return;
	object.move((reverse ? -1 : 1) * ((speed + 3) / 50.0), 0);
}