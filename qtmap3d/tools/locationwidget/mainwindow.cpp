#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "locationwidget.h"
#include "QDebug"
#include "osgEarth/Utils"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mLocationWidget = new LocationWidget(this);

    osgEarth::Viewpoint test("Tehran", 22.34, 2234.56, 2344.5, 243234,22,123);
    osgEarth::Viewpoint test1("karaj", 24.34, 11.56, 33.5, 3,22,123);
    mLocationWidget->addViewPoint(test);
    mLocationWidget->addViewPoint(test1);

    connect(mLocationWidget,&LocationWidget::onClickedPosition,[=](osgEarth::Viewpoint point){
        std::string  a = point.toString();
        QString str = QString::fromStdString(a);
        qDebug()<<str;
    });
    connect(mLocationWidget,&LocationWidget::goPosition,[=](float lat ,float lan , float range){
       qDebug()<<lat << lan << range;

    });
    connect(mLocationWidget,&LocationWidget::sendNamePosition,[=](QString name){
       qDebug()<<name;
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


void MainWindow::on_pushButton_clicked()
{
    double a =rand();
    double b = rand();
    double c = rand();
    mLocationWidget->setMousePosition(a,b,c);
}
