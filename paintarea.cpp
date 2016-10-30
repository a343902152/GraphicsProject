#include "paintarea.h"

PaintArea::PaintArea()
{
    curImage = QImage(400,300,QImage::Format_RGB32);  //画布的初始化大小设为400*300，使用32位颜色

    backColor = qRgb(255,255,255);    //画布初始化背景色使用白色
    curImage.fill(backColor);//对画布进行填充

    beginColor=Qt::red;
    endColor=Qt::green;
}

/**
 * 界面重绘事件，每当界面发生变化时会被调用
 * @brief PaintArea::paintEvent
 */
void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);


    painter.drawImage(0,0,curImage);
}

/**
 *
 * 最基础的绘制某个像素点的方法
 * drawLine等方法需要重复调用此方法
 * @brief PaintArea::drawPoint
 * @param image
 * @param point
 */
void PaintArea::drawPoint(QImage &image,QPoint point,QColor color){
//    cout<<"drawPoint x="<<point.x()<<",y="<<point.y()<<endl;
    QPainter painter(&image);   //在theImage上绘图

    QPen pen;
    pen.setColor(color);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);

    painter.setPen(pen);
    painter.drawPoint(point);
    update();   //进行更新界面显示，可引起窗口重绘事件，重绘窗口
}

/**
 *
 * 自定义的应用直线中点Bresenham算法实现的绘制直线方法
 * @brief PaintArea::drawLine
 * @param image
 * @param beginPoint
 * @param endPoint
 */
