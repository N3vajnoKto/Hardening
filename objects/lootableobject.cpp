
#include "lootableobject.h"
#include "droppeditemobject.h"

LootableObject::LootableObject(QObject* parent) : Object(parent)
{

}

LootableObject::~LootableObject() {
    for (auto to : loot_) {
        delete to.item();
    }
}

SpawnOption::SpawnOption(Item* item, int mn, int mx, double chance) {
    item_ = item;
    minimum_ = mn;
    maximum_ = mx;
    chance_ = chance;
}


std::vector<SpawnOption>& LootableObject::loot() {
    return loot_;
}

int SpawnOption::minimum() {
    return minimum_;
}

int SpawnOption::maximum() {
    return maximum_;
}

Item* SpawnOption::item() {
    return item_;
}

double SpawnOption::chance() {
    return chance_;
}

ItemGroup* SpawnOption::spawn() {
    int res = minimum();
    std::mt19937 rnd(time(0));
    if ( maximum() - minimum() != 0 && (rnd() % 1000) / 1000.0 <= chance()) {
        res += rnd() % (maximum() - minimum());
    }

    ItemGroup* it = new ItemGroup(item()->copy());
    it->setCount(std::min(item()->maxNumber(), res));

    return it;
}

void LootableObject::die() {
    std::mt19937 rnd(time(0));
    for (auto to : loot_) {
        ItemGroup* itemGroup = to.spawn();
        DroppedItemObject* drop = new DroppedItemObject(itemGroup);
        QPointF dir = QPointF(cos((rnd() % 1000) / 300), sin((rnd() % 1000) / 300));
        drop->setPos(pos());
        drop->speed() = dir * 10;
        emit objectAdded(drop);
    }

    destroyObject();
}

