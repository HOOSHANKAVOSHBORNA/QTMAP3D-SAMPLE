#ifndef CrystalMapController_H
#define CrystalMapController_H

#include <QQuickWindow>
#include <QObject>
#include <QEvent>
#include <QScreen>
#include <GL/gl.h>
#include <osgEarth/MapNode>
#include <osgEarth/Map>
#include <osgEarthUtil/EarthManipulator>

#include "OsgRenderer.h"
#include "CrystalOsgController.h"


class CrystalEventHandler;


class CrystalMapController : private CrystalOsgController
{
    friend class OsgQuickWindow;
    Q_OBJECT

public:
    osgViewer::Viewer *getViewer();
    osgEarth::Util::EarthManipulator *getEarthManipulator();
    osgEarth::Viewpoint getViewpoint() const;
    osgEarth::MapNode *getMapNode();
    const osgEarth::SpatialReference* getMapSRS() const;

public:
    void setMap(osgEarth::Map *map);
    void setTrackNode(osg::Node *node);
    void untrackNode();
    bool addNode(osg::Node *node);
    bool removeNode(osg::Node *node);
    void setViewpoint(const osgEarth::Viewpoint& vp, double duration_s = 0.0);
    void addLayer(osgEarth::Layer* layer);

public slots:
    void setZoom(double);
    void goToHome();
    void goToPosition(double latitude, double longitude, double range);
    void setGeocentric(bool bGeocentric);

private:
    explicit CrystalMapController(QQuickWindow *window);
    ~CrystalMapController();
};

#endif // CrystalMapController_H
