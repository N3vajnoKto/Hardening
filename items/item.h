
#ifndef ITEM_H
#define ITEM_H

#include "../player.h"
#include "itembase.h"


class Item : public ItemBase
{
public:
    explicit Item(QObject *parent = nullptr);
    explicit Item(const Item *parent);
    virtual bool useItem(QPointF pos);
    Player* player();
    void setPlayer(Player* player);
    virtual ItemBase* copy() const override;
private:
    Player* player_ = nullptr;
};

#endif // ITEM_H
