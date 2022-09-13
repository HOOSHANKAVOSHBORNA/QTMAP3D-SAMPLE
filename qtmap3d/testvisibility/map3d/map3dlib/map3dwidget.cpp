#include "map3dwidget.h"

#include <osgQOpenGL/osgQOpenGLWidget>
#include <osgDB/FileUtils>
#include <osgViewer/Viewer>
//#include <osgEarth/Map>
//#include <osgEarth/MapNode>
#include <osgEarth/Registry>
//#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/AutoClipPlaneHandler>
#include <osgEarthUtil/LogarithmicDepthBuffer>
#include <osgEarthUtil/ExampleResources>
#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarth/ImageLayer>
#include <osg/Camera>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/ShapeDrawable>
#include <osgEarthSymbology/AltitudeSymbol>
#include <osgEarthSymbology/LineSymbol>
#include <osgEarthSymbology/RenderSymbol>
#include <osgEarthSymbology/Style>
#include <osgEarthAnnotation/ModelNode>
#include <osgUtil/Tessellator>
#include <QDirIterator>
#include<QDebug>
#include <QDockWidget>
#include <QSlider>
#include <QHBoxLayout>
#include <exception>
#include <osgEarth/Map>
#include <osgEarth/MapNode>
#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarthSymbology/Geometry>
#include <osgEarthFeatures/Feature>
#include <osgEarthAnnotation/FeatureNode>



using namespace osgEarth;
using namespace osgEarth::Drivers;
const double ZOOM_STEP{0.2};
const double UP_DOWN_STEP{0.1};
const double LEFT_RIGHT_STEP{0.1};
const double HEAD_STEP{osg::DegreesToRadians(5.0)};
const double PITCH_STEP{osg::DegreesToRadians(2.0)};

const double MIN_DISTANCE{10.0};
const double MAX_DISTANCE{1000000000.0};
const double MAX_OFSET{5000.0};

osgEarth::Annotation::FeatureNode* makepolygan(QVector<osg::Vec3d> vertices){
     //osg::ref_ptr<osg::Vec3dArray> vertices = new osg::Vec3dArray(4);

    osgEarth::Symbology::Geometry* geom =new osgEarth::Symbology::Polygon();
    for (int i=0; i<vertices.length();i++){
        geom->push_back(vertices[i]);
    }
//    geom->push_back( osg::Vec3d(52.859,   35.800, 0) );
//    geom->push_back( osg::Vec3d(52.900, 35.800, 0) );
//    geom->push_back( osg::Vec3d(52.800, 35.600, 0) );
//    geom->push_back( osg::Vec3d(52.759,   35.500, 0) );
    osgEarth::Features::Feature* feature = new osgEarth::Features::Feature(geom, osgEarth::SpatialReference::get("wgs84"));
    feature->geoInterp() = GEOINTERP_RHUMB_LINE;
    osgEarth::Symbology::Style geomStyle;
    geomStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()->stroke()->color() = Color::Green;
    geomStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()->stroke()->width() = 5.0f;
    geomStyle.getOrCreate<osgEarth::Symbology::PolygonSymbol>()->fill()->color() =Color(osg::Vec4(0.0f,1.0f,0.0f,0.5f));
    //geomStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()->tessellationSize()->set(75000, Units::METERS);
    geomStyle.getOrCreate<osgEarth::Symbology::RenderSymbol>()->depthOffset()->enabled() = true;
    geomStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_RELATIVE_TO_TERRAIN;
    geomStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_DRAPE;
    osgEarth::Annotation::FeatureNode* gnode = new osgEarth::Annotation::FeatureNode(feature, geomStyle);
    return  gnode;

}

