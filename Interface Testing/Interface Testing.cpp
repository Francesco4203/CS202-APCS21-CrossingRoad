#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
//#include "CANIMAL.h"
//#include "CPEOPLE.h"
//#include "CVEHICLE.h"
//#include "CGAME.h"
using namespace std;
using namespace sf;
class CVEHICLE {
protected:
	int speed;//step per second, or seconds needed for 1 step
	bool isStop;
	Sprite object;
	Texture vehicle;
public:
	CVEHICLE() = delete;//default NOT available
	CVEHICLE(int x, int y, int mode);
	virtual void Move() = 0;
	void stop();//stop when red light
	void resume();//move again when green light
	Sprite getObject();
};

//Constructor set image for object

class CTRUCK : public CVEHICLE {
	// image
public:
	CTRUCK() = delete;//default NOT available
	CTRUCK(int x, int y, int mode);//1 2 3 -> easy medium hard
	void Move();
	~CTRUCK();//1 2 3 -> easy medium hard
};
class CCAR : public CVEHICLE {
	// image
public:
	CCAR() = delete;//default NOT available
	CCAR(int x, int y, int mode);//1 2 3 -> easy medium hard
	void Move();
	~CCAR();
};
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
}
CTRUCK::~CTRUCK() {

}
void CTRUCK::Move() {
	if (isStop) return;
	srand(time(NULL));
	object.move((rand() % speed + 3) / 10.0, 0);
}
CCAR::CCAR(int x, int y, int mode) : CVEHICLE(x, y, mode) {
	vehicle.loadFromFile("Resource/car.png");
	object.setTexture(vehicle);
}
CCAR::~CCAR() {

}
void CCAR::Move() {
	if (isStop) return;
	srand(time(NULL));
	object.move((rand() % (speed + 5) + 3) / 10.0, 0);
}

int main()
{
    string resourcePath = "Resource/";

    RenderWindow window(VideoMode(1500, 800), "Crossing Road Game!");
	CVEHICLE* a,*b;
	a = new CCAR(5, 10, 1);
	b = new CTRUCK(100, 100, 1);
    while (window.isOpen()) {

        Event event;
		a->resume();
		b->resume();
        while (window.pollEvent(event))
        {
			if (event.type && event.key.code == Keyboard::Escape) {
				window.close();
			}
        }
		a->Move();
		b->Move();
        window.clear();
		window.draw(a->getObject());
		window.draw(b->getObject());
        window.display();
    }
    
    return 0;
}