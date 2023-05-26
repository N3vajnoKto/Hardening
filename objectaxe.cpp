
#include "objectaxe.h"

ObjectAxe::ObjectAxe(QObject* parent) : ToolObject(parent)
{
    setTimer(new QTimer(this));

    useArea().clear();
    box() = QRectF(-30, -50, 60, 100);
    useArea() = {{-20, -40}, {20, -40}, {20, 40}, {-20, 40}};
    hitbox() = useArea();
    body() = useArea();

    connect(timer(), &QTimer::timeout, this, &ObjectAxe::destroyObject);
    timer()->start(320);
}

void ObjectAxe::live() {
    setPos(player()->pos() + dir_ * 100);
    dir_ = QPointF(dir_.x() * cos(ang_) - dir_.y() * sin(ang_), dir_.x() * sin(ang_) + dir_.y() * cos(ang_));
    rotate(-ang_);
}

void ObjectAxe::setAngle(double ang) {
    ang_ = ang;
}