osg::Geode* makeSape(osg::Vec3 eye,float radius)
{
    osg::ref_ptr<osg::Sphere>         pSphereShape   = new osg::Sphere(eye, radius);
    osg::ref_ptr<osg::ShapeDrawable>  pShapeDrawable = new osg::ShapeDrawable(pSphereShape.get());

    pShapeDrawable->setColor(osg::Vec4(1.0, 0.0, 0.0, 0.3f));

    osg::ref_ptr<osg::Geode>  geode = new osg::Geode();
    geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(1.0), osg::StateAttribute::ON);

    geode->addDrawable(pShapeDrawable.get());

    return geode.release();
}
Map3dWidget::Map3dWidget(bool isGeocentric, QWidget *parent)
    : QWidget(parent)
{
    mIsGeocentric = isGeocentric;
    mLayout = new QHBoxLayout(this);
    mLayout->setMargin(0);
    mMapOpenGLWidget = new osgQOpenGLWidget(this);

    mLayout->addWidget(mMapOpenGLWidget);
    createWidgets();
    // init signal handle-------------------------------------------------------
    QObject::connect(mMapOpenGLWidget, &osgQOpenGLWidget::initialized, [=]{
        //create camera ----------------------------------------------
        createManipulator();
        mMapOpenGLWidget->getOsgViewer()->setCameraManipulator(mEarthManipulator);
        //create map node---------------------------------------------
        GDALOptions gdal;
        gdal.url() = "../map3dlib/data/earth_files/world.tif";
        osg::ref_ptr<ImageLayer> imlayer = new ImageLayer("base-world", gdal);
        //        GDALOptions ggdal;
        //        ggdal.url() = "/home/client112/Documents/mbr/QTMAP3D-DATA/dataosgearth/Tehranelevation/tehran1.tif";
        //        osg::ref_ptr<ElevationLayer> elv = new ElevationLayer( "SRTM", ggdal );

        MapOptions mapOptGeo;
        mapOptGeo.coordSysType() = MapOptions::CSTYPE_GEOCENTRIC;
        mapOptGeo.profile() = ProfileOptions("global-mercator");

        mMapNodeGeo = new MapNode(new Map(mapOptGeo));
        mMapNodeGeo->getMap()->addLayer(imlayer);
        //mMapNodeGeo->getMap()->addLayer(elv);

        MapOptions mapOptProj;
        mapOptProj.coordSysType() = MapOptions::CSTYPE_PROJECTED;
        mapOptProj.profile() = ProfileOptions("plate-carre");
        mMapNodeProj = new MapNode(new Map(mapOptProj));
        mMapNodeProj->getMap()->addLayer(imlayer);

        mMapRoot = new osg::Group();

        mMapRoot->addChild(mMapNodeGeo);
        mMapRoot->addChild(mMapNodeProj);





        //////////////////////////////////////////////////////////
        mMapNodeGeo->setNodeMask(isGeocentric);
        mMapNodeProj->setNodeMask(!isGeocentric);

        mMapOpenGLWidget->getOsgViewer()->setSceneData(mMapRoot);
        mHomeViewpoint = mEarthManipulator->getViewpoint();

        mCmWidget->setStateMap(isGeocentric);



        osg::Vec3 position(0.3f,0.2f,1.0f);
        mDrownode =makeSape(osg::Vec3(position.x(),position.y(),position.z()),20000.0f);
        osgEarth::Symbology::Style  style;

        style.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_RELATIVE_TO_TERRAIN;
        style.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_DRAPE;
        style.getOrCreate<osgEarth::Symbology::ModelSymbol>()->setModel(mDrownode);

        osg::ref_ptr<osgEarth::Annotation::ModelNode>  model;
        model = new osgEarth::Annotation::ModelNode(mMapNodeGeo, style);
        osgEarth::GeoPoint  point(osgEarth::SpatialReference::get("wgs84"), 52.859, 35.461);
        model->setPosition(point);
        mMapNodeGeo->addChild(model);
        ///////////
        QVector<osg::Vec3d> vertices;
        vertices.push_back( osg::Vec3d(52.859,35.550, 0) );
        vertices.push_back( osg::Vec3d(52.859,35.540, 0) );
        vertices.push_back( osg::Vec3d(52.865,35.540, 0) );
        vertices.push_back( osg::Vec3d(52.865,35.550, 0) );
        QVector<osg::Vec3d> vertices1;
        vertices1.push_back( osg::Vec3d(52.900,35.500, 0) );
        vertices1.push_back( osg::Vec3d(52.850,35.450, 0) );
        vertices1.push_back( osg::Vec3d(52.900,35.400, 0) );
        vertices1.push_back( osg::Vec3d(52.950,35.400, 0) );
        vertices1.push_back( osg::Vec3d(53.000,35.450, 0) );
        vertices1.push_back( osg::Vec3d(53.050,35.500, 0) );

        QVector<osg::Vec3d> vertices2;
        vertices2.push_back( osg::Vec3d(52.800,35.500, 0) );
        vertices2.push_back( osg::Vec3d(52.770,35.470, 0) );
        vertices2.push_back( osg::Vec3d(52.830,35.440, 0) );
        vertices2.push_back( osg::Vec3d(52.860,35.470, 0) );
        vertices2.push_back( osg::Vec3d(52.860,35.500, 0) );

        QVector<osg::Vec3d> vertices3;
        vertices3.push_back( osg::Vec3d(52.800,35.430, 0) );
        vertices3.push_back( osg::Vec3d(52.760,35.390, 0) );
        vertices3.push_back( osg::Vec3d(52.760,35.350, 0) );
        vertices3.push_back( osg::Vec3d(52.800,35.310, 0) );
        vertices3.push_back( osg::Vec3d(52.840,35.310, 0) );
        vertices3.push_back( osg::Vec3d(52.880,35.350, 0) );
        vertices3.push_back( osg::Vec3d(52.880,35.390, 0) );
        vertices3.push_back( osg::Vec3d(52.840,35.430, 0) );


        osgEarth::Annotation::FeatureNode* fNode =makepolygan(vertices);
        mMapNodeGeo->addChild(fNode);
        osgEarth::Annotation::FeatureNode* fNode1 =makepolygan(vertices1);
        mMapNodeGeo->addChild(fNode1);
        osgEarth::Annotation::FeatureNode* fNode2 =makepolygan(vertices2);
        mMapNodeGeo->addChild(fNode2);
        osgEarth::Annotation::FeatureNode* fNode3 =makepolygan(vertices3);
        mMapNodeGeo->addChild(fNode3);

        ///
    });
}

