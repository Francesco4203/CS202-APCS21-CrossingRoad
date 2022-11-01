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
class animal {
public:
	virtual void say() {
		cout << "animal\n";
	}
	void supersay() {
		cout << "super animal\n";
	}
};
class pussy:public animal{
public:
	void say() {
		cout << "meow meow\n";
	}
	void supersay() {
		cout << "super meow\n";
	}
};
int main()
{
	animal* a = new animal();//a is animal
	pussy* b = new pussy();//b is pussy
	a->say();//a say as animal
	a->supersay();//a super say as animal
	b->say();// b say as pussy
	b->supersay();// b super say as pussy
	a = (animal*) b;//a cast up from pussy to animal
	a->say();//a still say as pussy, since say in animal is virtual
	a->supersay();//a super say as animal
	//return 0;
	RenderWindow window(VideoMode({ 200, 200 }), "Work?");
	CircleShape shape(100.f);
	shape.setFillColor(Color::Red);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
		}
		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
}