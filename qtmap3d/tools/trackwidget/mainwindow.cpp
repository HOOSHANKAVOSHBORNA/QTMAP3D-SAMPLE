#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDockWidget>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mTrackWidget = new TrackModelWidget(this);
    QJsonObject o1
         {
             { "key", "1" },
             { "area1", "234324" },
            {"type","green"},
             { "sate", "red" },
            {"name","mersad"},
            {"n","سبزوار"},
            {"title","CEO"},
         };
    QJsonObject o2
         {
             { "key", "3" },
             { "area1", "434324" },
            {"type","blue"},
             { "sate", "red" },
            {"name","1"},
            {"n","Tehran"},
            {"title","GEO"},
         };
    mTrackWidget->hide();
    mTrackWidget->move(this->width() -200 ,0);
    mTrackWidget->setMinimaizeWidget(true);
    mTrackWidget->addModel("air","karar");
    mTrackWidget->addModel("mbr","machine");
    mTrackWidget->setModelInfo("air","karar",o1);
    mTrackWidget->setModelInfo("mbr","machine",o2);
    mTrackWidget->setModelPosition("air","karar",53.2334,24.56777,100.88);
    mTrackWidget->setModelPosition("mbr","machine",53.2334,24.33333,1000.888);
    connect(mTrackWidget,&TrackModelWidget::onModelClicked,[=](QString type , QString name){
       qDebug()<<type << name ;
    });
    connect(mTrackWidget,&TrackModelWidget::onPin,[=](bool t){

        if(t){
            mDock = new QDockWidget(this);
            mDock->setWidget(mTrackWidget);

            addDockWidget(Qt::RightDockWidgetArea, mDock);

            mDock->setMaximumWidth(200);
            mDock->setMinimumWidth(200);
            mDock->setMinimumHeight(250);

        }else{
            mDock->deleteLater();
            mTrackWidget->setParent(this);
            mTrackWidget->move(this->width() -200 ,0);
            mTrackWidget->show();
        }



    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    mTrackWidget->setClose();
    QMainWindow::mousePressEvent(event);
}

void MainWindow::on_pushButton_clicked()
{
    if (mTrackWidget->isHidden())
         mTrackWidget->show();
    else
        mTrackWidget->hide();
}

void MainWindow::on_pushButton_2_clicked()
{
    double t =rand();
    double a =rand();
    double b =rand();
   mTrackWidget->removeModel("air","karar");
   i--;
}



void MainWindow::on_pushButton_3_clicked()
{

    mTrackWidget->addModel(QString::number(i),QString::number(i));
    i++;
}
