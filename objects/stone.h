
#ifndef STONE_H
#define STONE_H



#include "lootableobject.h"
#include "../items/itemstone.h"


class Stone : public LootableObject
{
public:
    Stone(QObject* parent = nullptr);
    void getDamage(Damage damage) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap look_;
};

#endif // STONE_H
