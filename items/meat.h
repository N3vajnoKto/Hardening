
#ifndef MEAT_H
#define MEAT_H


#include "item.h"

class Meat : public Item
{
public:
    Meat(QObject* parent = nullptr);
    Meat(const Meat* parent);
    ItemBase* copy() const override;
};

#endif // MEAT_H
