
#ifndef AXEOBJECT_H
#define AXEOBJECT_H


#include "toolobject.h"
#include "player.h"
#include <QTimer>

class ObjectAxe : public ToolObject
{
public:
    explicit ObjectAxe(QObject* parent);
    QPointF dir_ = {0, 0};
    void live() override;
    void setAngle(double ang);
private:
    double ang_ = 0.1;
};

#endif // AXEOBJECT_H
