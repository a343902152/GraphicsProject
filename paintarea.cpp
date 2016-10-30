#include "paintarea.h"

PaintArea::PaintArea()
{
    curImage = QImage(400,300,QImage::Format_RGB32);  //画布的初始化大小设为400*300，使用32位颜色

    backColor = qRgb(255,255,255);    //画布初始化背景色使用白色
    curImage.fill(backColor);//对画布进行填充
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
        cout<<x<<" "<<y<<endl;
    }

}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)   //如果鼠标左键按着的同时移动鼠标
    {
        endPoint = event->pos();  //获得鼠标指针的当前坐标作为终止坐标
        int x=endPoint.x();
        int y=endPoint.y();
        cout<<x<<" "<<y<<endl;
    }
}


void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
   if(event->button() == Qt::LeftButton)   //如果鼠标左键释放
   {
       endPoint = event->pos();
       int x=endPoint.x();
       int y=endPoint.y();
       cout<<x<<" "<<y<<endl;
   }
}
PaintArea::~PaintArea()
{

}

