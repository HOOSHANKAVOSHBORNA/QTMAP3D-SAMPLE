
#include <QResizeEvent>
#include <iostream>
#include <QScreen>
#include <osgGA/FirstPersonManipulator>
#include <osgGA/TrackballManipulator>
#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <QThread>
#include <QtOpenGL/QtOpenGL>
#include <iostream>

#include "OsgQuickWindow.h"
#include "CrystalMapController.h"

OsgQuickWindow::OsgQuickWindow(QWindow *parent) :
    QQuickWindow(parent),
    m_pMapController(new CrystalMapController(this))
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
    m_pMapController->deleteLater();
}

CrystalMapController *OsgQuickWindow::mapController() const
{
    return m_pMapController;
}


void OsgQuickWindow::cleanup()
{
    m_pMapController->cleanup();
}

void OsgQuickWindow::frame()
{
    if (m_bResized) {
        resizeGL();
        m_bResized = false;
    }

    paintGL();
}

void OsgQuickWindow::restoreContext()
{
    if (m_pContext && m_pSurface) {
        m_pContext->makeCurrent(m_pSurface);
    }
}


void OsgQuickWindow::initializeGL()
{
    //std::cout << "initializeGL" << std::endl;

    m_pOGLF->initializeOpenGLFunctions();

    m_pContext = QOpenGLContext::currentContext();
    m_pSurface = m_pContext->surface();


    m_pMapController->initializeGL(width(), height(), screen(), renderTargetId());

    restoreContext();
    m_pMapController->initializeOsgEarth();
    restoreContext();
    emit osgInitialized();
    restoreContext();

    resetOpenGLState();

    QObject::connect(this, &OsgQuickWindow::beforeRendering,
                     this, &OsgQuickWindow::frame,
                     Qt::DirectConnection);
}

void OsgQuickWindow::resizeGL()
{
    m_pMapController->resizeGL(m_viewportWidth, m_viewportHeight, screen());
}

void OsgQuickWindow::paintGL()
{
    resetOpenGLState();

    m_pMapController->paintGL();

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


    switch (event->key()) {
    case Qt::Key_Up:
    {
        auto manip = m_pMapController->getEarthManipulator();
        if (manip) {
            manip->pan(0, -0.03);
        }
        event->accept();
    }
    break;
    case Qt::Key_Down:
    {
        auto manip = m_pMapController->getEarthManipulator();
        if (manip) {
            manip->pan(0, 0.03);
        }
        event->accept();
    }
    break;
    case Qt::Key_Left:
    {
        auto manip = m_pMapController->getEarthManipulator();
        if (manip) {
            manip->pan(0.03, 0);
        }
        event->accept();
    }
    break;
    case Qt::Key_Right:
    {
        auto manip = m_pMapController->getEarthManipulator();
        if (manip) {
            manip->pan(-0.03, 0);
        }
        event->accept();
    }
    break;
    }


    if (event->isAccepted())
        return;

    m_pMapController->keyPressEvent(event);


}

void OsgQuickWindow::keyReleaseEvent(QKeyEvent *event)
{
    QQuickWindow::keyReleaseEvent(event);

    if (event->isAccepted())
        return;

    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        event->accept();
        break;
    }

    if (event->isAccepted())
        return;

    m_pMapController->keyReleaseEvent(event);
}

void OsgQuickWindow::mousePressEvent(QMouseEvent *event)
{
    QQuickWindow::mousePressEvent(event);

    if (event->isAccepted())
        return;

    m_pMapController->mousePressEvent(event);


    if (event->button() == Qt::LeftButton) {
        m_lastMousePressTime = QTime::currentTime();
        m_lastPressPoint = event->pos();
    }
}

void OsgQuickWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QQuickWindow::mouseReleaseEvent(event);

    if (event->isAccepted())
        return;

    m_pMapController->mouseReleaseEvent(event);


    if (event->button() == Qt::LeftButton) {
        if (m_lastMousePressTime.msecsTo(QTime::currentTime()) < 400) {
            const QPoint diff = event->pos() - m_lastPressPoint;
            if (std::abs(diff.x()) < 10 && std::abs(diff.y()) < 10) {
                emit clicked();
            }
        }
    }
}

void OsgQuickWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    QQuickWindow::mouseDoubleClickEvent(event);

    if (event->isAccepted())
        return;

    m_pMapController->mouseDoubleClickEvent(event);


}

void OsgQuickWindow::mouseMoveEvent(QMouseEvent *event)
{
    QQuickWindow::mouseMoveEvent(event);

    if (event->isAccepted())
        return;

    m_pMapController->mouseMoveEvent(event);

}

void OsgQuickWindow::wheelEvent(QWheelEvent *event)
{
    QQuickWindow::wheelEvent(event);

    if (event->isAccepted())
        return;


    m_pMapController->wheelEvent(event);

}

