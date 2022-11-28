
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

    QObject::connect(this, &CrystalWindow::homeButtonClicked,
                     m_pMapController, &CrystalMapController::goToHome);
    QObject::connect(this, &CrystalWindow::projectionButtonClicked,
                     m_pMapController, &CrystalMapController::toggleProjection);


    QObject::connect(this, &CrystalWindow::upButtonClicked,
                     m_pMapController, &CrystalMapController::panUp);
    QObject::connect(this, &CrystalWindow::downButtonClicked,
                     m_pMapController, &CrystalMapController::panDown);
    QObject::connect(this, &CrystalWindow::leftButtonClicked,
                     m_pMapController, &CrystalMapController::panLeft);
    QObject::connect(this, &CrystalWindow::rightButtonClicked,
                     m_pMapController, &CrystalMapController::panRight);


    QObject::connect(this, &CrystalWindow::rotateUpButtonClicked,
                     m_pMapController, &CrystalMapController::rotateUp);
    QObject::connect(this, &CrystalWindow::rotateDownButtonClicked,
                     m_pMapController, &CrystalMapController::rotateDown);
    QObject::connect(this, &CrystalWindow::rotateLeftButtonClicked,
                     m_pMapController, &CrystalMapController::rotateLeft);
    QObject::connect(this, &CrystalWindow::rotateRightButtonClicked,
                     m_pMapController, &CrystalMapController::rotateRight);


    QObject::connect(this, &CrystalWindow::zoomInButtonClicked,
                     m_pMapController, &CrystalMapController::zoomIn);
    QObject::connect(this, &CrystalWindow::zoomOutButtonClicked,
                     m_pMapController, &CrystalMapController::zoomOut);

    QObject::connect(m_pMapController, &CrystalMapController::headingAngleChanged,
                     this, &CrystalWindow::setHeadingAngle);
}

CrystalWindow::~CrystalWindow()
{

}

qreal CrystalWindow::headingAngle() const
{
    return m_headingAngle;
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
                item.sideItemIndex = idx;
            }
        }

        for (auto& toolboxItem : item.qmlDesc->toolboxItemsList) {


            QVariant ret;
            QMetaObject::invokeMethod(this,
                                      "addToolboxItem",
                                      Qt::DirectConnection,
                                      Q_RETURN_ARG(QVariant, ret),
                                      Q_ARG(QVariant, QVariant::fromValue<QString>(toolboxItem.name)),
                                      Q_ARG(QVariant, QVariant::fromValue<QString>(toolboxItem.category)),
                                      Q_ARG(QVariant, QVariant::fromValue<QString>(toolboxItem.iconUrl)),
                                      Q_ARG(QVariant, QVariant::fromValue<bool>(toolboxItem.checkable))
                                      );
             bool bOk = false;
            const int idx = ret.toInt(&bOk);
            if (bOk) {
                emit toolboxItemCreated(toolboxItem.name, toolboxItem.category, item.pInterface);
            }
        }
    }
}

void CrystalWindow::setHeadingAngle(qreal angle)
{
    if (m_headingAngle != angle) {
        m_headingAngle = angle;
        emit headingAngleChanged(angle);
    }
}


void CrystalWindow::keyPressEvent(QKeyEvent *event)
{
    OsgQuickWindow::keyPressEvent(event);
}
