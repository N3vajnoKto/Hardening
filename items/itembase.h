
#ifndef ITEMBASE_H
#define ITEMBASE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QPixmapCache>
#include <QIcon>

#include "../objects/objectbase.h"

class ItemBase : public QObject
{
    Q_OBJECT
public:
    explicit ItemBase(QObject *parent, const QIcon& icon);
    explicit ItemBase(QObject *parent = nullptr);
    explicit ItemBase(const ItemBase *parent);
    ~ItemBase();
    QIcon icon() const;
    void setIcon(const QIcon& icon);
    void setId(QString str);
    bool autouse();
    void setAutouse(bool bl);
    bool isDisposable() const;
    void setDisposable(bool bl);
    QString id();
    QPixmap pixmap(int w = -1, int h = -1, int cnt = 0) const;
    int maxNumber() const;
    void setMaxNumber(int mx);
    virtual bool useItem(QPointF pos);
    virtual ItemBase* copy() const;

private:
    QString id_ = "";
    QRectF box_;
    QIcon icon_;
    bool autouse_ = false;
    bool disposable_ = true;
    int maxNumber_ = 64;

signals:
    void addObject(ObjectBase* obj);
    void itemDestroyed(ItemBase* item);

};

#endif // ITEMBASE_H