void Map3dWidget::setMap(Map *map)
{
    mMapNodeGeo->getMap()->clear();
    mMapNodeProj->getMap()->clear();

    //    LayerVector layers;
    //    map->getLayers(layers);
    //    foreach (auto layer, layers) {
    //        qDebug()<<layer->getName().c_str();
    //        qDebug()<<layer->getTypeName();
    //        ImageLayer* imLayere = static_cast<ImageLayer*>(layer.get());
    //        auto lay2 = static_cast<ImageLayer*>(imLayere->clone(osg::CopyOp::SHALLOW_COPY));
    //        mMapNodeGeo->getMap()->addLayer(imLayere);
    //        mMapNodeProj->getMap()->addLayer(lay2);
    //    }

    mMapNodeGeo->getMap()->setLayersFromMap(map);
    mMapNodeProj->getMap()->setLayersFromMap(map);

    //    LayerVector layers1;
    //    mMapNodeGeo->getMap()->getLayers(layers1);
    //    foreach (auto layer, layers1) {
    //        qDebug()<<layer->getName().c_str();
    //        qDebug()<<layer->getTypeName();
    //        //mMapNodeGeo->getMap()->addLayer(layer.get());
    //        //mMapNodeProj->getMap()->addLayer(layer.get());
    //    }

    mCmWidget->setStateMap(map->isGeocentric());
    typeChanged(map->isGeocentric());
    home();
}

void Map3dWidget::setViewpoint(const Viewpoint &vp, double duration_s)
{
    mEarthManipulator->setViewpoint(vp,duration_s);
}

MapNode *Map3dWidget::getMapNode()
{
    if(mIsGeocentric)
        return mMapNodeGeo;
    else
        return mMapNodeProj;
}

void Map3dWidget::createManipulator()
{
    mEarthManipulator = new osgEarth::Util::EarthManipulator;
    auto  settings = mEarthManipulator->getSettings();
    settings->setSingleAxisRotation(true);
    //qDebug()<<settings->getMaxDistance();
    settings->setMinMaxDistance(MIN_DISTANCE, MAX_DISTANCE);
    settings->setMaxOffset(MAX_OFSET, MAX_OFSET);
    //settings->setMinMaxPitch(-90, 90);
    settings->setTerrainAvoidanceEnabled(true);
    settings->setThrowingEnabled(false);

}

