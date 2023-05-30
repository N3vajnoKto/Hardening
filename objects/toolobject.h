
#ifndef TOOLOBJECT_H
#define TOOLOBJECT_H

#include "object.h"
#include "../player.h"
#include <QTimer>


class ToolObject : public Object
{
public:
    ToolObject(QObject* parent);
    void setPlayer(Player* player);
    Player* player();
    virtual void live() override;
private:
    Player* player_ = nullptr;
};

#endif // TOOLOBJECT_H
