#ifndef CRYSTALOSGCONTROLLER_H
#define CRYSTALOSGCONTROLLER_H

#include <QObject>
#include <QQuickWindow>
#include <QObject>
#include <QEvent>
#include <QScreen>
#include <GL/gl.h>
#include <osgEarth/MapNode>
#include <osgEarth/Map>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/Sky>

#include "OsgRenderer.h"

class CrystalOsgController : public QObject
{
    friend class OsgQuickWindow;

    Q_OBJECT

public:

protected:
    explicit CrystalOsgController(QQuickWindow *window);
    virtual ~CrystalOsgController();

    void cleanup();

    void initializeGL(int width, int height, QScreen *screen, GLuint renderTargetId); void resizeGL(int width, int height, QScreen *screen);
    void paintGL();

    virtual void installEventHandler() = 0;

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

    void createOsgRenderer(int width, int height, QScreen *screen);
    void initializeOsgEarth();
    void createMapNode(bool bGeocentric);
    void createCameraManipulator();

protected:
    osg::ref_ptr<osgEarth::MapNode> mMapNode;
    osg::ref_ptr<osgEarth::Util::SkyNode> mSkyNode;
    osg::ref_ptr<osg::Group> mMapRoot;

protected:
    OSGRenderer *m_pOsgRenderer = nullptr;
    bool m_isFirstFrame = true;
    GLuint m_renderTargetId = 0;
    QQuickWindow *m_pWindow = nullptr;

    osgEarth::Util::EarthManipulator *m_pEarthManipulator = nullptr;

    bool m_bGeocentric = true;

};

#endif // CRYSTALOSGCONTROLLER_H
