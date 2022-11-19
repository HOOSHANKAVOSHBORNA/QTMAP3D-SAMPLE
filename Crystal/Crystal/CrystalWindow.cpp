
#include "CrystalWindow.h"
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarth/ImageLayer>
#include <iostream>

CrystalWindow::CrystalWindow(QWindow *parent) :
    OsgQuickWindow(parent)
{

}

CrystalWindow::~CrystalWindow()
{

}

void CrystalWindow::keyPressEvent(QKeyEvent *event)
{
    OsgQuickWindow::keyPressEvent(event);
}

