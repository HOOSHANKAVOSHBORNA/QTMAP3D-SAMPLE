#ifndef OSGQUICKWINDOW_H
#define OSGQUICKWINDOW_H

#include <QWindow>
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

#include "OsgRenderer.h"

class OsgQuickWindow : public QQuickWindow
{
    Q_OBJECT

public:
    OsgQuickWindow(QWindow *parent = nullptr);
    ~OsgQuickWindow();


    osgViewer::Viewer *getViewer() const;

public slots:
    void cleanup();
    void frame();

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

    bool m_bResized     = false;

    int m_viewportWidth = 0;
    int m_viewportHeight = 0;

    bool m_isFirstFrame = true;

};

#endif // OSGQUICKWINDOW_H
