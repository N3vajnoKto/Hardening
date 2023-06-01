
#include "objectaxe.h"

ObjectAxe::ObjectAxe(QObject* parent) : ToolObject(parent)
{
    useArea().clear();
    box() = QRectF(-50, -50, 100, 100);
    useArea() = {{-20, -50}, {20, -50}, {20, 30}, {-20, 30}};
    hitbox() = useArea();
    body() = useArea();
    setZValue(1000000);
    QTimer::singleShot(320, this, &ObjectAxe::destroyObject);

    QPixmapCache::find("objectAxe", &look_);

    look_ = look_.transformed(QTransform::fromScale(-1, -1));
    int pw = look_.width();
    int ph = look_.height();
    look_ = look_.transformed(QTransform().rotateRadians(-M_PI / 4));
    look_ = look_.copy((look_.width() - pw)/2, (look_.height() - ph)/2, pw, ph);

}

void ObjectAxe::live() {
    setPos(player()->pos() + dir_ * 100);
    dir_ = QPointF(dir_.x() * cos(ang_) - dir_.y() * sin(ang_), dir_.x() * sin(ang_) + dir_.y() * cos(ang_));
    rotate(-ang_);
    int pw = look_.width();
    int ph = look_.height();
    look_ = look_.transformed(QTransform().rotateRadians(ang_));
    look_ = look_.copy((look_.width() - pw)/2, (look_.height() - ph)/2, pw, ph);
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

    QPointF dir = normalize(obj->pos() - player()->pos());
    obj->speed() += dir * 30;

    if (scenePath(useArea()).intersects(obj->scenePath(obj->hitbox())) && !damaged.count(obj)) {
        damaged.insert(obj);
        obj->getDamage(damage());
    }
}

void ObjectAxe::move(QPointF dir) {
    setPos(pos() + dir);
    setZValue(1000000);
}

void ObjectAxe::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->save();
    painter->drawPixmap(box().x() + 15, box().y() + 15, look_);
    painter->restore();
}
