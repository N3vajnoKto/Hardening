
#ifndef ITEM_H
#define ITEM_H


#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QIcon>
#include <QPixmap>

#include "object.h"

class Item : public QObject
{
    Q_OBJECT
public:
    explicit Item(QObject *parent = nullptr, QIcon icon = QIcon(":/icons/notImpl.png"));
    explicit Item(Item *parent);
    int count() const;
    void setCount(int x);
    void addCount(int add);
    QIcon icon() const;
    void addItem(Item* item);
    void setIcon(QIcon icon);
    int maxNumber();
    void setMaxNumber(int mx);
    bool full() const;
    void setId(QString str);
    bool autouse();
    void setAutouse(bool bl);
    QString id();
    QPixmap pixmap(int w = -1, int h = -1) const;

    virtual bool useItem(QPointF pos);

private:
    int count_ = 1;
    int maxNumber_ = 64;
    QString id_ = "";
    QRectF box_;
    QIcon icon_;
    double axeDamage = 0;
    double pickaxeDamage = 0;
    double swordDamage = 0;
    bool autouse_ = false;


signals:
    void addObject(Object* obj);

};

#endif // ITEM_H
