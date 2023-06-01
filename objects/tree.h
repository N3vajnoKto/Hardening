
#ifndef TREE_H
#define TREE_H

#include "lootableobject.h"
#include "../items/itemwood.h"


class Tree : public LootableObject
{
public:
    Tree(QObject* parent = nullptr);
    void getDamage(Damage damage) override;
    void setLook(const QPixmap& pxm);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    QPixmap look_;
};

#endif // TREE_H
