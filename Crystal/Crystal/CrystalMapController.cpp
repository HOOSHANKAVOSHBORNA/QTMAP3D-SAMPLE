
#include <iostream>
#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarth/ImageLayer>
#include <osgEarthUtil/Sky>
#include <osgEarth/Registry>
#include <QMessageBox>
#include <QTimer>

#include "CrystalMapController.h"

class CrystalEventHandler : public osgGA::GUIEventHandler
{
public:
    CrystalEventHandler(CrystalMapController *pMapController);
    virtual ~CrystalEventHandler() override { }

protected:
    bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa) override;

private:
    void mouseEvent(osgViewer::View *view, const osgGA::GUIEventAdapter &ea, QEvent::Type qEventType);

private:
    CrystalMapController *m_pMapController = nullptr;
};

CrystalMapController::CrystalMapController(QQuickWindow *window) :
    CrystalOsgController(window)
{
//        QTimer::singleShot(10000, [this](){this->setGeocentric(false);});
}

CrystalMapController::~CrystalMapController()
{

}

void CrystalMapController::installEventHandler()
{
    getViewer()->addEventHandler(new CrystalEventHandler(this));
}

osgViewer::Viewer *CrystalMapController::getViewer()
{
    return dynamic_cast<osgViewer::Viewer*>(m_pOsgRenderer);
}

osgEarth::Util::EarthManipulator *CrystalMapController::getEarthManipulator()
{
    return m_pEarthManipulator;
}

osgEarth::Viewpoint CrystalMapController::getViewpoint() const
{
    if (m_pEarthManipulator)
        return m_pEarthManipulator->getViewpoint();
    return osgEarth::Viewpoint();
}

osgEarth::MapNode *CrystalMapController::getMapNode()
{
    return mMapNode;
}

const osgEarth::SpatialReference *CrystalMapController::getMapSRS() const
{
    return mMapNode->getMapSRS();
}

void CrystalMapController::setMap(osgEarth::Map *map)
{
    setGeocentric(map->isGeocentric());

    mMapNode->getMap()->clear();
    mMapNode->getMap()->setLayersFromMap(map);

    goToHome();
}

void CrystalMapController::setTrackNode(osg::Node *node)
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

void CrystalMapController::untrackNode()
{
    auto vp = getEarthManipulator()->getViewpoint();
    if(vp.getNode() == nullptr)
        return;
    vp.setNode(nullptr);
    getEarthManipulator()->setViewpoint(vp);
}

bool CrystalMapController::addNode(osg::Node *node)
{
    osgEarth::Registry::shaderGenerator().run(node);// for textures or lighting
    return mMapNode->addChild(node);
}

bool CrystalMapController::removeNode(osg::Node *node)
{
    return mMapNode->removeChild(node);
}

void CrystalMapController::setViewpoint(const osgEarth::Viewpoint &vp, double duration_s)
{
    getEarthManipulator()->setViewpoint(vp,duration_s);
}

void CrystalMapController::addLayer(osgEarth::Layer *layer)
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

void CrystalMapController::setZoom(double val)
{
    getEarthManipulator()->zoom(0, -val, getViewer());
}

void CrystalMapController::goToHome()
{
    getEarthManipulator()->home(0);
}

void CrystalMapController::goToPosition(double latitude, double longitude, double range)
{
    osgEarth::GeoPoint  pointLatLong(osgEarth::SpatialReference::get("wgs84"), latitude, longitude, 0);
    osgEarth::GeoPoint  mapPoint;
    pointLatLong.transform(getMapSRS(), mapPoint);

    osgEarth::Viewpoint vp;
    vp.focalPoint() = mapPoint;
    vp.range()= range;
    setViewpoint(vp, 3.0);
}

void CrystalMapController::setGeocentric(bool bGeocentric)
{
    if (m_bGeocentric == bGeocentric)
        return;

    m_bGeocentric = bGeocentric;

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

void CrystalMapController::toggleProjection()
{
    setGeocentric(!m_bGeocentric);
}

void CrystalMapController::frame()
{
    emit headingAngleChanged(-getViewpoint().getHeading());
}

void CrystalMapController::panUp()
{
    getEarthManipulator()->pan(0.0, -0.1);
}

void CrystalMapController::panDown()
{
    getEarthManipulator()->pan(0.0, 0.1);
}

void CrystalMapController::panLeft()
{
    getEarthManipulator()->pan(0.1, 0.0);
}

void CrystalMapController::panRight()
{
    getEarthManipulator()->pan(-0.1, 0.0);
}

void CrystalMapController::rotateUp()
{
    getEarthManipulator()->rotate(0.0, 0.1);
}

void CrystalMapController::rotateDown()
{
    getEarthManipulator()->rotate(0.0, -0.1);
}

void CrystalMapController::rotateLeft()
{
    getEarthManipulator()->rotate(-0.1, 0.0);
}

void CrystalMapController::rotateRight()
{
    getEarthManipulator()->rotate(0.1, 0.0);
}

void CrystalMapController::zoomIn()
{
    getEarthManipulator()->zoom(0.0, -0.4, getViewer());
}

void CrystalMapController::zoomOut()
{
    getEarthManipulator()->zoom(0.0, 0.4, getViewer());
}

bool CrystalEventHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{

    osgViewer::View *view = dynamic_cast<osgViewer::View *>(&aa);

    QEvent::Type qEventType;
    switch (ea.getEventType())
    {
    case osgGA::GUIEventAdapter::FRAME:
        m_pMapController->frame();
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

void CrystalEventHandler::mouseEvent(osgViewer::View *view, const osgGA::GUIEventAdapter &ea, QEvent::Type qEventType)
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
            //m_pMapController->mapMouseEvent(event,currentWorldPos);
            return;
        }
    }
}

CrystalEventHandler::CrystalEventHandler(CrystalMapController *pMapController) :
    m_pMapController(pMapController)
{

}
