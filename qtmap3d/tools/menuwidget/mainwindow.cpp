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
    mQQuickWidget = new QQuickWidget(QUrl(QStringLiteral("qrc:/main.qml")),this);
           mQQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
            mQQuickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
            mQQuickWidget->setClearColor(Qt::transparent);

            mQQuickWidget->resize(this->width(), this->height());
            mQQuickWidget->raise();



   /// horizontalLayout creat in ui
   mQQuickWidget->engine()->rootContext()->setContextProperty("NamePlugin",this);
   ui->horizontalLayout->addWidget(mQQuickWidget);
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




