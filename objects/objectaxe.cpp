
#include "objectaxe.h"

ObjectAxe::ObjectAxe(QObject* parent) : ToolObject(parent)
{
    useArea().clear();
    box() = QRectF(-30, -50, 60, 100);
    useArea() = {{-20, -40}, {20, -40}, {20, 40}, {-20, 40}};
    hitbox() = useArea();
    body() = useArea();

    QTimer::singleShot(320, this, &ObjectAxe::destroyObject);
}

void ObjectAxe::live() {
    setPos(player()->pos() + dir_ * 100);
    dir_ = QPointF(dir_.x() * cos(ang_) - dir_.y() * sin(ang_), dir_.x() * sin(ang_) + dir_.y() * cos(ang_));
    rotate(-ang_);
}

void ObjectAxe::setAngle(double ang) {
    ang_ = ang;
}

void ObjectAxe::interactWithObject(Object *obj) {
    if (player() == dynamic_cast<Player*> (obj)) {
        return;
    }


    if (scenePath(useArea()).intersects(obj->scenePath(obj->hitbox())) && !damaged.count(obj)) {
        damaged.insert(obj);
        obj->getDamage(damage());
    }
}
void ObjectAxe::interactWithObject(ObjectBase *obj) {
    if (player() == dynamic_cast<Player*> (obj)) {
        return;
    }

    if (scenePath(useArea()).intersects(obj->scenePath(obj->hitbox())) && !damaged.count(obj)) {
        damaged.insert(obj);
        obj->getDamage(damage());
    }
}
