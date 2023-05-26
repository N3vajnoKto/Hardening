
#ifndef OBJECT_H
#define OBJECT_H
#include <QPointF>
#include <QRectF>
#include <QGraphicsItem>
#include <QPainter>

namespace Move{
    const QPointF forward{0, -1};
    const QPointF back{0, 1};
    const QPointF left{-1, 0};
    const QPointF right{1, 0};
};

class Object : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Object(QObject* parent = nullptr);
    ~Object() = default;

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
    QPointF directionToObject(Object* obj) const;
    double dist(QPointF) const;
    double dist(Object* obj) const;
    int movePrior() const;
    void setMovePrior(int prior);
    void rotate(double ang);
    QPointF normalize(QPointF dir);


    virtual void live();
    virtual void interactWithObjectBody(Object* obj);
    virtual void interactWithObject(Object* obj);

    QRectF boundingRect() const;
    QPainterPath shape() const override;
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
    QPointF prevPos_ = {0, 0};

signals:
    void objectDestroyed(Object* obj);


};


#endif // OBJECT_H
