
#include "CrystalWindow.h"
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarth/ImageLayer>

CrystalWindow::CrystalWindow(QWindow *parent) :
    OsgQuickWindow(parent)
{

    QObject::connect(this, &CrystalWindow::initialized,
                     this, &CrystalWindow::initializeOsgEarth,
                     Qt::DirectConnection);

}

CrystalWindow::~CrystalWindow()
{

}

void CrystalWindow::initializeOsgEarth()
{
    constexpr double MIN_DISTANCE{10.0};
    constexpr double MAX_DISTANCE{1000000000.0};
    constexpr double MAX_OFSET{5000.0};

    auto earthManipulator = new osgEarth::Util::EarthManipulator;
    auto settings = earthManipulator->getSettings();
    settings->setSingleAxisRotation(true);
    settings->setMinMaxDistance(MIN_DISTANCE, MAX_DISTANCE);
    settings->setMaxOffset(MAX_OFSET, MAX_OFSET);
    settings->setMinMaxPitch(-90, 90);
    settings->setTerrainAvoidanceEnabled(true);
    settings->setThrowingEnabled(false);

    getViewer()->setCameraManipulator(earthManipulator);

    osgEarth::Drivers::GDALOptions gdal;
    gdal.url() = "/home/client112/Desktop/Hooshan/Crystal/world.tif";
    osg::ref_ptr<osgEarth::ImageLayer> imlayer = new osgEarth::ImageLayer("base-world", gdal);
    osgEarth::MapOptions mapOptGeo;
    mapOptGeo.coordSysType() = osgEarth::MapOptions::CSTYPE_GEOCENTRIC;
    mapOptGeo.profile() = osgEarth::ProfileOptions("global-mercator");

    osgEarth::Map *mp = new osgEarth::Map(mapOptGeo);

    mMapNodeGeo = new osgEarth::MapNode(mp);
    mMapNodeGeo->getMap()->addLayer(imlayer);

    osg::ref_ptr<osgEarth::Util::SkyNode> skyNodeGeo = osgEarth::Util::SkyNode::create( mMapNodeGeo);
    skyNodeGeo->addChild(mMapNodeGeo);

    mMapRoot = new osg::Group();
    mMapRoot->addChild(skyNodeGeo);

    getViewer()->setSceneData(mMapRoot);
}
