#include "stone.h"

Stone::Stone(QObject *parent) : LootableObject(parent)
{
    setSolid(true);
    box() = QRectF(-100, -100, 200, 200);
    body() = {{-100, 20}, {-100, -20}, {-50, -35}, {50, -35}, {100, -20}, {100, 20}, {50, 35}, {-50, 35} };
    hitbox() = body();
    useArea() = body();
    setSolidWithPlayer(true);
    loot() = {SpawnOption(new ItemStone(), 10, 20, 0.6), SpawnOption(new ItemStone(), 10, 20, 0.6), SpawnOption(new ItemStone(), 10, 20, 0.6)};
}

void Stone::getDamage(Damage damage) {
    health() -= damage.pickaxeDamage();
    if (health() <= 0) {
        die();
    }
}

