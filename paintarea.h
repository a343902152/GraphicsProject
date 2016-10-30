#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <iostream>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include<QtGui>
#include<QPaintEvent>
using namespace std;

class PaintArea : public QWidget
{
public:
    PaintArea();
    ~PaintArea();

protected:
    void paintEvent(QPaintEvent *);   //重绘事件
    void mousePressEvent(QMouseEvent *);  //鼠标按下事件
    void mouseMoveEvent(QMouseEvent *);   //鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *);   //鼠标释放事件

    void drawPoint(QImage &image,QPoint point,QColor color);
    void drawLine(QImage &image,QPoint beginPoint,QPoint endPoint,QColor beginColor,QColor endColor);
private:
    QImage curImage;    //QImage类对象，用于在其上绘图
    QImage tempImage; //临时画布

    QRgb backColor;  //QRgb颜色对象，存储image的背景色
    QPoint beginPoint,endPoint;//记录鼠标点击的起点坐标，和放开时的终点坐标
    QColor beginColor;  // 渐变起点的颜色
    QColor endColor;    // 渐变终点的颜色

    bool isDrawing; // 用于双重缓冲，判断是否正在绘制
};

#endif // PAINTAREA_H
