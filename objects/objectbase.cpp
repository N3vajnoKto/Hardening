
#include "objectbase.h"
#include <QPainterPath>
ObjectBase::ObjectBase(QObject* parent) : QObject(parent), QGraphicsItem()
{
    box_ = {-40, -40, 80, 80};
    body_ = {{-20, -20}, {20, -20}, {20, 20}, {-20, 20}};
    hitbox_ = {{-20, -40}, {20, -40}, {20, 20}, {-20, 20}};
    double angle = 0;

    for (int i = 0; i < 8; ++i) {
        useArea_.push_back({50 * cos(angle), 50 * sin(angle)});
        angle += 2 * M_PI / 8;
    }

    speed_ = {0, 0};
    health_ = 100;
    direct_ = {0, 0};
    setPos({0, 0});

}

void ObjectBase::getDamage(Damage damage) {
    if (isImortal()) return;
    health() -= damage.swordDamage();
    if (health() <= 0) {
        die();
    }
}


std::vector<QPointF>& ObjectBase::hitbox() {
    return hitbox_;
}

QPainterPath ObjectBase::path(const std::vector<QPointF>& vec) const {
    QPainterPath path(vec.at(0));
    for (int i = 1; i < vec.size(); ++i) {
        path.lineTo(vec.at(i));
    }

    path.closeSubpath();

    return path;
}

QPainterPath ObjectBase::scenePath(const std::vector<QPointF>& vec) const {
    QPainterPath path(vec.at(0) + pos());
    for (int i = 1; i < vec.size(); ++i) {
        path.lineTo(vec.at(i) + pos());
    }

    path.closeSubpath();

    return path;
}

QRectF& ObjectBase::box() {
    return box_;
}
QPointF& ObjectBase::speed() {
    return speed_;
}
QPointF& ObjectBase::direct() {
    return direct_;
}

double& ObjectBase::health() {
    return health_;
}

std::vector<QPointF>& ObjectBase::body() {
    return body_;
}

std::vector<QPointF>& ObjectBase::useArea() {
    return useArea_;
}

QRectF ObjectBase::boundingRect() const {

    return box_;
}

void ObjectBase::move(QPointF move) {
    setPos(pos() + move);
    setZValue(int(y()));
}

void ObjectBase::addSpeed(QPointF move) {
    speed_ += move;
}

void ObjectBase::addDirect(QPointF move) {
    direct_ += move;
}

void ObjectBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->save();
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(QPen(Qt::black, 2));
    painter->drawPath(path(body()));
    painter->setPen(QPen(Qt::green, 2));
    painter->drawPath(path(hitbox()));

    painter->setPen(QPen(Qt::red, 2));
    painter->drawPath(path(useArea()));

    painter->restore();
}

void ObjectBase::live() {
    move(speed());
}

void ObjectBase::die() {
    destroyObject();
}

void ObjectBase::setSolid(bool bl) {
    solid = bl;
}

bool ObjectBase::isSolid() const {
    return solid;
}

bool ObjectBase::isImortal() const {
    return imortal_;
}

void ObjectBase::setImortal(bool bl) {
    imortal_ = bl;
}

void ObjectBase::setInteractive(bool bl) {
    interactive_ = bl;
}

bool ObjectBase::isInteractive() const {
    return interactive_;
}

QPointF ObjectBase::directionToObject(ObjectBase* obj) const{
    return obj->pos() - pos();
}

double ObjectBase::dist(QPointF dir) const {
    return sqrtl(dir.x() * dir.x() + dir.y() * dir.y());
}

double ObjectBase::dist(ObjectBase* obj) const{
    return dist(directionToObject(obj));
}

int ObjectBase::movePrior() const {
    return movePrior_;
}

void ObjectBase::setMovePrior(int prior) {
    movePrior_ = prior;
}

QPointF ObjectBase::normalize(QPointF dir) {
    double len = sqrtl(dir.x() * dir.x() + dir.y() * dir.y());
    if (len == 0) return dir;
    dir.rx() /= len;
    dir.ry() /= len;

    return dir;
}

void ObjectBase::destroyObject() {
    emit objectDestroyed(this);
}

void ObjectBase::rotate(double ang) {
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

    for (auto& to : useArea_){
        double x = to.x();
        double y = to.y();
        to.rx() = x * cos(ang) + y * sin(ang);
        to.ry() = -x * sin(ang) + y * cos(ang);
    }

}

void ObjectBase::interactWithObjectBody(ObjectBase* obj) {
    if (scenePath(body()).intersects(obj->scenePath(obj->body()))) {
        if (isSolid() && obj->isSolid() && movePrior() <= obj->movePrior()) {
            double l = 0;
            double r = std::max(box().width(), box().height());
            QPointF dir = normalize(pos() - obj->pos());
            for (int i = 0; i < 5; ++i) {
                double sr = (l + r) / 2;
                move(sr * dir);
                if (scenePath(body()).intersects(obj->scenePath(obj->body()))) {
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

void ObjectBase::interactWithObject(ObjectBase* obj) {

}

