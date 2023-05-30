
#ifndef DROPPEDITEMOBJECT_H
#define DROPPEDITEMOBJECT_H

#include "object.h";
#include "../items/itemgroup.h"


class DroppedItemObject : public Object
{
public:
    DroppedItemObject(ItemGroup* item = nullptr, QObject* parent = nullptr);
    ~DroppedItemObject();
    ItemGroup* item();
    void setItem(ItemGroup* item);
    PlayerBase* player();
    void setPlayer(PlayerBase* player);
    void live() override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void interactWithPlayer(PlayerBase *player) override;
public slots:
    void makeInteractive();
private:
    ItemGroup* item_ = nullptr;
    PlayerBase* player_ = nullptr;
};

#endif // DROPPEDITEMOBJECT_H
