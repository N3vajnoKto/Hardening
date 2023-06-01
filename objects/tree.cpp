
#include "tree.h"

Tree::Tree(QObject *parent) : LootableObject(parent)
{
    setSolid(true);
    box() = QRectF(-120, -180, 200, 200);
    body() = {{-40, -30}, {-30, -40}, {-30, -40}, {20, -30}, {20, 0}, {-40, 0}};
    hitbox() = body();
    useArea() = body();
    setSolidWithPlayer(true);
    loot() = {SpawnOption(new ItemWood(), 10, 20), SpawnOption(new ItemWood(), 10, 20), SpawnOption(new ItemWood(), 10, 20)};

    QPixmapCache::find("tree", &look_);
}

void Tree::getDamage(Damage damage) {
    health() -= damage.axeDamage();
    if (health() <= 0) {
        die();
    }
}

void Tree::setLook(const QPixmap& pxm) {
    look_ = pxm;
}

void Tree::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->save();

    int x = box().x();
    int y = box().y();

    painter->drawPixmap(x, y, look_);

    painter->restore();
}
