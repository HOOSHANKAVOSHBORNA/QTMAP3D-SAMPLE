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
    mQQuickWidget->resize(300, 300);
    mQQuickWidget->raise();
    setMinimumSize(300,300);
    setMaximumSize(300,300);
    mQQuickWidget->engine()->rootContext()->setContextProperty("Location",this);
}

void LocationWidget::addItemPositio(double latitude, double longitude, double altitude)
{
    emit itemPositionAdd(latitude,longitude ,altitude);
}