void Map3dWidget::createWidgets()
{
    mCmWidget = new CameraManipulatorWidget(this);
    // setting CameraManipulatorWidget
    mCmWidget->setZoomStep(ZOOM_STEP);
    mCmWidget->setUpDownStep(UP_DOWN_STEP);
    mCmWidget->setLeftRightStep(LEFT_RIGHT_STEP);
    mCmWidget->setHeadStep(HEAD_STEP);
    mCmWidget->setPitchStep(PITCH_STEP);
    connect(mCmWidget, &CameraManipulatorWidget::homeClicked, this,  &Map3dWidget::home);
    connect(mCmWidget, &CameraManipulatorWidget::zoomChanged, this,&Map3dWidget::setZoom);
    connect(mCmWidget, &CameraManipulatorWidget::upDownChanged, [=](double val){mEarthManipulator->pan(0,val);} );
    connect(mCmWidget, &CameraManipulatorWidget::leftRightChanged, [=](double val){mEarthManipulator->pan(val,0);} );
    connect(mCmWidget, &CameraManipulatorWidget::headChanged, [=](double val){mEarthManipulator->rotate(val,0);} );
    connect(mCmWidget, &CameraManipulatorWidget::pitchChanged, [=](double val){mEarthManipulator->rotate(0,val);} );
    connect(mCmWidget, &CameraManipulatorWidget::mapChange,this, &Map3dWidget::typeChanged);
    //-------------------------------------
    mCompassWidget = new CompassWidget(this);
    connect(mCmWidget, &CameraManipulatorWidget::headChanged, [=](double val){
        double degri = osg::RadiansToDegrees(val);
        mCompassWidget->setRotate(-degri);
    } );
    //-------------------------------
}

void Map3dWidget::setZoom(double val)
{
    mEarthManipulator->zoom(0, -val, mMapOpenGLWidget->getOsgViewer());
}

void Map3dWidget::home()
{
    mEarthManipulator->home(0);
    //        mEarthManipulator->setViewpoint(mHomeViewpoint);
    mCompassWidget->setPoint(0);
}

void Map3dWidget::typeChanged(bool isGeocentric)
{
    mIsGeocentric = isGeocentric;
    //qDebug()<<"isGeneric:"<<isGeocentric;
    mMapNodeGeo->setNodeMask(isGeocentric);
    mMapNodeProj->setNodeMask(!isGeocentric);
    //    mEarthManipulator->updateProjection()
    //    osg::Camera *c = new osg::Camera() ;
    //    mEarthManipulator->updateCamera(*c);
    //    mEarthManipulator->setInitialVFOV(0);
    //    auto cam = new osgEarth::Util::EarthManipulator;
    //    auto  settings = cam->getSettings();
    //    qDebug()<<settings->getOrthoTracksPerspective();
    //    settings->setOrthoTracksPerspective(isGeocentric);
    //    qDebug()<<settings->getOrthoTracksPerspective();
    //settings->setMinMaxPitch(90, 180);
    //cam->applySettings(settings);
    Viewpoint vp = mEarthManipulator->getViewpoint();
    //    qDebug()<<"vp.heading():"<<QString::fromUtf8(vp.heading()->asString().c_str());
    //    qDebug()<<"vp.pitch():"<<QString::fromUtf8(vp.pitch()->asString().c_str());
    //    qDebug()<<"vp.range():"<<QString::fromUtf8(vp.range()->asString().c_str());
    createManipulator();
    mMapOpenGLWidget->getOsgViewer()->setCameraManipulator(mEarthManipulator);
    mEarthManipulator->setViewpoint(vp);
}
void Map3dWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    if(mCmWidget)
        mCmWidget->move(0, this->height()- mCmWidget->height());
    if(mCompassWidget)
        mCompassWidget->move(this->width()- mCompassWidget->width() - 5, this->height()- mCompassWidget->height() - 5);
}

