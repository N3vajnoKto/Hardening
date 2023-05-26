
#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "inventory.h"

class Player : public Object
{
public:
    Player(QObject* parent = nullptr);
    QPointF& playerMovement();
    QPointF& playerDirection();
    void addPlayerMovement(QPointF move);
    void setPlayerDirection(QPointF move);
    QPointF normalize(QPointF dir);
    void live() override;
    void interactWithObject(Object*) override;
    bool ableToMove = true;
    Inventory* inventory();
private:
    QPointF playerMovement_;
    QPointF playerDirection_;
    double playerSpeed_ = 7;
    Inventory* inventory_;

};

#endif // PLAYER_H
