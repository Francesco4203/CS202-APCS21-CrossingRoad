#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
//#include "CANIMAL.h"
//#include "CPEOPLE.h"
//#include "CVEHICLE.h"
//#include "CGAME.h"

#include <ctime>

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

int main()
{
    string resourcePath = "Resource/";

    RenderWindow window(VideoMode(1500, 800), "Crossing Road Game!");

    Font font;
    font.loadFromFile(resourcePath + "arial.ttf");
    Text loseT, winT;
    loseT.setFont(font);
    loseT.setString("LOSE");
    loseT.setCharacterSize(60);
    loseT.setPosition(500, 500);

    winT.setFont(font);
    winT.setString("WIN");
    winT.setCharacterSize(60);
    winT.setPosition(500, 500);

    Texture Tcar, Ttruck, Troad, Tman, Tline;
    Tcar.loadFromFile(resourcePath + "car.png");
    Ttruck.loadFromFile(resourcePath + "truck.png");
    Troad.loadFromFile(resourcePath + "road.png");
    Tman.loadFromFile(resourcePath + "man.png");
    Tline.loadFromFile(resourcePath + "line.png");

    Sprite car1(Tcar);
    Sprite car2(Tcar);
    Sprite truck1(Ttruck);
    Sprite truck2(Ttruck);
    Sprite road1(Troad);
    Sprite road2(Troad);
    Sprite road3(Troad);
    Sprite road4(Troad);
    Sprite man(Tman);
    Sprite line(Tline);

    car1.scale(0.3, 0.3);
    car2.scale(0.3, 0.3);
    truck1.scale(0.3, 0.3);
    truck2.scale(0.3, 0.3);
    road1.scale(3, 0.4);
    road2.scale(3, 0.4);
    road3.scale(3, 0.4);
    road4.scale(3, 0.4);
    man.scale(0.1, 0.1);
    line.scale(4, 0.1);

    car1.setPosition(0, 100);
    road1.setPosition(0, 100);
    truck1.setPosition(1350, 250);
    road2.setPosition(0, 250);
    car2.setPosition(0, 400);
    road3.setPosition(0, 400);
    truck2.setPosition(1350, 550);
    road4.setPosition(0, 550);
    man.setPosition(750, 700);
    line.setPosition(-10, 10);


    srand(time(NULL));
    int speed = 30;
    float x = rand() % 7 + 3, y = rand() % 7 + 3 , z = rand() % 7 + 3, t = rand() % 7 + 3;
    bool win = false, lose = false;

    while (window.isOpen() && (!win || !lose)) {

        Event event;
        while (window.pollEvent(event)) 
        {

            switch (event.type) 
            {

            case Event::Closed:
                window.close();
                break;

            case Event::KeyPressed:
                switch (event.key.code)
                {
                case Keyboard::W:
                    if(man.getPosition().y - speed >= 0) man.move(0, -speed);
                    break;
                case Keyboard::S:
                    if (man.getPosition().y + speed <= 700) man.move(0, speed);
                    break;
                case Keyboard::A:
                    if (man.getPosition().x - speed >= 0) man.move(-speed, 0);
                    break;
                case Keyboard::D:
                    if (man.getPosition().x + speed <= 1450) man.move(speed, 0);
                    break;
                }
                break;

            }

        }

        car1.move(x/10, 0);
        car2.move(y/10, 0);
        truck1.move(-z/10, 0);
        truck2.move(-t/10, 0);
        
        if (car1.getPosition().x >= 1500) {
            car1.setPosition(0, 100);
            x = rand() % 7 + 3;
        }
        if (car2.getPosition().x >= 1500) {
            car2.setPosition(0, 400);
            y = rand() % 7 + 3;
        }
        if (truck1.getPosition().x <= -150) {
            truck1.setPosition(1350, 250);
            z = rand() % 7 + 3;
        }
        if (truck2.getPosition().x <= -150) {
            truck2.setPosition(1350, 550);
            t = rand() % 7 + 3;
        }

        window.clear();

        window.draw(line);
        window.draw(road1);
        window.draw(road2);
        window.draw(road3);
        window.draw(road4);
        window.draw(car1);
        window.draw(car2);
        window.draw(truck1);
        window.draw(truck2);
        window.draw(man);

        if (man.getGlobalBounds().intersects(car1.getGlobalBounds())) {
            lose = true;
        }
        if (man.getGlobalBounds().intersects(car2.getGlobalBounds())) {
            lose = true;
        }
        if (man.getGlobalBounds().intersects(truck1.getGlobalBounds())) {
            lose = true;
        }
        if (man.getGlobalBounds().intersects(truck2.getGlobalBounds())) {
            lose = true;
        }
        if (man.getGlobalBounds().intersects(line.getGlobalBounds())) {
            win = true;
        }
        
        if (lose || win) {
            window.clear();
            if (win) {
                window.draw(winT);
            }
            if (lose) {
                window.draw(loseT);
            }
        }

        window.display();
    }

    return 0;
}