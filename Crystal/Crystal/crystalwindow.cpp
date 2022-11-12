
#include "crystalwindow.h"
#include <QResizeEvent>
#include <iostream>
#include <QScreen>
#include <osgGA/FirstPersonManipulator>
#include <osgGA/TrackballManipulator>
#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <QThread>
#include <QtOpenGL/QtOpenGL>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarth/ImageLayer>

CrystalWindow::CrystalWindow(QWindow *parent) :
    QQuickWindow(parent)
{
    m_pOGLF = new QOpenGLFunctions_2_0;

    QObject::connect(this, &CrystalWindow::beforeSynchronizing,
                     this, &CrystalWindow::sync,
                     Qt::DirectConnection);
    QObject::connect(this, &CrystalWindow::sceneGraphInvalidated,
                     this, &CrystalWindow::cleanup,
                     Qt::DirectConnection);

    setClearBeforeRendering(false);
    setColor(Qt::black);

    QObject::connect(this, &CrystalWindow::initialized, [this](){

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

        m_pRenderer->setCameraManipulator(earthManipulator);

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

        m_pRenderer->setSceneData(mMapRoot);

    });

}

CrystalWindow::~CrystalWindow()
{
    cleanup();
}

void CrystalWindow::sync()
{
    if (!m_bSynced) {
        QObject::connect(this, &CrystalWindow::beforeRendering,
                         this, &CrystalWindow::frame,
                         Qt::DirectConnection);
        QObject::connect(this, &CrystalWindow::afterRendering,
                         this, &CrystalWindow::onAfterRendering,
                         Qt::DirectConnection);

        m_bSynced = true;
    }

}

void CrystalWindow::cleanup()
{
    if (m_pRenderer) {
        m_pRenderer->deleteLater();
        m_pRenderer = nullptr;
    }

}

void CrystalWindow::frame()
{
    if (!m_bInitialized) {
        initializeGL();
        m_bInitialized = true;

    }

    if (m_bResized) {
        resizeGL();
        m_bResized = false;
    }

    paintGL();
}

void CrystalWindow::onAfterRendering()
{
    static bool bNotInitialized = true;

    if (bNotInitialized) {

        emit initialized();

        resetOpenGLState();
        bNotInitialized = false;
        update();
    }
}

void CrystalWindow::initializeGL()
{
    m_pOGLF->initializeOpenGLFunctions();
    createOsgRenderer();
}

void CrystalWindow::resizeGL()
{

    const float pixelRatio = static_cast<float>(screen()->devicePixelRatio());
    m_pRenderer->resize(0, 0, width(), height(), pixelRatio);

}

void CrystalWindow::paintGL()
{

    resetOpenGLState();

    if (m_isFirstFrame) {
        m_isFirstFrame = false;
        m_pRenderer->getCamera()->getGraphicsContext()->setDefaultFboId(renderTargetId());
    }

    m_pRenderer->frame();
    m_pOGLF->glClear(GL_DEPTH_BUFFER_BIT);

    resetOpenGLState();
}

void CrystalWindow::resizeEvent(QResizeEvent *ev)
{
    QQuickWindow::resizeEvent(ev);

    const QSize s = ev->size();
    m_bResized       = true;
    m_viewportWidth  = s.width();
    m_viewportHeight = s.height();

}

void CrystalWindow::keyPressEvent(QKeyEvent *event)
{
    QQuickWindow::keyPressEvent(event);

    if (event->isAccepted())
        return;

    if (m_pRenderer)
        m_pRenderer->keyPressEvent(event);
}

void CrystalWindow::keyReleaseEvent(QKeyEvent *event)
{
    QQuickWindow::keyReleaseEvent(event);

    if (event->isAccepted())
        return;

    if (m_pRenderer)
        m_pRenderer->keyReleaseEvent(event);

}

void CrystalWindow::mousePressEvent(QMouseEvent *event)
{
    QQuickWindow::mousePressEvent(event);

    if (event->isAccepted())
        return;

    if (m_pRenderer)
        m_pRenderer->mousePressEvent(event);

}

void CrystalWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QQuickWindow::mouseReleaseEvent(event);

    if (event->isAccepted())
        return;

    if (m_pRenderer)
        m_pRenderer->mouseReleaseEvent(event);


}

void CrystalWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    QQuickWindow::mouseDoubleClickEvent(event);

    if (event->isAccepted())
        return;

    if (m_pRenderer)
        m_pRenderer->mouseDoubleClickEvent(event);


}

void CrystalWindow::mouseMoveEvent(QMouseEvent *event)
{
    QQuickWindow::mouseMoveEvent(event);

    if (event->isAccepted())
        return;

    if (m_pRenderer)
        m_pRenderer->mouseMoveEvent(event);

}

void CrystalWindow::wheelEvent(QWheelEvent *event)
{
    QQuickWindow::wheelEvent(event);

    if (event->isAccepted())
        return;

    if (m_pRenderer)
        m_pRenderer->wheelEvent(event);

}

void CrystalWindow::createOsgRenderer()
{
    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
    ds->setNvOptimusEnablement(1);
    ds->setStereo(false);


    m_pRenderer = new OSGRenderer(this);
    const float pixelRatio = static_cast<float>(screen()->devicePixelRatio());
    m_pRenderer->setupOSG(0 , 0, width(), height(), pixelRatio);

    m_pRenderer->getCamera()->setClearColor(osg::Vec4(0.3f, 0.3f, 0.3f, 1.0f));
}

