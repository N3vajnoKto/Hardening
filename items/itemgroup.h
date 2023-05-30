
#ifndef ITEMGROUP_H
#define ITEMGROUP_H


#include <QObject>
#include "itembase.h"

class ItemGroup : public QObject
{
    Q_OBJECT
public:
    ItemGroup(ItemBase* item = nullptr, QObject* parent = nullptr);
    ItemGroup(ItemGroup* ig);
    ~ItemGroup();
    ItemBase* item() const;
    void setItem(ItemBase* item);
    int count() const;
    void setCount(int c);
    void addCount(int c);
    void addItemGroup(ItemGroup* item);
    QPixmap pixmap(int w, int h) const;
    bool full() const;
    int maxNumber() const;
    void useItem(QPointF pnt);
private:
    ItemBase* item_ = nullptr;
    int count_ = 1;
};

#endif // ITEMGROUP_H
