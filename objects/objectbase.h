
#ifndef OBJECTBASE_H
#define OBJECTBASE_H
#include <QPointF>
#include <QRectF>
#include <QGraphicsItem>
#include <QPainter>
#include "../damage.h"

namespace Move{
    const QPointF forward{0, -1};
    const QPointF back{0, 1};
    const QPointF left{-1, 0};
    const QPointF right{1, 0};
}


class ObjectBase : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ObjectBase(QObject* parent = nullptr);
    ~ObjectBase() = default;

    QRectF& box();
    QPointF& speed();
    double& health();
    QPointF& direct();
    std::vector<QPointF>& body();
    std::vector<QPointF>& hitbox();
    std::vector<QPointF>& useArea();
    QPainterPath path(const std::vector<QPointF>& vec) const;
    QPainterPath scenePath(const std::vector<QPointF>& vec) const;
    void move(QPointF move);
    void addSpeed(QPointF move);
    void addDirect(QPointF move);
    void setSolid(bool bl);
    bool isSolid() const;
    void setInteractive(bool bl);
    bool isInteractive() const;
    bool isImortal() const;
    void setImortal(bool bl);
    QPointF directionToObject(ObjectBase* obj) const;
    double dist(QPointF) const;
    double dist(ObjectBase* obj) const;
    int movePrior() const;
    void setMovePrior(int prior);
    void rotate(double ang);
    QPointF normalize(QPointF dir);

    virtual void live();
    virtual void interactWithObjectBody(ObjectBase* obj);
    virtual void interactWithObject(ObjectBase* obj);
    virtual void die();
    virtual void getDamage(Damage damage);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void destroyObject();

private:
    QRectF box_;
    std::vector<QPointF> body_;
    std::vector<QPointF> hitbox_;
    std::vector<QPointF> useArea_;
    double health_;
    QPointF speed_;
    QPointF direct_;
    int movePrior_ = 0;
    bool interactive_ = true;
    bool solid = true;
    bool imortal_ = false;
    QPointF prevPos_ = {0, 0};

signals:
    void objectDestroyed(ObjectBase* obj);
    void objectAdded(ObjectBase* obj);


};


#endif // OBJECT_H
