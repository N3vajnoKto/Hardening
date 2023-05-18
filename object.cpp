
#include "object.h"
#include <QPainterPath>
Object::Object(QObject* parent) : QObject(parent), QGraphicsItem()
{
    box_ = {-40, -40, 80, 80};
    body_ = {{-20, -20}, {20, -20}, {0, 20}};
    hitbox_ = {{-20, -40}, {20, -40}, {20, 20}, {-20, 20}};
    speed_ = {0, 0};
    health_ = 100;
    direct_ = {0, 0};
    setPos({0, 0});

}

QPainterPath Object::shape() const {
    QPainterPath path(body_.at(0));
    for (int i = 1; i < body_.size(); ++i) {
        path.lineTo(body_.at(i));
    }

    path.closeSubpath();

    return path;
}


std::vector<QPointF>& Object::hitbox() {
    return hitbox_;
}

QPainterPath Object::path(const std::vector<QPointF>& vec) const {
    QPainterPath path(vec.at(0));
    for (int i = 1; i < vec.size(); ++i) {
        path.lineTo(vec.at(i));
    }

    path.closeSubpath();

    return path;
}

QPainterPath Object::scenePath(const std::vector<QPointF>& vec) const {
    QPainterPath path(vec.at(0) + pos());
    for (int i = 1; i < vec.size(); ++i) {
        path.lineTo(vec.at(i) + pos());
    }

    path.closeSubpath();

    return path;
}

QRectF& Object::box() {
    return box_;
}
QPointF& Object::speed() {
    return speed_;
}
QPointF& Object::direct() {
    return direct_;
}

double& Object::health() {
    return health_;
}

std::vector<QPointF>& Object::body() {
    return body_;
}

QRectF Object::boundingRect() const {

    return box_;
}

void Object::move(QPointF move) {
    setPos(pos() + move);
}

void Object::addSpeed(QPointF move) {
    speed_ += move;
}

void Object::addDirect(QPointF move) {
    direct_ += move;
}

void Object::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->save();
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(QPen(Qt::black, 2));
    painter->drawPath(shape());
    painter->setPen(QPen(Qt::green, 2));
    painter->drawPath(path(hitbox()));

    painter->restore();
}

void Object::live() {
    if (!enabled) return;
    move(speed());
}

void Object::setSolid(bool bl) {
    solid = bl;
}

bool Object::isSolid() const {
    return solid;
}

QPointF Object::directionToObject(Object* obj) const{
    return obj->pos() - pos();
}

double Object::dist(QPointF dir) const {
    return sqrtl(dir.x() * dir.x() + dir.y() * dir.y());
}

double Object::dist(Object* obj) const{
    return dist(directionToObject(obj));
}

int Object::movePrior() const {
    return movePrior_;
}

void Object::setMovePrior(int prior) {
    movePrior_ = prior;
}

QPointF Object::normalize(QPointF dir) {
    double len = sqrtl(dir.x() * dir.x() + dir.y() * dir.y());
    if (len == 0) return dir;
    dir.rx() /= len;
    dir.ry() /= len;

    return dir;
}

void Object::destroyObject() {
    emit objectDestroyed(this);
}

void Object::rotate(double ang) {
    for (auto& to : hitbox_){
        double x = to.x();
        double y = to.y();
        to.rx() = x * cos(ang) + y * sin(ang);
        to.ry() = -x * sin(ang) + y * cos(ang);
    }

    for (auto& to : body_){
        double x = to.x();
        double y = to.y();
        to.rx() = x * cos(ang) + y * sin(ang);
        to.ry() = -x * sin(ang) + y * cos(ang);
    }

}

void Object::interactWithObjectBody(Object* obj) {
    if (collidesWithItem(obj)) {
        if (isSolid() && obj->isSolid() && movePrior() <= obj->movePrior()) {
            double l = 0;
            double r = std::max(box().width(), box().height());
            QPointF dir = normalize(pos() - obj->pos());
            for (int i = 0; i < 5; ++i) {
                double sr = (l + r) / 2;
                move(sr * dir);
                if (collidesWithItem(obj)) {
                    l = sr;
                } else {
                    r = sr;
                }
                move(-sr * dir);
            }

            move(r * dir);
        }
    }
}

void Object::interactWithObject(Object* obj) {

}

