
#ifndef TOOL_H
#define TOOL_H

#include "item.h";
#include "player.h"
#include <QObject>
#include <QTimer>


class Tool : public Item
{
public:
    Tool(QObject* parent = nullptr);

    double axeDamage();
    void setAxeDamage(double damage);

    double pickaxeDamage();
    void setPickaxeDamage(double damage);

    double swordDamage();
    void setSwordDamage(double damage);

    double useRadius();
    void setUseRadius(double rad);

    int reload();
    void setReload(int rl);

    bool usable();
    void setUsable(bool bl = true);

    void startReload(int msec);

    virtual bool useItem(QPointF pos) override;
    Player* player();
    void setPlayer(Player* player);

public slots:
    void finishReload();

private:
    Player* player_ = nullptr;
    double axeDamage_ = 0;
    double pickaxeDamage_ = 0;
    double swordDamage_ = 0;
    double useRadius_ = 100;
    bool usable_ = true;
    int reload_ = 420;
};

#endif // TOOL_H
