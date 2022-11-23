
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarth/ImageLayer>
#include <osgGA/GUIEventAdapter>
#include <iostream>

#include "CrystalWindow.h"
#include "CrystalPluginManager.h"

CrystalWindow::CrystalWindow(QWindow *parent) :
    OsgQuickWindow(parent)
{

}

CrystalWindow::~CrystalWindow()
{

}

void CrystalWindow::initializePluginsUI(std::list<CrystalPluginInfo> pluginsInfoList)
{
    for (auto& item : pluginsInfoList) {

        if (item.qmlDesc->bPluginHasSideItem) {
            QVariant ret;
            QMetaObject::invokeMethod(this,
                                      "addSideItem",
                                      Qt::DirectConnection,
                                      Q_RETURN_ARG(QVariant, ret),
                                      Q_ARG(QVariant, QVariant::fromValue<QString>(item.qmlDesc->strSideItemMenuBarTitle)),
                                      Q_ARG(QVariant, QVariant::fromValue<QString>(item.qmlDesc->strSideItemMenuBarIconUrl)),
                                      Q_ARG(QVariant, QVariant::fromValue<QString>(item.qmlDesc->strSideItemUrl))
                                      );

            bool bOk = false;
            const int idx = ret.toInt(&bOk);
            if (bOk) {
                item.index = idx;
            }
        }
    }
}

void CrystalWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {

    }
}
