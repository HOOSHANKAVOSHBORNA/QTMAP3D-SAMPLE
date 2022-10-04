#include "locationwidget.h"
#include <QQmlEngine>
#include <QQuickWidget>
#include <QQmlContext>
#include <osgEarth/optional>

LocationWidget::LocationWidget(QWidget *parent) : QWidget(parent)
{
    mQQuickWidget = new QQuickWidget(QUrl(QStringLiteral("qrc:/Qml/loactionWidget.qml")),this);
    mQQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    mQQuickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    mQQuickWidget->setClearColor(Qt::transparent);
    mQQuickWidget->resize(230, 60);
    mQQuickWidget->raise();
    setMinimumSize(230,60);
    setMaximumSize(230,300);
    mQQuickWidget->engine()->rootContext()->setContextProperty("Location",this);
    connect(this,&LocationWidget::onCurrentClicked,[=](QString name){
        foreach (osgEarth::Viewpoint i, mListViewpoint) {
            osgEarth::optional<std::string> str = i.name();
            QString tempNamp = QString::fromStdString(str.get());
            if (tempNamp == name){
                onClickedPosition(i);
                break;
            }
        }
    });


    connect(this,&LocationWidget::onOpenWidget,[=](bool a ,bool b , bool c ){
        if (b ){
            mQQuickWidget->resize(230, 300);
            mQQuickWidget->raise();
            resize(230,300);
            raise();
            this->move(0,parent->height() - this->height());

        }else if (a) {
            mQQuickWidget->resize(230, 120);
            mQQuickWidget->raise();
            resize(230,120);
            raise();
            this->move(0,parent->height() - this->height());
        }else if (c){
            mQQuickWidget->resize(230, 120);
            mQQuickWidget->raise();
            resize(230,120);
            raise();
            this->move(0,parent->height() - this->height());
        }
        else{
            mQQuickWidget->resize(230, 60);
            mQQuickWidget->raise();
            resize(230,60);
            raise();
            this->move(0,parent->height() - this->height());
        }



    });
}

void LocationWidget::addViewPoint(osgEarth::Viewpoint point)
{
     osgEarth::optional<std::string> str = point.name();
     QString name = QString::fromStdString(str.get());
     mListViewpoint.append(point);
     double x = point.focalPoint()->x();
     double y = point.focalPoint()->y();
     emit savePosition(name , x ,y);
}

void LocationWidget::setMousePosition(double latitude, double longitude, double altitude)
{
    emit changePosition(latitude , longitude ,altitude);
}
