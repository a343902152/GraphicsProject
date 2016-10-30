#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(700,500);   //主窗口大小设为700*500
    setWindowTitle(tr("实验1直线中点Bresenham算法"));

    area=new PaintArea;
//    ui->textBrowser_pencolor->setPalette(Qt::black);
    scrollArea=new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(area);     //将画布添加到scrollArea中
    scrollArea->widget()->setMinimumSize(800,600);  //scrollArea初始化大小设为800*600
    setCentralWidget(scrollArea);    //将scrollArea加入到主窗口的中心区

}

MainWindow::~MainWindow()
{
    delete ui;
}
