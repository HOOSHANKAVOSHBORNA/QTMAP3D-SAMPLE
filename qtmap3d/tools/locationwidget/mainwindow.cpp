#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "locationwidget.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mLocationWidget = new LocationWidget(this);


    mLocationWidget->addItemPositio(123.546,21.342,411.13331);
    mLocationWidget->addItemPositio(123.546,21.342,411.13331);
    mLocationWidget->addItemPositio(123.546,21.342,411.13331);

    connect(mLocationWidget,&LocationWidget::goPosition,[=](float lat ,float lan){
       qDebug()<<lat << lan;

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    mLocationWidget->move(0,this->height()- mLocationWidget->height());
}

