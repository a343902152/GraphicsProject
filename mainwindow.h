#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <iostream>
#include<QtGui>
#include<QColorDialog>

#include<queue>
#include "paintarea.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);   //重绘事件
    ~MainWindow();

private slots:
    void on_btn_begincolor_clicked();

    void on_btn_endcolor_clicked();

private:
    Ui::MainWindow *ui;
    PaintArea *area;
    QScrollArea *scrollArea;
};

#endif // MAINWINDOW_H
