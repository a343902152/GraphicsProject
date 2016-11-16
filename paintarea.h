#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <iostream>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include<QtGui>
#include<QPaintEvent>
#include<queue>
#include<math.h>
#include<cstring>
using namespace std;

class PaintArea : public QWidget
{
public:
    PaintArea();
    void setBeginColor(QColor color);
    void setEndColor(QColor color);
    void setActionType(string actionType);
    ~PaintArea();

protected:
    void paintEvent(QPaintEvent *);   //重绘事件
    void mousePressEvent(QMouseEvent *);  //鼠标按下事件
    void mouseMoveEvent(QMouseEvent *);   //鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *);   //鼠标释放事件
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);


    void drawPoint(QImage &image,QPoint point,QColor color);
    void drawLine(QImage &image,QPoint beginPoint,QPoint endPoint,QColor beginColor,QColor endColor);
    void fillPolygon(QImage &image,QPoint beginPoint,QColor newColor);
    bool isClose(QPoint firstPoint,QPoint secondPoint,double threshHold);

    void drawBEPoint(QImage &image,QPoint beginPoint,QPoint endPoint);  // 绘制起点、重点及相应说明
    QPoint preDrawLine(QPoint beginPoint,QPoint endPoint); //drawLine之前的预处理，主要针对shift的情况
public:
    QImage curImage;    //QImage类对象，用于在其上绘图
    QImage tempImage; //临时画布

    QRgb backColor;  //QRgb颜色对象，存储image的背景色
    QPoint beginPoint,endPoint;//记录鼠标点击的起点坐标，和放开时的终点坐标
    QPoint ploygonStartPoint;
    QColor beginColor;  // 渐变起点的颜色
    QColor endColor;    // 渐变终点的颜色

    string actionType;
    bool isDrawing; // 用于双重缓冲，判断是否正在绘制
    bool isDrawingPolygon;  // 用于多边形绘制的一个额外的bool值，与idDrawing配合使用
    bool isPressingShift;

    int width;
    int height;

    queue<QPoint> ploygonPointList;
};

#endif // PAINTAREA_H
