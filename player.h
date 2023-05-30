
#ifndef PLAYER_H
#define PLAYER_H

#include "playerbase.h"
#include "objects/object.h"


class Player : public PlayerBase
{
public:
    Player(QObject* parent = nullptr);
    void interactWithObjectBody(Object* obj);
};

#endif // PLAYER_H
