#include "trackwidget.h"
#include <QQmlEngine>
#include <QQuickWidget>
#include <QQmlContext>
TrackWidget::TrackWidget(QWidget *parent)
    : QWidget(parent)

{
    mQQuickWidget = new QQuickWidget(QUrl(QStringLiteral("qrc:/trackwidget/trackwidget.qml")),this);
            mQQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
            mQQuickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
            mQQuickWidget->setClearColor(Qt::transparent);
            mQQuickWidget->resize(200, 450);
            mQQuickWidget->raise();

     mQQuickWidget->engine()->rootContext()->setContextProperty("NamePlugin",this);
     setMinimumSize(200,450);
     setMaximumSize(200,450);
}

