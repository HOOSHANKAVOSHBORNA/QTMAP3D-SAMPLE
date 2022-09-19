    #include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDockWidget>
#include <QLabel>
#include "QQuickWidget"
#include <QQmlEngine>
#include <QQmlContext>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->dockWidget->setFeatures(ui->dockWidget->features() & ~QDockWidget::DockWidgetClosable);
    //ui->dockWidget->setFeatures(ui->dockWidget->features() & ~QDockWidget::DockWidgetFloatable);
    mListNamePlugin << "name" << "line" << "model"<<"meature" << "dising" << "height" << "image" ;
    mIconPlugin << "qrc:/res/right-r.png";
    mIconPlugin << "qrc:/res/icons8-chevron-right-96.png";
    mIconPlugin << "qrc:/res/icons8-ruler-96.png";
    mIconPlugin << "qrc:/res/icons8-pencil-96.png";
    mIconPlugin << "qrc:/res/icons8-line-chart-96.png";
    mIconPlugin << "qrc:/res/icons8-ruler-96.png";
    mIconPlugin << "qrc:/res/icons8-puzzle-96.png";
    mCategoryPlugin << "Image" << "Trrain" << "Model" << "Meature" << "Designing" << "Measurement" << "Image" ;
    mQQuickWidget = new QQuickWidget(QUrl(QStringLiteral("qrc:/main.qml")),this);
           mQQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
            mQQuickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
            mQQuickWidget->setClearColor(Qt::transparent);

           mQQuickWidget->resize(200, 400);
            //mQQuickWidget->raise();



   /// horizontalLayout creat in ui
   mQQuickWidget->engine()->rootContext()->setContextProperty("NamePlugin",this);
   //ui->verticalLayout->addWidget(mQQuickWidget);
   //ui->horizontalLayout->addWidget(mQQuickWidget);

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

 QVariantList MainWindow::getListNamePlugin()
{
     return mListNamePlugin;
 }




void MainWindow::setListPlugin(const QVariantList &v)
{
    mListNamePlugin=v;
}

QVariantList MainWindow::getListiconPlugin()
{
    return mIconPlugin;
}

QVariantList MainWindow::getLisCategortPlugin()
{
    return mCategoryPlugin;
}

void MainWindow::onGetClicked(QString category, QString name)
{
    //qDebug()<<name << category;
    emit onClickedPlugin(category,name);
}




