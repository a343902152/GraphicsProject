#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800,600);   //主窗口大小设为700*500
    setWindowTitle(tr("实验1直线中点Bresenham算法"));

    // 把画布添加到界面中
    area=new PaintArea;
    scrollArea=new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(area);     //将画布添加到scrollArea中
    scrollArea->widget()->setMinimumSize(800,600);  //scrollArea初始化大小设为800*600
    setCentralWidget(scrollArea);    //将scrollArea加入到主窗口的中心区


    // 初始化画笔颜色界面
    QPalette palette = ui->textBrowser_begincolor->palette();
    palette.setColor(QPalette::Base,area->beginColor);
    ui->textBrowser_begincolor->setPalette(palette);

    palette = ui->textBrowser_endcolor->palette();
    palette.setColor(QPalette::Base,area->endColor);
    ui->textBrowser_endcolor->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_begincolor_clicked()
{
    //设置起点画笔颜色
    QColor newColor = QColorDialog::getColor();  //从颜色对话框获得颜色
    if (newColor.isValid())   //如果得到的是可用的颜色
    {
        area->setBeginColor(newColor);
        QPalette palette = ui->textBrowser_begincolor->palette(); //显示这个颜色
        palette.setColor(QPalette::Base,newColor);
        ui->textBrowser_begincolor->setPalette(palette);
        update();
    }
}

void MainWindow::on_btn_endcolor_clicked()
{
    //设置终点颜色
    QColor newColor = QColorDialog::getColor();  //从颜色对话框获得颜色
    if (newColor.isValid())   //如果得到的是可用的颜色
    {
        area->setEndColor(newColor);
        QPalette palette = ui->textBrowser_endcolor->palette(); //显示这个颜色
        palette.setColor(QPalette::Base,newColor);
        ui->textBrowser_endcolor->setPalette(palette);
        update();
    }
}
