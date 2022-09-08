#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDockWidget>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mQQuickWidget = new QQuickWidget(QUrl(QStringLiteral("qrc:/main.qml")));
           mQQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
            mQQuickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
            mQQuickWidget->setClearColor(Qt::transparent);
            mQQuickWidget->resize(this->width(), this->height());
            mQQuickWidget->raise();


   /// horizontalLayout creat in ui

   ui->horizontalLayout->addWidget(mQQuickWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


