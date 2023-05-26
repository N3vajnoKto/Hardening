
#include "tool.h"

Tool::Tool(QObject* parent) : Item(parent)
{
    setAutouse(true);
}

double Tool::axeDamage() {
    return axeDamage_;
}
void Tool::setAxeDamage(double damage) {
    axeDamage_ = damage;
}

double Tool::pickaxeDamage() {
    return pickaxeDamage_;
}

void Tool::setPickaxeDamage(double damage) {
    pickaxeDamage_ = damage;
}

double Tool::swordDamage() {
    return swordDamage_;
}

void Tool::setSwordDamage(double damage) {
    swordDamage_ = damage;
}

double Tool::useRadius() {
    return useRadius_;
}

void Tool::setUseRadius(double rad) {
    useRadius_ = rad;
}

Player* Tool::player() {
    return player_;
}
void Tool::setPlayer(Player* player) {
    player_ = player;
}

int Tool::reload() {
    return reload_;
}

void Tool::setReload(int rl) {
    reload_ = rl;
}

bool Tool::usable() {
    return usable_;
}

void Tool::setUsable(bool bl) {
    usable_ = bl;
}

void Tool::startReload(int msec) {
    setUsable(false);
    QTimer::singleShot(msec, this, &Tool::finishReload);
}

void Tool::finishReload() {
    setUsable(true);
}

bool Tool::useItem(QPointF pos) {
    return true;
}
