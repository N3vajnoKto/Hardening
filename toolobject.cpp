
#include "toolobject.h"

ToolObject::ToolObject(QObject* parent) : Object(parent)
{
    setSolid(false);
    setInteractive(false);

}

QTimer* ToolObject::timer() {
    return timer_;
}
void ToolObject::setTimer(QTimer* timer) {
    timer_ = timer;
}

void ToolObject::setPlayer(Player* player) {
    player_ = player;
}
Player* ToolObject::player() {
    return player_;
}

void ToolObject::live() {

}

