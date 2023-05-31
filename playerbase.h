
#ifndef PLAYERBASE_H
#define PLAYERBASE_H

#include "objects/objectbase.h"
#include "inventory.h"
#include "items/itembase.h"

class PlayerBase : public ObjectBase
{
public:
    PlayerBase(QObject* parent = nullptr);
    QPointF& playerMovement();
    QPointF& playerDirection();
    void addPlayerMovement(QPointF move);
    void setPlayerDirection(QPointF move);
    QPointF normalize(QPointF dir);
    void live() override;
    void interactWithObject(ObjectBase*) override;
    void getDamage(Damage damage) override;
    bool ableToMove = true;
    Inventory* inventory();
private:
    QPointF playerMovement_;
    QPointF playerDirection_;
    double playerSpeed_ = 7;
    Inventory* inventory_;
signals:
};

#endif // PLAYERBASE_H
