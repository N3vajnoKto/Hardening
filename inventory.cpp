
#include "inventory.h"
#include <iostream>

Inventory::Inventory(int sz, int row, QObject *parent)
    : QObject{parent}
{
    row_ = row;
    cells_.resize(sz);
    for (int i = 0; i < sz; ++i) {
        cells_[i] = new Cell(nullptr, cellSize, this);
    }

    rebuild();
}

void Inventory::rebuild() {
    double width = x();
    double height = y();

    for (int i = 0; i < cells_.size(); ++i) {
        if (i % row() == 0 && i != 0) {
            height += cellSize.height() + space;
            width = x();
        }
        cells_[i]->setPos({width, height});
        width += cellSize.width() + space;
    }

}

bool Inventory::addItem(ItemGroup* item) {
    emit itemAdded(item->item());
    for (auto* to : cells_) {
        if (to->item() != nullptr){
            to->item()->addItemGroup(item);
            if (item->count() == 0) return true;
        }
    }

    if (item->count() != 0) {
        for (auto* to : cells_) {
            if (to->item() == nullptr) {
                to->setItem(item);
                return true;
            }
        }
    }

    return false;
}

ItemGroup* Inventory::picked() {
    return picked_;
}

void Inventory::setPicked(ItemGroup* cell) {
    picked_ = cell;
}


Cell* Inventory::current() {
    return current_;
}

void Inventory::makeCurrent(Cell* cell) {
    if (current() == cell) return;
    if (current() != nullptr) {
        current()->setCurrent(false);
    }

    cell->setCurrent(true);

    current_ = cell;

    rebuild();
}

int Inventory::row() const {
    return row_;
}

int Inventory::x() {
    return x_;
}

int Inventory::y() {
    return y_;
}

Cell* Inventory::at(int ind) {
    if (ind >= cells_.size()) throw std::invalid_argument("ERROR! inventory out of bounds");
    return cells_[ind];
}

std::vector<Cell*>& Inventory::cells() {
    return cells_;
}
