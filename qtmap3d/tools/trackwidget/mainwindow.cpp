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
    mTrackWidget = new TrackWidget(this);
    QJsonObject o1
         {
             { "key", 1 },
             { "colorborder", "#234324" },
            {"colorlink","green"},
             { "color", "red" },
            {"type","1"},
            {"name","سبزوار"},
            {"title","CEO"},
         };
    mTrackWidget->hide();
    mTrackWidget->move(this->width() -200 ,0);
    mTrackWidget->addObject(12.3,123.5444,23.0,"krar","air",o1);
    mTrackWidget->addObject(12.445543,12.5444,23.0,"mbr","machine",o1);
    connect(ui->pushButton_3,&QPushButton::clicked,mTrackWidget,&TrackWidget::onClickedCloseMenu);
    connect(mTrackWidget,&TrackWidget::onPin,[=](bool t){

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

void MainWindow::on_pushButton_clicked()
{
    mTrackWidget->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    double t =rand();
    double a =rand();
    double b =rand();
    mTrackWidget->getChangeCoordinates("krar",a,b,t);
}
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton)
    {
        qDebug() << "Right mouse click!" << endl;
    }
}
