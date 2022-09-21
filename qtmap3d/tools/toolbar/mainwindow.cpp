#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "toolbarwidget.h"
#include "QDebug"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mToolBar = new ToolBarWidget(this);
    mToolBar->addItem("data","qrc:/res/icons8-location-96.png","File");
    mToolBar->addItem("image","qrc:/res/icons8-location-96.png","Image");
    mToolBar->addItem("t","qrc:/res/icons8-location-96.png","Analyze");

       connect(mToolBar,&ToolBarWidget::onClickedPlugin,[=](QString category ,QString name){
            qDebug()<<category << name;
       });
          connect(mToolBar,&ToolBarWidget::onPin,[=](bool t){
                       if(t){
                           mDock = new QDockWidget(this);
                           mDock->setWidget(mToolBar);

                           addDockWidget(Qt::RightDockWidgetArea, mDock);

                           mDock->setMaximumWidth(200);
                           mDock->setMinimumWidth(200);
                           mDock->setMinimumHeight(250);

                       }else{
                           mDock->deleteLater();
                           mToolBar->setParent(this);
                           mToolBar->show();
                       }



               });


}

MainWindow::~MainWindow()
{
    delete ui;
}
