    #include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDockWidget>
#include <QLabel>
#include "QQuickWidget"
#include <QQmlEngine>
#include <QQmlContext>

MainWindow::MainWindow( QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->dockWidget->setFeatures(ui->dockWidget->features() & ~QDockWidget::DockWidgetClosable);
    //ui->dockWidget->setFeatures(ui->dockWidget->features() & ~QDockWidget::DockWidgetFloatable);

    mQQuickWidget = new QQuickWidget(QUrl(QStringLiteral("qrc:/main.qml")),this);
            mQQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
            mQQuickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
            mQQuickWidget->setClearColor(Qt::transparent);
            mQQuickWidget->resize(200, 400);
            //mQQuickWidget->raise();



   /// horizontalLayout creat in ui
   mQQuickWidget->engine()->rootContext()->setContextProperty("NamePlugin",this);

   connect(this,&MainWindow::onPin,[=](bool t){
                if(t){
                    mDock = new QDockWidget(this);
                    mDock->setWidget(mQQuickWidget);
                    addDockWidget(Qt::RightDockWidgetArea, mDock);
                    mDock->setMaximumWidth(200);
                    mDock->setMinimumWidth(200);
                    mDock->setMinimumHeight(250);
                }else{
                    mDock->deleteLater();
                    mQQuickWidget->setParent(this);
                    mQQuickWidget->show();
                }



        });
   connect(this,&MainWindow::onClickedPlugin,[=](QString category ,QString name){
        qDebug()<<category << name;
   });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setPlugin(QString name, QString icon, QString category)
{
    mNamePlugin = name;
    mIconPlugin = icon;
    mCategoryPlugin = category;
    taggel();
}

 QVariant MainWindow::getNamePlugin()
{
     return mNamePlugin;
 }




QVariant MainWindow::getIconPlugin()
{
    return mIconPlugin;
}

QVariant MainWindow::getCategortPlugin()
{
    return mCategoryPlugin;
}

void MainWindow::onGetClicked(QString category, QString name)
{
    //qDebug()<<name << category;
    emit onClickedPlugin(category,name);
}




