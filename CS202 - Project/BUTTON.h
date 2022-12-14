#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>

class Button {
public:
	Button() {}
	Button(std::string t, int charsize, sf::Vector2f size, sf::Color bgcolor, sf::Color tcolor){
		text.setString(t);
		text.setCharacterSize(charsize);
		text.setFillColor(tcolor);

		button.setSize(size);
		button.setFillColor(bgcolor);
	}
	void SetAll(std::string t, int charsize, sf::Vector2f size, sf::Color bgcolor, sf::Color tcolor, sf::Font& font) {
		text.setString(t);
		text.setCharacterSize(charsize);
		text.setFillColor(tcolor);
		text.setFont(font);

		button.setSize(size);
		button.setFillColor(bgcolor);
	}
	void setFont(sf::Font& font) {
		text.setFont(font);
	}
	void setBG(sf::Color bgcolor) {
		button.setFillColor(bgcolor);
	}
	void setTColor(sf::Color tcolor) {
		text.setFillColor(tcolor);
	}
	void setST(int x) {
		text.setCharacterSize(x);
	}
	void setPos(sf::Vector2f pos) {
		button.setPosition(pos);
		
		float xPos = (pos.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
		float yPos = (pos.y + button.getLocalBounds().height / 4) - (text.getLocalBounds().height / 4);
		text.setPosition({ xPos,yPos });
	}
	void DrawButton(sf::RenderWindow &window) {
		window.draw(button);
		window.draw(text);
	}
	bool isMO(sf::RenderWindow &window) {
		float mouse_X = sf::Mouse::getPosition(window).x;
		float mouse_Y = sf::Mouse::getPosition(window).y;

		float btn_X = button.getPosition().x;
		float btn_Y = button.getPosition().y;

		float btnPosW = button.getPosition().x + button.getLocalBounds().width;
		float btnPosH = button.getPosition().y + button.getLocalBounds().height;

		if (mouse_X < btnPosW && mouse_X > btn_X && mouse_Y < btnPosH && mouse_Y > btn_Y) {
			return true;
		}
		return false;
	}
	~Button(){}
private:
	sf::RectangleShape button;
	sf::Text text;
};