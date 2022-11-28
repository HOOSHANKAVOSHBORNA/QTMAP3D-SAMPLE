
#include <iostream>
#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarth/ImageLayer>
#include <osgEarthUtil/Sky>
#include <osgEarth/Registry>
#include <QMessageBox>
#include <QTimer>

#include "mapcontroller.h"

class MainEventHandler : public osgGA::GUIEventHandler
{
public:
    MainEventHandler(MapController *pMapController);
    virtual ~MainEventHandler() override { }

protected:
    bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa) override;

private:
    void mouseEvent(osgViewer::View *view, const osgGA::GUIEventAdapter &ea, QEvent::Type qEventType);

private:
    MapController *mpMapController = nullptr;
};

MapController::MapController(QQuickWindow *window) :
    OsgController(window)
{
//        QTimer::singleShot(10000, [this](){this->setGeocentric(false);});
}

MapController::~MapController()
{

}

void MapController::installEventHandler()
{
    getViewer()->addEventHandler(new MainEventHandler(this));
}

osgViewer::Viewer *MapController::getViewer()
{
    return dynamic_cast<osgViewer::Viewer*>(mpOsgRenderer);
}

osgEarth::Util::EarthManipulator *MapController::getEarthManipulator()
{
    return mpEarthManipulator;
}

osgEarth::Viewpoint MapController::getViewpoint() const
{
    if (mpEarthManipulator)
        return mpEarthManipulator->getViewpoint();
    return osgEarth::Viewpoint();
}

osgEarth::MapNode *MapController::getMapNode()
{
    return mMapNode;
}

const osgEarth::SpatialReference *MapController::getMapSRS() const
{
    return mMapNode->getMapSRS();
}

void MapController::setMap(osgEarth::Map *map)
{
    setGeocentric(map->isGeocentric());

    mMapNode->getMap()->clear();
    mMapNode->getMap()->setLayersFromMap(map);

    goToHome();
}

void MapController::setTrackNode(osg::Node *node)
{
    auto vp = getEarthManipulator()->getViewpoint();
    if(vp.getNode() == node)
        return;

    vp.setNode(node);
    getEarthManipulator()->setViewpoint(vp);
    auto camSet = getEarthManipulator()->getSettings();
    camSet->setTetherMode(osgEarth::Util::EarthManipulator::TetherMode::TETHER_CENTER);
    getEarthManipulator()->applySettings(camSet);
}

void MapController::untrackNode()
{
    auto vp = getEarthManipulator()->getViewpoint();
    if(vp.getNode() == nullptr)
        return;
    vp.setNode(nullptr);
    getEarthManipulator()->setViewpoint(vp);
}

bool MapController::addNode(osg::Node *node)
{
    osgEarth::Registry::shaderGenerator().run(node);// for textures or lighting
    return mMapNode->addChild(node);
}

bool MapController::removeNode(osg::Node *node)
{
    return mMapNode->removeChild(node);
}

void MapController::setViewpoint(const osgEarth::Viewpoint &vp, double duration_s)
{
    getEarthManipulator()->setViewpoint(vp,duration_s);
}

void MapController::addLayer(osgEarth::Layer *layer)
{

    mMapNode->getMap()->addLayer(layer);
    // Check if the layer is added successfully
    auto added = mMapNode->getMap()->getLayerByName(layer->getName());
    if (added && added->getEnabled())
    {

    }
    else
    {
        QMessageBox::warning(nullptr, tr("Error"), tr("Data loading failed!"));
    }
}

void MapController::setZoom(double val)
{
    getEarthManipulator()->zoom(0, -val, getViewer());
}

void MapController::goToHome()
{
    getEarthManipulator()->home(0);
}

void MapController::goToPosition(double latitude, double longitude, double range)
{
    osgEarth::GeoPoint  pointLatLong(osgEarth::SpatialReference::get("wgs84"), latitude, longitude, 0);
    osgEarth::GeoPoint  mapPoint;
    pointLatLong.transform(getMapSRS(), mapPoint);

    osgEarth::Viewpoint vp;
    vp.focalPoint() = mapPoint;
    vp.range()= range;
    setViewpoint(vp, 3.0);
}

