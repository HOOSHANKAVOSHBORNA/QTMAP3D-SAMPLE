
#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarth/ImageLayer>
#include <osgEarthUtil/Sky>

#include "CrystalOsgController.h"


CrystalOsgController::CrystalOsgController(QQuickWindow *window) :
    m_pWindow(window)
{

}

CrystalOsgController::~CrystalOsgController()
{

}

void CrystalOsgController::cleanup()
{
    if (m_pOsgRenderer) {
        m_pOsgRenderer->deleteLater();
        m_pOsgRenderer = nullptr;
    }
}

void CrystalOsgController::initializeGL(int width, int height, QScreen *screen, GLuint renderTargetId)
{

    m_renderTargetId = renderTargetId;

    createOsgRenderer(width, height, screen);

    if(m_pWindow) {
        QObject::connect(m_pOsgRenderer, &OSGRenderer::needsUpdate,
                         m_pWindow, &QQuickWindow::update,
                         Qt::DirectConnection);
    }
}

void CrystalOsgController::resizeGL(int width, int height, QScreen *screen)
{
    if (m_pOsgRenderer) {
        const float pixelRatio = static_cast<float>(screen->devicePixelRatio());
        m_pOsgRenderer->resize(0, 0, width, height, pixelRatio);
    }
}

void CrystalOsgController::paintGL()
{
    if (m_pOsgRenderer) {
        if (m_isFirstFrame) {
            m_isFirstFrame = false;
            m_pOsgRenderer->getCamera()->getGraphicsContext()->setDefaultFboId(m_renderTargetId);
        }

        m_pOsgRenderer->frame();
    }
}

void CrystalOsgController::keyPressEvent(QKeyEvent *event)
{
    if (m_pOsgRenderer)
        m_pOsgRenderer->keyPressEvent(event);
}

void CrystalOsgController::keyReleaseEvent(QKeyEvent *event)
{

    if (m_pOsgRenderer)
        m_pOsgRenderer->keyReleaseEvent(event);
}

void CrystalOsgController::mousePressEvent(QMouseEvent *event)
{
    if (m_pOsgRenderer) {
        m_pOsgRenderer->mousePressEvent(event);
    }

}

void CrystalOsgController::mouseReleaseEvent(QMouseEvent *event)
{

    if (m_pOsgRenderer) {
        m_pOsgRenderer->mouseReleaseEvent(event);
    }
}

void CrystalOsgController::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (m_pOsgRenderer)
        m_pOsgRenderer->mouseDoubleClickEvent(event);

}

void CrystalOsgController::mouseMoveEvent(QMouseEvent *event)
{

    if (m_pOsgRenderer) {
        m_pOsgRenderer->mouseMoveEvent(event);
    }
}

void CrystalOsgController::wheelEvent(QWheelEvent *event)
{

    if (m_pOsgRenderer)
        m_pOsgRenderer->wheelEvent(event);
}


void CrystalOsgController::createOsgRenderer(int width, int height, QScreen *screen)
{
    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
    ds->setNvOptimusEnablement(1);
    ds->setStereo(false);


    m_pOsgRenderer = new OSGRenderer(this);
    const float pixelRatio = static_cast<float>(screen->devicePixelRatio());
    m_pOsgRenderer->setupOSG(0 , 0, width, height, pixelRatio);

    m_pOsgRenderer->getCamera()->setClearColor(osg::Vec4(0.15f, 0.15f, 0.15f, 1.0f));

}

void CrystalOsgController::initializeOsgEarth()
{
    createCameraManipulator();
    m_pOsgRenderer->setCameraManipulator(m_pEarthManipulator);

    installEventHandler();

    mMapRoot = new osg::Group();
    mSkyNode = osgEarth::Util::SkyNode::create(mMapNode);
    createMapNode(true);

    m_pOsgRenderer->setSceneData(mMapRoot);

    osgEarth::Drivers::GDALOptions gdal;
    gdal.url() = "../../world.tif";
    osg::ref_ptr<osgEarth::ImageLayer> imlayer = new osgEarth::ImageLayer("base-world", gdal);
    mMapNode->getMap()->addLayer(imlayer);
}

void CrystalOsgController::createMapNode(bool bGeocentric)
{
    mSkyNode->removeChild(mMapNode);
    mMapRoot->removeChild(mMapNode);
    mMapRoot->removeChild(mSkyNode);

    osgEarth::MapOptions mapOpt;
    if(bGeocentric)
    {
        mapOpt.coordSysType() = osgEarth::MapOptions::CSTYPE_GEOCENTRIC;
        mapOpt.profile() = osgEarth::ProfileOptions("global-mercator");
        mMapNode = new osgEarth::MapNode(new osgEarth::Map(mapOpt));
    }
    else
    {
        mapOpt.coordSysType() = osgEarth::MapOptions::CSTYPE_PROJECTED;
        mapOpt.profile() = osgEarth::ProfileOptions();
        mMapNode = new osgEarth::MapNode(new osgEarth::Map(mapOpt));
    }

    mSkyNode->addChild(mMapNode);
    mMapRoot->addChild(mSkyNode);
    mMapRoot->addChild(mMapNode);
}

void CrystalOsgController::createCameraManipulator()
{
    m_pEarthManipulator = new osgEarth::Util::EarthManipulator;
    auto  settings = m_pEarthManipulator->getSettings();
    settings->setSingleAxisRotation(true);

    settings->setMinMaxDistance(10.0, 1000000000.0);
    settings->setMaxOffset(5000.0, 5000.0);
    settings->setMinMaxPitch(-90, 90);
    settings->setTerrainAvoidanceEnabled(true);
    settings->setThrowingEnabled(false);
}
