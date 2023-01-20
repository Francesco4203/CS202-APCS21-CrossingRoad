#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>

using namespace std;
using namespace sf;

enum buttonState {BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

class Button {
public:
private:
    // Name
    string name;
    string path;

    // Shape
    short unsigned buttonState;
    RectangleShape shape;

    //Texture
    Texture idleTexture;
    Texture hoverTexture;

    Font font;
    Text Tname;

    bool needName;

public:
    Button(string path, float x, float y, float width, float height, string name, bool needName);
    ~Button();

    void update(const Vector2f mousePos);
    const bool isPressed() const;

    Vector2f getPosition();

    void setPosition(int x, int y);
    void render(RenderTarget* target);
};