
#ifndef TOOL_H
#define TOOL_H

#include "item.h";
#include "../player.h"
#include <QObject>
#include <QTimer>


class Tool : public Item
{
public:
    explicit Tool(QObject* parent = nullptr);
    explicit Tool(const Tool* tool);

    Damage damage() const;
    void setDamage(Damage damage);

    double useRadius();
    void setUseRadius(double rad);

    int reload();
    void setReload(int rl);

    bool usable();
    void setUsable(bool bl = true);

    void startReload(int msec);

    virtual bool useItem(QPointF pos) override;
    virtual ItemBase* copy() const override;

public slots:
    void finishReload();

private:
    Damage damage_;
    double useRadius_ = 100;
    bool usable_ = true;
    int reload_ = 420;
};

#endif // TOOL_H
