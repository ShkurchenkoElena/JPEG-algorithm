#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{   Image image("F:/zhivotnoye.jpg",200);
    image.jpeg();
    QImage im1=image.getIm();
    QImage im2=image.getOldIm();
    im1.save("F:/Result/new_zhivotnoye(k=200).jpg");
    QPainter painter(this);


    painter.drawImage(0,0, im2.scaled(this->width()/2,this->height()));
    painter.drawImage(this->width()/2,0,im1.scaled(this->width()/2,this->height()));

}
