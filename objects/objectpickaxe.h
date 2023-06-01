
#ifndef OBJECTPICKAXE_H
#define OBJECTPICKAXE_H




#include "toolobject.h"
#include "../player.h"
#include <set>

class ObjectPickaxe : public ToolObject
{
public:
    explicit ObjectPickaxe(QObject* parent = nullptr);
    QPointF dir_ = {0, 0};
    void live() override;
    void setAngle(double ang);
    void interactWithObject(Object *obj) override;
    void interactWithObject(ObjectBase *obj) override;
    void move(QPointF dir) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPixmap look_;
private:
    std::set<ObjectBase*> damaged;
    double ang_ = 0.1;
};


#endif // OBJECTPICKAXE_H
