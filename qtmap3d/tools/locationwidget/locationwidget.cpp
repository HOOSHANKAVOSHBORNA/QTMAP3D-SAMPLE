#include "locationwidget.h"
#include <QQmlEngine>
#include <QQuickWidget>
#include <QQmlContext>

LocationWidget::LocationWidget(QWidget *parent) : QWidget(parent)
{
    mQQuickWidget = new QQuickWidget(QUrl(QStringLiteral("qrc:/Qml/loactionWidget.qml")),this);
    mQQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    mQQuickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    mQQuickWidget->setClearColor(Qt::transparent);
    mQQuickWidget->resize(300, 60);
    mQQuickWidget->raise();
    setMinimumSize(300,60);
    setMaximumSize(300,300);
    mQQuickWidget->engine()->rootContext()->setContextProperty("Location",this);

    connect(this,&LocationWidget::onOpenWidget,[=](bool t ,bool c ){
        if (t && c){
            mQQuickWidget->resize(300, 300);
            mQQuickWidget->raise();
            resize(300,300);
            raise();
            this->move(0,parent->height() - this->height());

        }else if (t && !c) {
            mQQuickWidget->resize(300, 100);
            mQQuickWidget->raise();
            resize(300,100);
            raise();
            this->move(0,parent->height() - this->height());
        } else if (!t && c){
            mQQuickWidget->resize(300, 300);
            mQQuickWidget->raise();
            resize(300,300);
            raise();
            this->move(0,parent->height() - this->height());
        }

        else{
            mQQuickWidget->resize(300, 60);
            mQQuickWidget->raise();
            resize(300,60);
            raise();
            this->move(0,parent->height() - this->height());
        }



    });
}

void LocationWidget::addItemPositio(double latitude, double longitude, double altitude)
{
    emit itemPositionAdd(latitude,longitude ,altitude);
}
