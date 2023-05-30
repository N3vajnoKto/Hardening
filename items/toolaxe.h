
#ifndef TOOLAXE_H
#define TOOLAXE_H


#include "tool.h";


class ToolAxe : public Tool
{
public:
    explicit ToolAxe(QObject *parent = nullptr);
    explicit ToolAxe(const ToolAxe *parent);

    bool useItem(QPointF pos) override;
    ItemBase* copy() const override;

private:
    bool turn = true;

signals:

};

#endif // TOOLAXE_H