void MapController::setGeocentric(bool bGeocentric)
{
    if (mbGeocentric == bGeocentric)
        return;

    mbGeocentric = bGeocentric;

    osgEarth::LayerVector layers;
    mMapNode->getMap()->getLayers(layers);

    createMapNode(bGeocentric);
    for(auto layer: layers)
       addLayer(layer);

    osgEarth::Viewpoint vp = getEarthManipulator()->getViewpoint();

    createCameraManipulator();
    getViewer()->setCameraManipulator(getEarthManipulator());
    getEarthManipulator()->setViewpoint(vp);
}

void MapController::toggleProjection()
{
    setGeocentric(!mbGeocentric);
}

void MapController::frame()
{
    emit headingAngleChanged(-getViewpoint().getHeading());
}

void MapController::panUp()
{
    getEarthManipulator()->pan(0.0, -0.1);
}

void MapController::panDown()
{
    getEarthManipulator()->pan(0.0, 0.1);
}

void MapController::panLeft()
{
    getEarthManipulator()->pan(0.1, 0.0);
}

void MapController::panRight()
{
    getEarthManipulator()->pan(-0.1, 0.0);
}

void MapController::rotateUp()
{
    getEarthManipulator()->rotate(0.0, -0.1);
}

void MapController::rotateDown()
{
    getEarthManipulator()->rotate(0.0, 0.1);
}

void MapController::rotateLeft()
{
    getEarthManipulator()->rotate(-0.1, 0.0);
}

void MapController::rotateRight()
{
    getEarthManipulator()->rotate(0.1, 0.0);
}

void MapController::zoomIn()
{
    getEarthManipulator()->zoom(0.0, -0.4, getViewer());
}

void MapController::zoomOut()
{
    getEarthManipulator()->zoom(0.0, 0.4, getViewer());
}

bool MainEventHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{

    osgViewer::View *view = dynamic_cast<osgViewer::View *>(&aa);

    QEvent::Type qEventType;
    switch (ea.getEventType())
    {
    case osgGA::GUIEventAdapter::FRAME:
        mpMapController->frame();
        break;
    case (osgGA::GUIEventAdapter::PUSH):
        qEventType = QEvent::Type::MouseButtonPress;
        if (view) { mouseEvent(view, ea, qEventType); }
        break;
    case (osgGA::GUIEventAdapter::RELEASE):
        qEventType = QEvent::Type::MouseButtonRelease;
        if (view) { mouseEvent(view, ea, qEventType); }
        break;
    case (osgGA::GUIEventAdapter::MOVE):
        qEventType = QEvent::Type::MouseMove;
        if (view) { mouseEvent(view, ea, qEventType); }
        break;
    case (osgGA::GUIEventAdapter::SCROLL):
        qEventType = QEvent::Type::Wheel;
        if (view) { mouseEvent(view, ea, qEventType); }
        break;
    case (osgGA::GUIEventAdapter::DOUBLECLICK):
        qEventType = QEvent::Type::MouseButtonDblClick;
        if (view) { mouseEvent(view, ea, qEventType); }
        break;
    default:
        break;
    }
    return false;

}

void MainEventHandler::mouseEvent(osgViewer::View *view, const osgGA::GUIEventAdapter &ea, QEvent::Type qEventType)
{

    QMouseEvent* event;
    Qt::MouseButton mb;
    switch (ea.getButtonMask())
    {
    case osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON:
        mb = Qt::MouseButton::LeftButton;
        break;
    case osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON:
        mb = Qt::MouseButton::RightButton;
        break;
    case osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON:
        mb = Qt::MouseButton::MiddleButton;
        break;
    default:
        mb = Qt::MouseButton::NoButton;
    }

    event = new QMouseEvent(qEventType,
                            QPointF(static_cast<qreal>(ea.getX()),static_cast<qreal>(ea.getY())),
                            mb, mb, Qt::KeyboardModifier::NoModifier);

    osgUtil::LineSegmentIntersector::Intersections intersections;
    if (view->computeIntersections(ea, intersections))
    {
        for (const auto &intersection : intersections)
        {
            //            mCurrentLocalPos    = intersection.getLocalIntersectPoint();
            osg::Vec3d currentWorldPos = intersection.getWorldIntersectPoint();
            //mpMapController->mapMouseEvent(event,currentWorldPos);
            return;
        }
    }
}

MainEventHandler::MainEventHandler(MapController *pMapController) :
    mpMapController(pMapController)
{

}
