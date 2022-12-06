#include "INCLUDING.h"

void CENEMY::setPosition(double x, double y) {
    object.setPosition(x, y);
}
void CENEMY::output(ofstream& f) {
    f << type << ' ' << speed << ' ' << isStop << ' ' << object.getPosition().x << ' ' << object.getPosition().y << '\n';
}
void CENEMY::stop() {
    isStop = true;
}
void CENEMY::resume() {
    isStop = false;
}
Sprite CENEMY::getObject() {
    return object;
}

void CENEMY::Move(bool reverse) {
    if (isStop) return;
    object.move((reverse ? -1 : 1) * (speed + 3) / 50.0, 0);
    if (object.getPosition().x >= 1500 && !reverse) {
        object.setPosition(-350, object.getPosition().y);
    }
    if (object.getPosition().x <= -200 && reverse) {
        object.setPosition(1500 + 350, object.getPosition().y);
    }
}