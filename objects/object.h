
#ifndef OBJECT_H
#define OBJECT_H

#include "objectbase.h"
#include "../playerbase.h"

class Object : public ObjectBase
{
public:
    Object(QObject* parent = nullptr);
    virtual void interactWithPlayer(PlayerBase* player);
    virtual void interactWithPlayerBody(PlayerBase* player);
    virtual void interactWithObjectBody(Object* obj);
    virtual void interactWithObject(Object* obj);
    virtual void die() override;

    bool isSolidWithPlayer() const;
    void setSolidWithPlayer(bool bl);
    void setDamage(Damage damage);
    Damage damage() const;
private:
    bool solidWithPlayer_ = true;
    Damage damage_;

};

#endif // OBJECT_H
