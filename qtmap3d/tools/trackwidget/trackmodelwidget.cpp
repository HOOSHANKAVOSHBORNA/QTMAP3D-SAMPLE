#include "trackmodelwidget.h"
#include <QQmlEngine>
#include <QQuickWidget>
#include <QQmlContext>
#include <QJsonObject>
#include <QJsonArray>
TrackModelWidget::TrackModelWidget(QWidget *parent)
    : QWidget(parent)

{
    mQQuickWidget = new QQuickWidget(QUrl(QStringLiteral("qrc:/trackwidget/trackwidget.qml")),this);
    mQQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    mQQuickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    mQQuickWidget->setClearColor(Qt::transparent);
    mQQuickWidget->resize(200, 420);
    mQQuickWidget->raise();
    //
    mQQuickWidget->engine()->rootContext()->setContextProperty("DetaliObject",this);
    connect(this,&TrackModelWidget::changeSize,[=](bool t){
        if(t){
            resize(200,420);
            raise();
        }else
            resize(200,40);
            raise();
    });

    //    setMaximumSize(200,450);
}

void TrackModelWidget::addModel( QString type, QString name)
{

    emit modelAdded(type,name);
}

void TrackModelWidget::setModelPosition(QString t, QString n, double latitude, double longitude, double altitude)
{
    emit modelPosition(t,n,latitude,longitude,altitude);
}

void TrackModelWidget::setClose()
{
    emit close();
}

void TrackModelWidget::setModelInfo(QString type , QString name,QJsonObject info)
{
    QStringList keyInfo;
    QStringList valueInfo;

    keyInfo = info.keys();
    foreach (QString i, info.keys()) {
        valueInfo.append(info.value(i).toString());
    }
    QString string= stringListToString(keyInfo,valueInfo);
    modelInfo(type,name,string);
}

void TrackModelWidget::setMinimaizeWidget(bool isMax)
{
    emit minimize(isMax);
}

QString TrackModelWidget::stringListToString(QStringList key, QStringList value)
{
    QString string ;
    for (int i=0;i<key.length();++i) {
        string+=key[i] + " : " + value[i];
        string=string + "\n";
    }
    return  string;
}

void TrackModelWidget::getIsClicked(QString type, QString name)
{
    emit onModelClicked(type,name);
}

void TrackModelWidget::setChangeSize(bool t)
{
    emit changeSize(t);
}











