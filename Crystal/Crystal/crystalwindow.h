#ifndef CRYSTALWINDOW_H
#define CRYSTALWINDOW_H

#include <QQuickWindow>
#include <QOpenGLFunctions_2_0>
#include <OpenThreads/ReadWriteMutex>
#include <osgEarthUtil/Sky>
#include <osgEarth/ImageLayer>
#include <osgEarth/MapOptions>
#include <osgEarth/Profile>
#include <osgEarth/Map>
#include <osgEarth/MapNode>
#include <osgEarthDrivers/gdal/GDALOptions>

#include "osgrenderer.h"

class CrystalWindow : public QQuickWindow
{
    Q_OBJECT

public:
    CrystalWindow(QWindow *parent = nullptr);
    ~CrystalWindow();

public slots:
    void sync();
    void cleanup();
    void frame();
    void onAfterRendering();

private:
    void initializeGL();
    void resizeGL();
    void paintGL();

protected:
    void resizeEvent(QResizeEvent *) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;


    void createOsgRenderer();


signals:
    void initialized();

private:
    QOpenGLFunctions_2_0 *m_pOGLF = nullptr;
    OSGRenderer *m_pRenderer = nullptr;

    bool m_bSynced      = false;
    bool m_bInitialized = false;
    bool m_bResized     = false;

    int m_viewportWidth = 0;
    int m_viewportHeight = 0;

    OpenThreads::ReadWriteMutex m_osgMutex;

    bool m_isFirstFrame = true;

    osg::ref_ptr<osgEarth::MapNode> mMapNodeGeo;
    osg::ref_ptr<osg::Group> mMapRoot;
};

#endif // CRYSTALWINDOW_H
