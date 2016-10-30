#ifndef MYPOINT2_H
#define MYPOINT2_H


class MyPoint2
{
public:
    MyPoint2();
    MyPoint2(double x,double y);
    ~MyPoint2();

    double getX();
    double getY();
public:
    double x;
    double y;
};

#endif // MYPOINT2_H
