
#include "circle.h"

Circle::Circle(double rad, QPointF pnt)
{
    radius_ = rad;
    pos_ = pnt;
}


double& Circle::radius() {

    return radius_;

}
QPointF& Circle::pos() {
    return pos_;

}
