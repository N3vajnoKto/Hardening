#include "stone.h"

Stone::Stone(QObject *parent) : LootableObject(parent)
{
    setSolid(true);
    box() = QRectF(-100, -120, 200, 200);
    body() = {{-50, 20}, {-50, -20}, {-35, -35}, {45, -35}, {60, -20}, {60, 20}, {45, 35}, {-30, 35} };
    hitbox() = body();
    useArea() = body();
    setSolidWithPlayer(true);
    loot() = {SpawnOption(new ItemStone(), 10, 20, 0.6), SpawnOption(new ItemStone(), 10, 20, 0.6), SpawnOption(new ItemStone(), 10, 20, 0.6)};

    QPixmapCache::find("cobblestone", &look_);
}

void Stone::getDamage(Damage damage) {
    health() -= damage.pickaxeDamage();
    if (health() <= 0) {
        die();
    }
}

void Stone::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->save();

    int x = box().x();
    int y = box().y();

    painter->drawPixmap(x, y, look_);

    painter->restore();
}
