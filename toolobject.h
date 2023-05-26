
#ifndef TOOLOBJECT_H
#define TOOLOBJECT_H

#include "object.h"
#include "player.h"
#include <QTimer>


class ToolObject : public Object
{
public:
    ToolObject(QObject* parent);
    QTimer* timer();
    void setTimer(QTimer* timer);
    void setPlayer(Player* player);
    Player* player();
    virtual void live() override;
private:
    QTimer* timer_ = nullptr;
    Player* player_ = nullptr;
};

#endif // TOOLOBJECT_H
