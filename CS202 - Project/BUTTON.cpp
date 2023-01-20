#include "BUTTON.h"

Button::Button(string path, float x, float y, float width, float height, string name, bool needName) {
    this->path = path;
    this->name = name;
    this->buttonState = BTN_IDLE;
    this->shape.setPosition(Vector2f(x, y));
    this->shape.setSize(Vector2f(width, height));
    if (!needName) {
        this->idleTexture.loadFromFile(this->path + "/" + this->name + "_idle.png");
        this->hoverTexture.loadFromFile(this->path + "/" + this->name + "_hover.png");
    }
    this->font.loadFromFile("font/astrolyt.ttf");
    this->needName = needName;
    if (needName) {
        this->idleTexture.loadFromFile(this->path + "_idle.png");
        this->hoverTexture.loadFromFile(this->path + "_hover.png");
        Tname.setFont(font);
        Tname.setCharacterSize(50);
        Tname.setFillColor(Color::White);
        Tname.setPosition( x + (width - name.length() * 45) / 2, y);
        Tname.setString(name);
    }
}
Button::~Button() {

}

void Button::update(const Vector2f mousePos) {
    //IDLE
    this->buttonState = BTN_IDLE;
    if (this->shape.getGlobalBounds().contains(mousePos))
    {
        //HOVER
        this->buttonState = BTN_HOVER;
        bool leftPress = false;
        while (Mouse::isButtonPressed(Mouse::Left))
        {
            leftPress = true;
        }
        if (leftPress)
            this->buttonState = BTN_ACTIVE;
    }
    switch (this->buttonState)
    {
    case BTN_IDLE:
        this->shape.setTexture(&this->idleTexture);
        this->Tname.setFillColor(Color::White);
        break;
    case BTN_HOVER:
        this->shape.setTexture(&this->hoverTexture);
        this->Tname.setFillColor(Color::Red);
        break;
    case BTN_ACTIVE:
        break;
    default:
        break;
    }
}
const bool Button::isPressed() const {
    if (this->buttonState == BTN_ACTIVE)
        return true;
    return false;
}

Vector2f Button::getPosition() {
    return shape.getPosition();
}
void Button::setPosition(int x, int y) {
    shape.setPosition(x, y);
    Tname.setPosition(x + (shape.getSize().x - name.length() * 45) / 2, y);
}

void Button::render(RenderTarget* target)
{
    target->draw(this->shape);
    if (needName) {
        target->draw(this->Tname);
    }
}