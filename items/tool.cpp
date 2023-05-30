
#include "tool.h"

Tool::Tool(QObject* parent) : Item(parent)
{
    setAutouse(true);
}

Tool::Tool(const Tool* tool) : Item(tool) {
    damage_ = tool->damage_;
    useRadius_ = tool->useRadius_;
    usable_ = tool->usable_;
    reload_ = tool->reload_;
}

Damage Tool::damage() const {
    return damage_;
}
void Tool::setDamage(Damage damage) {
    damage_ = damage;
}

double Tool::useRadius() {
    return useRadius_;
}

void Tool::setUseRadius(double rad) {
    useRadius_ = rad;
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

ItemBase* Tool::copy() const {
    return new Tool(this);
}

bool Tool::useItem(QPointF pos) {
    return true;
}
