
#ifndef ITEM_H
#define ITEM_H


#include <QObject>


class Item : public QObject
{
    Q_OBJECT
public:
    explicit Item(QObject *parent = nullptr);

private:
    int count_;

signals:

};

#endif // ITEM_H
