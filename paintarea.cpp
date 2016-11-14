#include "paintarea.h"

PaintArea::PaintArea()
{
    width=300;
    height=200;
    curImage = QImage(width,height,QImage::Format_RGB32);  //画布的初始化大小设为400*300，使用32位颜色

    backColor = qRgb(255,255,255);    //画布初始化背景色使用白色
    curImage.fill(backColor);//对画布进行填充
    tempImage=curImage;  // tmp画布是cur画布的复制

    beginColor=Qt::red;
    endColor=Qt::blue;

    isDrawing=false;

    actionType="fillPolygon";
}

/**
 * 界面重绘事件，每当界面发生变化时会被调用
 * @brief PaintArea::paintEvent
 */
void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    cout<<"paintenven"<<endl;
    painter.drawImage(0,0,curImage);

//    if(isDrawing){
//        painter.drawImage(0,0,tempImage);
//    }else{
//        painter.drawImage(0,0,curImage);
//    }
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
    QPainter painter(&image);   //在theImage上绘图
//    cout<<"drawPoint"<<point.x()<<","<<point.y()<<endl;
    QPen pen;
    pen.setColor(color);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);

    painter.setPen(pen);
    painter.drawPoint(point);
    repaint();   //进行更新界面显示，可引起窗口重绘事件，重绘窗口
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
                d-=(1+k);
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
 * 填充多边形的算法
 * 首先设置一个填充颜色，然后以当前坐标点的bgcolor为底色，以其他颜色为边界。
 * @brief PaintArea::fillPolygon
 * @param image
 * @param beginPoint
 * @param newColor
 */
void PaintArea::fillPolygon(QImage &image, QPoint beginPoint, QColor newColor){
    QColor backgroundColor=image.pixel(beginPoint);
    cout<<"fill"<<endl;

    queue<QPoint> pointQueue;
    if(newColor!=backgroundColor){
        pointQueue.push(beginPoint);
    }
    int count=0;
    int vis[width+5][height+5];
    memset(vis,0,sizeof(vis));

    int dir[4][2]={{1,0}, {-1,0} ,{0,1}, {0,-1}};
    while(!pointQueue.empty()){
        count++;

        QPoint curPoint=pointQueue.front();
        pointQueue.pop();
        drawPoint(image,curPoint,newColor);

        int x=curPoint.x();
        int y=curPoint.y();
        int tx=x;
        int ty=y;

        // fixme: 某个点还未drawpoint，但是其颜色已经提前变成目标颜色，导致新的点不能加到队列中去
        for(int i=0;i<4;i++){
            tx=x+dir[i][0];
            ty=y+dir[i][1];
//            cout<<tx<<","<<ty<<endl;
            if(tx>=0 && tx<width && ty>=0 && ty <height&&!vis[tx][ty]){
                // 不管要不要填充，都设置为vis
                vis[tx][ty]=1;
                QPoint newPoint(tx,ty);
                QColor tmpColor=(QColor)(image.pixel(newPoint));
                if(tmpColor==backgroundColor){
//                    cout<<"push"<<tx<<","<<ty<<endl;
                    pointQueue.push(newPoint);
                }
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
        isDrawing=true;
        beginPoint = event->pos();   //获得鼠标指针的当前坐标作为起始坐标

        //当前点击位置的横纵坐标
        int x=beginPoint.x();
        int y=beginPoint.y();
    }
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)   //如果鼠标左键按着的同时移动鼠标
    {
        endPoint = event->pos();  //获得鼠标指针的当前坐标作为终止坐标
        int x=endPoint.x();
        int y=endPoint.y();

        if(isDrawing){
            tempImage=curImage;            
            if(actionType=="temp"){

            }else{
                drawBEPoint(tempImage,beginPoint,endPoint);
                drawLine(tempImage,beginPoint,endPoint,beginColor,endColor);
            }
        }
    }
}


void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
   if(event->button() == Qt::LeftButton)   //如果鼠标左键释放
   {
       isDrawing=false;
       endPoint = event->pos();
       int x=endPoint.x();
       int y=endPoint.y();

       if(actionType=="fillPolygon"){
           fillPolygon(curImage,beginPoint,endColor);
       }else{
           drawLine(curImage,beginPoint,endPoint,beginColor,endColor);
       }
   }

}


/**
  绘制起点和终点的坐标
 * @brief PaintArea::drawBEPoint
 * @param image
 * @param beginPoint
 * @param endPoint
 */
void PaintArea::drawBEPoint(QImage &image, QPoint beginPoint, QPoint endPoint){
    QPainter painter(&image);

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(5);

    painter.setPen(pen);
    painter.drawPoint(beginPoint);
    painter.drawPoint(endPoint);

    pen.setColor(Qt::black);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawText(beginPoint,"("+QString::number(beginPoint.x())+","+QString::number(beginPoint.y())+")");
    painter.drawText(endPoint,"("+QString::number(endPoint.x())+","+QString::number(endPoint.y())+")");
}

void PaintArea::setBeginColor(QColor color){
    this->beginColor=color;
}

void PaintArea::setEndColor(QColor color){
    this->endColor=color;
}

PaintArea::~PaintArea()
{

}

