
#include "tree.h"

Tree::Tree(QObject *parent) : LootableObject(parent)
{
    setSolid(true);
    box() = QRectF(-200, -280, 400, 400);
    body() = {{-20, -20}, {20, -20}, {20, 20}, {-20, 20}};
    hitbox() = { {-100, -180}, {100, -180}, {100, -100}, {20, -100}, {20, 20}, {-20, 20}, {-20, -100}, {-100, -100} };
    useArea() = body();
    setSolidWithPlayer(true);
    loot() = {SpawnOption(new ItemWood(), 10, 20), SpawnOption(new ItemWood(), 10, 20), SpawnOption(new ItemWood(), 10, 20)};
}

void Tree::getDamage(Damage damage) {
    health() -= damage.axeDamage();
    if (health() <= 0) {
        die();
    }
}

