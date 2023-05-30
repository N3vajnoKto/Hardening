
#ifndef TOOLPICKAXE_H
#define TOOLPICKAXE_H


#include "tool.h"

class ToolPickaxe : public Tool
{
public:
    explicit ToolPickaxe(QObject *parent = nullptr);
    explicit ToolPickaxe(const ToolPickaxe *parent);

    bool useItem(QPointF pos) override;
    ItemBase* copy() const override;

private:
    bool turn = true;

signals:

};

#endif // TOOLPICKAXE_H