void PaintArea::drawLine(QImage &image,QPoint beginPoint,QPoint endPoint,
                        QColor beginColor,QColor endColor){
    cout<<"drawLine"<<endl;
    QColor curColor=beginColor;
    QPoint curPoint;

    // k要乘以-1是因为QT坐标轴中y轴向下为正
    double k=-(endPoint.y()-beginPoint.y())*1.0/(endPoint.x()-beginPoint.x());
    cout<<k<<endl;
    double d;
    // 绘制0<K<1
    int colorCount=0;
    if(0<=k && k<=1){
        if(beginPoint.x()>endPoint.x()){
            QPoint t=beginPoint;
            beginPoint=endPoint;
            endPoint=t;

            QColor tc=beginColor;
            beginColor=endColor;
            endColor=tc;
        }
        double offsetRed=(endColor.red()-beginColor.red())*1.0/(endPoint.x()-beginPoint.x());
        double offsetGreen=(endColor.green()-beginColor.green())*1.0/(endPoint.x()-beginPoint.x());
        double offsetBlue=(endColor.blue()-beginColor.blue())*1.0/(endPoint.x()-beginPoint.x());
        d=0.5-k;
        for(curPoint=beginPoint;curPoint.x()<endPoint.x();curPoint.setX(curPoint.x()+1)){
            curColor=qRgb((int)beginColor.red()+(offsetRed*colorCount),
                          (int)beginColor.green()+(offsetGreen*colorCount++),
                          (int)beginColor.blue()+(offsetBlue*colorCount));
            drawPoint(image,curPoint,curColor);
            if(d<0){
                // 受QT坐标轴影响，原有的y+=1转变成y-=1
                curPoint.setY(curPoint.y()-1);
                d+=(1-k);
            }else{
                d-=k;
            }
        }
    }else if(k>1){
        // 受QT坐标系影响，y轴大于小于号相反
        if(beginPoint.y()<endPoint.y()){
            QPoint t=beginPoint;
            beginPoint=endPoint;
            endPoint=t;

            QColor tc=beginColor;
            beginColor=endColor;
            endColor=tc;
        }
        double offsetRed=(endColor.red()-beginColor.red())*1.0/(beginPoint.y()-endPoint.y());
        double offsetGreen=(endColor.green()-beginColor.green())*1.0/(beginPoint.y()-endPoint.y());
        double offsetBlue=(endColor.blue()-beginColor.blue())*1.0/(beginPoint.y()-endPoint.y());
        d=1-0.5*k;

        // 受QT坐标轴影响，大小与符号相反，原有的y+=1转变成y-=1
        for(curPoint=beginPoint;curPoint.y()>endPoint.y();curPoint.setY(curPoint.y()-1)){
            curColor=qRgb((int)beginColor.red()+(offsetRed*colorCount),
                          (int)beginColor.green()+(offsetGreen*colorCount++),
                          (int)beginColor.blue()+(offsetBlue*colorCount));
            drawPoint(image,curPoint,curColor);
            if(d>=0){
                curPoint.setX(curPoint.x()+1);
                d+=(1-k);
            }else{
                d+=1;
            }
        }
    }else if(k>=-1&&k<0){
        if(beginPoint.x()>endPoint.x()){
            QPoint t=beginPoint;
            beginPoint=endPoint;
            endPoint=t;

            QColor tc=beginColor;
            beginColor=endColor;
            endColor=tc;
        }
        double offsetRed=(endColor.red()-beginColor.red())*1.0/(endPoint.x()-beginPoint.x());
        double offsetGreen=(endColor.green()-beginColor.green())*1.0/(endPoint.x()-beginPoint.x());
        double offsetBlue=(endColor.blue()-beginColor.blue())*1.0/(endPoint.x()-beginPoint.x());
        d=-0.5-k;
        for(curPoint=beginPoint;curPoint.x()<endPoint.x();curPoint.setX(curPoint.x()+1)){
            curColor=qRgb((int)beginColor.red()+(offsetRed*colorCount),
                          (int)beginColor.green()+(offsetGreen*colorCount++),
                          (int)beginColor.blue()+(offsetBlue*colorCount));
            drawPoint(image,curPoint,curColor);
            if(d>0){
                // 受QT坐标轴影响，原有的y-=1转变成y+=1
                curPoint.setY(curPoint.y()+1);
                d-=(1-k);
            }else{
                d-=k;
            }
        }
    }else{
        // 受QT坐标系影响，y轴大于小于号相反
        if(beginPoint.y()>endPoint.y()){
            QPoint t=beginPoint;
            beginPoint=endPoint;
            endPoint=t;

            QColor tc=beginColor;
            beginColor=endColor;
            endColor=tc;
        }
        double offsetRed=(endColor.red()-beginColor.red())*1.0/(endPoint.y()-beginPoint.y());
        double offsetGreen=(endColor.green()-beginColor.green())*1.0/(endPoint.y()-beginPoint.y());
        double offsetBlue=(endColor.blue()-beginColor.blue())*1.0/(endPoint.y()-beginPoint.y());
        d=-1-0.5*k;

        // 受QT坐标轴影响，大小与符号相反，原有的y+=1转变成y-=1
        for(curPoint=beginPoint;curPoint.y()<endPoint.y();curPoint.setY(curPoint.y()+1)){
            curColor=qRgb((int)beginColor.red()+(offsetRed*colorCount),
                          (int)beginColor.green()+(offsetGreen*colorCount++),
                          (int)beginColor.blue()+(offsetBlue*colorCount));
            drawPoint(image,curPoint,curColor);
            if(d<0){
                curPoint.setX(curPoint.x()+1);
                d-=(1+k);
            }else{
                d-=1;
            }
        }
    }
}


/**
 * 每当鼠标点击(不是松开)时会调用
 * @brief PaintArea::mousePressEvent
 * @param event
 */
void PaintArea::mousePressEvent(QMouseEvent *event)//只区分是拖动还是绘制新图像操作
{
    if(event->button() == Qt::LeftButton)  //当鼠标左键按下
    {
        beginPoint = event->pos();   //获得鼠标指针的当前坐标作为起始坐标

        //当前点击位置的横纵坐标
        int x=beginPoint.x();
        int y=beginPoint.y();
//        drawPoint(curImage,beginPoint);

    }

}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)   //如果鼠标左键按着的同时移动鼠标
    {
        endPoint = event->pos();  //获得鼠标指针的当前坐标作为终止坐标
        int x=endPoint.x();
        int y=endPoint.y();
    }
}


void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
   if(event->button() == Qt::LeftButton)   //如果鼠标左键释放
   {
       endPoint = event->pos();
       int x=endPoint.x();
       int y=endPoint.y();
       drawLine(curImage,beginPoint,endPoint,beginColor,endColor);
   }

}
PaintArea::~PaintArea()
{

}

