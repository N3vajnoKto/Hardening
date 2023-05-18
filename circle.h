
#ifndef CIRCLE_H
#define CIRCLE_H

#include <QPointF>

class Circle
{
public:
    Circle(double rad = 1, QPointF pnt = {0, 0});
    double& radius();
    QPointF& pos();
private:
    double radius_ = 1;
    QPointF pos_ = {0, 0};
};

#endif // CIRCLE_H
