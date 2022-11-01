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

int main()
{
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
