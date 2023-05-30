
#include "toolobject.h"

ToolObject::ToolObject(QObject* parent) : Object(parent)
{
    setSolid(false);
    setInteractive(false);

}

void ToolObject::setPlayer(Player* player) {
    player_ = player;
}
Player* ToolObject::player() {
    return player_;
}

void ToolObject::live() {

}

