
#ifndef TOOLAXE_H
#define TOOLAXE_H


#include "tool.h";


class ToolAxe : public Tool
{
    Q_OBJECT
public:
    explicit ToolAxe(QObject *parent = nullptr);

    bool useItem(QPointF pos) override;

private:
    bool turn = true;

signals:

};

#endif // TOOLAXE_H
