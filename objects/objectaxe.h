
#ifndef AXEOBJECT_H
#define AXEOBJECT_H


#include "toolobject.h"
#include "../player.h"
#include <set>

class ObjectAxe : public ToolObject
{
public:
    explicit ObjectAxe(QObject* parent = nullptr);
    QPointF dir_ = {0, 0};
    void live() override;
    void setAngle(double ang);
    void interactWithObject(Object *obj) override;
    void interactWithObject(ObjectBase *obj) override;
private:
    std::set<ObjectBase*> damaged;
    double ang_ = 0.1;
};

#endif // AXEOBJECT_H
