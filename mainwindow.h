
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QkeyEvent>
#include <QMouseEvent>
#include <QTimer>
#include "screen.h"
#include "controller.h"


class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void focusScreen();

private:
    Screen* screen_;
    Controller* controller;
    QTimer* timer;

};

#endif // MAINWINDOW_H
