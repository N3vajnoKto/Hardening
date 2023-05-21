
#ifndef INVENTORY_H
#define INVENTORY_H


#include <QObject>
#include "cell.h"


class Inventory : public QObject
{
    Q_OBJECT
public:
    explicit Inventory(int sz = 30, int row = 10, QObject *parent = nullptr);
    Cell* at(int ind);
    std::vector<Cell*>& cells();
    int row() const;
    int x();
    int y();
    void makeCurrent(Cell* cell);
    Cell* current();
    void rebuild();

private:
    std::vector<Cell*> cells_;
    Cell* current_ = nullptr;
    int x_ = 5;
    int y_ = 5;
    int row_ = 10;
    QRectF cellSize = {0, 0, 30, 30};
    int space = 5;
    double scale = 1.15;

signals:

};

#endif // INVENTORY_H
