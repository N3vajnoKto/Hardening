
#include "objectpickaxe.h"

ObjectPickaxe::ObjectPickaxe(QObject* parent) : ToolObject(parent)
{
    useArea().clear();
    box() = QRectF(-30, -50, 60, 100);
    useArea() = {{-20, -40}, {20, -40}, {20, 40}, {-20, 40}};
    hitbox() = useArea();
    body() = useArea();
    setZValue(1000000);
    QTimer::singleShot(320, this, &ObjectPickaxe::destroyObject);

    QPixmapCache::find("objectPickaxe", &look_);

    look_ = look_.transformed(QTransform::fromScale(-1, -1));
    int pw = look_.width();
    int ph = look_.height();
    look_ = look_.transformed(QTransform().rotateRadians(-M_PI / 4));
    look_ = look_.copy((look_.width() - pw)/2, (look_.height() - ph)/2, pw, ph);
}

void ObjectPickaxe::live() {
    setPos(player()->pos() + dir_ * 100);
    dir_ = QPointF(dir_.x() * cos(ang_) - dir_.y() * sin(ang_), dir_.x() * sin(ang_) + dir_.y() * cos(ang_));
    rotate(-ang_);
    int pw = look_.width();
    int ph = look_.height();
    look_ = look_.transformed(QTransform().rotateRadians(ang_));
    look_ = look_.copy((look_.width() - pw)/2, (look_.height() - ph)/2, pw, ph);
}

void ObjectPickaxe::setAngle(double ang) {
    ang_ = ang;
}

void ObjectPickaxe::interactWithObject(Object *obj) {
    if (player() == dynamic_cast<Player*> (obj)) {
        return;
    }

    if (scenePath(useArea()).intersects(obj->scenePath(obj->hitbox())) && !damaged.count(obj)) {
        damaged.insert(obj);
        obj->getDamage(damage());
    }
}
void ObjectPickaxe::interactWithObject(ObjectBase *obj) {
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

void ObjectPickaxe::move(QPointF dir) {
    setPos(pos() + dir);
    setZValue(1000000);
}

void ObjectPickaxe::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->save();
    painter->drawPixmap(box().x(), box().y(), look_);
    painter->restore();
}

