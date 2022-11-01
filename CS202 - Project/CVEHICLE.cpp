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
void CVEHICLE::Move(int, int) {

}
void CVEHICLE::stop() {

}
void CVEHICLE::resume() {

}
CVEHICLE::CVEHICLE() {

}
CVEHICLE::CVEHICLE(int mode) {

}
CTRUCK::CTRUCK() : CVEHICLE() {

}
CTRUCK::CTRUCK(int mode) : CVEHICLE(mode) {

}
CTRUCK::~CTRUCK() {

}
CCAR::CCAR() : CVEHICLE() {

}
CCAR::CCAR(int mode) : CVEHICLE(mode) {

}
CCAR::~CCAR() {

}