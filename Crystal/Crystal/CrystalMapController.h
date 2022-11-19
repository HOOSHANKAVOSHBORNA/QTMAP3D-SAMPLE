#ifndef CrystalMapController_H
#define CrystalMapController_H

#include <QQuickWindow>
#include <QObject>
#include <QEvent>
#include <QScreen>
#include <GL/gl.h>
#include <osgEarth/MapNode>
#include <osgEarth/Map>

#include "OsgRenderer.h"

class CrystalMapController : public QObject
{
    friend class OsgQuickWindow;

    Q_OBJECT

public:
    osgViewer::Viewer *getViewer();


private:
    explicit CrystalMapController(QQuickWindow *window);
    ~CrystalMapController();

    void cleanup();

    void initializeGL(int width, int height, QScreen *screen, GLuint renderTargetId); void resizeGL(int width, int height, QScreen *screen);
    void paintGL();

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

    void createOsgRenderer(int width, int height, QScreen *screen);
    void initializeOsgEarth();

private:
    osg::ref_ptr<osgEarth::MapNode> mMapNodeGeo;
    osg::ref_ptr<osg::Group> mMapRoot;

private:
    OSGRenderer *m_pOsgRenderer = nullptr;
    bool m_isFirstFrame = true;
    GLuint m_renderTargetId = 0;
    QQuickWindow *m_pWindow = nullptr;

};

#endif // CrystalMapController_H
