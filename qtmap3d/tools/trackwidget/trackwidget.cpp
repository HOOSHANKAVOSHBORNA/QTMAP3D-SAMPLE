#include "trackwidget.h"
#include <QQmlEngine>
#include <QQuickWidget>
#include <QQmlContext>
#include <QJsonObject>
#include <QJsonArray>
TrackWidget::TrackWidget(QWidget *parent)
    : QWidget(parent)

{
    mQQuickWidget = new QQuickWidget(QUrl(QStringLiteral("qrc:/trackwidget/trackwidget.qml")),this);
    mQQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    mQQuickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    mQQuickWidget->setClearColor(Qt::transparent);
    mQQuickWidget->resize(200, 450);
    mQQuickWidget->raise();

    mQQuickWidget->engine()->rootContext()->setContextProperty("DetaliObject",this);
    setMinimumSize(200,450);
    setMaximumSize(200,450);
}

void TrackWidget::addObject(double latitude, double longitude, double height, QString name, QString type, QJsonObject info)
{
    mLatitude = latitude;
    mLongitude = longitude;
    mHeight = height;
    mName = name;
    mType = type;
    QJsonObject obj;
    obj [ "nodeData" ] = info;
    mInfo = obj.value(QString("nodeData"));
    emit objectAdded();
}

void TrackWidget::getChangeCoordinates(QString mname, double latitude, double longitude, double height)
{
    emit chengeCoordinates(mname,latitude,longitude,height);
}

double TrackWidget::getLatitude()
{
    return  mLatitude;
}

double TrackWidget::getLongitude()
{
    return  mLongitude;

}

double TrackWidget::getHeight()
{
    return mHeight;
}

QString TrackWidget::getName()
{
    return mName;
}

QString TrackWidget::getType()
{
    return mType;
}

QJsonValue TrackWidget::getInfo()
{
    return mInfo;
}

void TrackWidget::onClickedCloseMenu()
{
    emit closeMenu();
}

