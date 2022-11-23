
#include <iostream>

#include "CrystalMapController.h"
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarth/ImageLayer>
#include <osgEarthUtil/Sky>


osgViewer::Viewer *CrystalMapController::getViewer()
{
    return dynamic_cast<osgViewer::Viewer*>(m_pOsgRenderer);
}

CrystalMapController::CrystalMapController(QQuickWindow *window) :
    m_pWindow(window)
{

}

CrystalMapController::~CrystalMapController()
{

}

void CrystalMapController::cleanup()
{
    if (m_pOsgRenderer) {
        m_pOsgRenderer->deleteLater();
        m_pOsgRenderer = nullptr;
    }
}

void CrystalMapController::initializeGL(int width, int height, QScreen *screen, GLuint renderTargetId)
{
    //std::cout << "one" << std::endl;

    m_renderTargetId = renderTargetId;

    createOsgRenderer(width, height, screen);

    if(m_pWindow) {
        QObject::connect(m_pOsgRenderer, &OSGRenderer::needsUpdate,
                         m_pWindow, &QQuickWindow::update,
                         Qt::DirectConnection);
    }
}

void CrystalMapController::resizeGL(int width, int height, QScreen *screen)
{
    if (m_pOsgRenderer) {
        const float pixelRatio = static_cast<float>(screen->devicePixelRatio());
        m_pOsgRenderer->resize(0, 0, width, height, pixelRatio);
    }
}

void CrystalMapController::paintGL()
{
    if (m_pOsgRenderer) {
        if (m_isFirstFrame) {
            m_isFirstFrame = false;
            m_pOsgRenderer->getCamera()->getGraphicsContext()->setDefaultFboId(m_renderTargetId);
        }

        m_pOsgRenderer->frame();
    }
}

void CrystalMapController::keyPressEvent(QKeyEvent *event)
{
    if (m_pOsgRenderer)
        m_pOsgRenderer->keyPressEvent(event);
}

void CrystalMapController::keyReleaseEvent(QKeyEvent *event)
{

    if (m_pOsgRenderer)
        m_pOsgRenderer->keyReleaseEvent(event);
}

void CrystalMapController::mousePressEvent(QMouseEvent *event)
{
    if (m_pOsgRenderer) {
        m_pOsgRenderer->mousePressEvent(event);
    }

}

void CrystalMapController::mouseReleaseEvent(QMouseEvent *event)
{

    if (m_pOsgRenderer) {
        m_pOsgRenderer->mouseReleaseEvent(event);
    }
}

void CrystalMapController::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (m_pOsgRenderer)
        m_pOsgRenderer->mouseDoubleClickEvent(event);

}

void CrystalMapController::mouseMoveEvent(QMouseEvent *event)
{

    if (m_pOsgRenderer) {
        m_pOsgRenderer->mouseMoveEvent(event);
    }
}

void CrystalMapController::wheelEvent(QWheelEvent *event)
{

    if (m_pOsgRenderer)
        m_pOsgRenderer->wheelEvent(event);
}


void CrystalMapController::createOsgRenderer(int width, int height, QScreen *screen)
{
    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
    ds->setNvOptimusEnablement(1);
    ds->setStereo(false);


    m_pOsgRenderer = new OSGRenderer(this);
    const float pixelRatio = static_cast<float>(screen->devicePixelRatio());
    m_pOsgRenderer->setupOSG(0 , 0, width, height, pixelRatio);

    m_pOsgRenderer->getCamera()->setClearColor(osg::Vec4(0.15f, 0.15f, 0.15f, 1.0f));

}

void CrystalMapController::initializeOsgEarth()
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
