
#include "OsgQuickWindow.h"
#include <QResizeEvent>
#include <iostream>
#include <QScreen>
#include <osgGA/FirstPersonManipulator>
#include <osgGA/TrackballManipulator>
#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <QThread>
#include <QtOpenGL/QtOpenGL>

OsgQuickWindow::OsgQuickWindow(QWindow *parent) :
    QQuickWindow(parent)
{
    m_pOGLF = new QOpenGLFunctions_2_0;


    QObject::connect(this, &OsgQuickWindow::sceneGraphInitialized,
                     this, &OsgQuickWindow::initializeGL,
                     Qt::DirectConnection);
    QObject::connect(this, &OsgQuickWindow::sceneGraphInvalidated,
                     this, &OsgQuickWindow::cleanup,
                     Qt::DirectConnection);

    setClearBeforeRendering(false);
    setColor(Qt::black);

}

OsgQuickWindow::~OsgQuickWindow()
{
    cleanup();
}

osgViewer::Viewer *OsgQuickWindow::getViewer() const
{
    return static_cast<osgViewer::Viewer*>(m_pRenderer);
}

void OsgQuickWindow::cleanup()
{
    if (m_pRenderer) {
        m_pRenderer->deleteLater();
        m_pRenderer = nullptr;
    }

}

void OsgQuickWindow::frame()
{
    if (m_bResized) {
        resizeGL();
        m_bResized = false;
    }

    paintGL();
}


void OsgQuickWindow::initializeGL()
{
    m_pOGLF->initializeOpenGLFunctions();

    QOpenGLContext * const ctx = QOpenGLContext::currentContext();
    QSurface * const surface = ctx->surface();


    createOsgRenderer();
    ctx->makeCurrent(surface);

    emit initialized();

    ctx->makeCurrent(surface);
    resetOpenGLState();

    QObject::connect(this, &OsgQuickWindow::beforeRendering,
                     this, &OsgQuickWindow::frame,
                     Qt::DirectConnection);
}

void OsgQuickWindow::resizeGL()
{

    const float pixelRatio = static_cast<float>(screen()->devicePixelRatio());
    m_pRenderer->resize(0, 0, width(), height(), pixelRatio);

}

void OsgQuickWindow::paintGL()
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

void OsgQuickWindow::resizeEvent(QResizeEvent *ev)
{
    QQuickWindow::resizeEvent(ev);

    const QSize s = ev->size();
    m_bResized       = true;
    m_viewportWidth  = s.width();
    m_viewportHeight = s.height();

}

void OsgQuickWindow::keyPressEvent(QKeyEvent *event)
{
    QQuickWindow::keyPressEvent(event);

    if (event->isAccepted())
        return;

    if (m_pRenderer)
        m_pRenderer->keyPressEvent(event);
}

void OsgQuickWindow::keyReleaseEvent(QKeyEvent *event)
{
    QQuickWindow::keyReleaseEvent(event);

    if (event->isAccepted())
        return;

    if (m_pRenderer)
        m_pRenderer->keyReleaseEvent(event);

}

void OsgQuickWindow::mousePressEvent(QMouseEvent *event)
{
    QQuickWindow::mousePressEvent(event);

    if (event->isAccepted())
        return;

    if (m_pRenderer)
        m_pRenderer->mousePressEvent(event);


    m_lastMousePressTime = QTime::currentTime();
    m_lastPressPoint = event->pos();
}

void OsgQuickWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QQuickWindow::mouseReleaseEvent(event);

    if (event->isAccepted())
        return;

    if (m_pRenderer)
        m_pRenderer->mouseReleaseEvent(event);


    if (m_lastMousePressTime.msecsTo(QTime::currentTime()) < 400) {
        const QPoint diff = event->pos() - m_lastPressPoint;
        if (std::abs(diff.x()) < 10 && std::abs(diff.y()) < 10) {
            emit clicked();
        }
    }
}

void OsgQuickWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    QQuickWindow::mouseDoubleClickEvent(event);

    if (event->isAccepted())
        return;

    if (m_pRenderer)
        m_pRenderer->mouseDoubleClickEvent(event);


}

void OsgQuickWindow::mouseMoveEvent(QMouseEvent *event)
{
    QQuickWindow::mouseMoveEvent(event);

    if (event->isAccepted())
        return;

    if (m_pRenderer)
        m_pRenderer->mouseMoveEvent(event);

}

void OsgQuickWindow::wheelEvent(QWheelEvent *event)
{
    QQuickWindow::wheelEvent(event);

    if (event->isAccepted())
        return;

    if (m_pRenderer)
        m_pRenderer->wheelEvent(event);

}

void OsgQuickWindow::createOsgRenderer()
{
    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
    ds->setNvOptimusEnablement(1);
    ds->setStereo(false);


    m_pRenderer = new OSGRenderer(this);
    const float pixelRatio = static_cast<float>(screen()->devicePixelRatio());
    m_pRenderer->setupOSG(0 , 0, width(), height(), pixelRatio);

    m_pRenderer->getCamera()->setClearColor(osg::Vec4(0.15f, 0.15f, 0.15f, 1.0f));
}

