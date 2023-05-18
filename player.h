
#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

class Player : public Object
{
public:
    Player(QObject* parent = nullptr);
    QPointF& playerMovement(QPointF move);
    QPointF& playerDirection(QPointF move);
    void addPlayerMovement(QPointF move);
    void setPlayerDirection(QPointF move);
    QPointF normalize(QPointF dir);
    void live() override;
    void interactWithObject(Object*) override;
    bool ableToMove = true;
private:
    QPointF playerMovement_;
    QPointF playerDirection_;
    double playerSpeed_ = 7;

};

#endif // PLAYER_H
