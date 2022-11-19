#include "visibility.h"
#include "map3dwidget.h"
#include "toolbarwidget.h"
#include "websocketclient.h"

#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthAnnotation/ModelNode>
#include <osg/Shader>
#include <osg/ShapeDrawable>
#include <osg/LineWidth>
#include <QDebug>
#include <osgEarth/Registry>
#include <osg/ClipNode>
#include <osg/ClipPlane>
#include <osgEarthAnnotation/ImageOverlay>
#include <osgEarthAnnotation/CircleNode>
#include <osgEarthAnnotation/RectangleNode>
#include <osgEarthAnnotation/EllipseNode>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthAnnotation/LabelNode>
#include <osgEarthAnnotation/LocalGeometryNode>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthAnnotation/ModelNode>

#include <osgEarthAnnotation/AnnotationEditing>
#include <osgEarthAnnotation/ImageOverlayEditor>

#include <osgEarthSymbology/GeometryFactory>
#include <osg/PolygonMode>

using namespace osgEarth;
using namespace osgEarth::Annotation;
using namespace osgEarth::Features;
using namespace osgEarth::Util;

#include <QDebug>

Visibility::Visibility(QWidget *parent)
    : PluginInterface(parent)
{
}
void Visibility::setUpUI()
{
    ToolBarWidget::Category cat = ToolBarWidget::Category::Analyze;
    QString nameSphere = "Sphere";
    mToolBar->addItem(cat, nameSphere, "qrc:/res/visibility.png",true);

    QString nameLine = "Line";
    mToolBar->addItem(cat, nameLine, "qrc:/res/visibility.png",true);

    QObject::connect(mToolBar,&ToolBarWidget::onItemClicked, [=](ToolBarWidget::Category category ,QString name, bool isCheck){
        if(cat == category && name == nameSphere)
        {
            if(isCheck)
            {
                QObject::connect(mMap3dWidget,&Map3dWidget::mouseEvent, this, &Visibility::makeSphere);
            }
            else
            {
                QObject::disconnect(mMap3dWidget,&Map3dWidget::mouseEvent, this, &Visibility::makeSphere);

                mMap3dWidget->removeNode(mBackVisibilityNode);
                mMap3dWidget->removeNode(mVisibilityNode);
            }
        }

        if(cat == category && name == nameLine)
        {
            if(isCheck)
            {
                QObject::connect(mMap3dWidget,&Map3dWidget::mouseEvent, this, &Visibility::drawLine);
            }
            else
            {
                QObject::disconnect(mMap3dWidget,&Map3dWidget::mouseEvent, this, &Visibility::drawLine);

                mMap3dWidget->removeNode(mBackVisibilityNode);
                mMap3dWidget->removeNode(mVisibilityNode);
            }
        }
    });
}

void Visibility::makeSphere(QMouseEvent *event, osgEarth::GeoPoint geoPos)
{
    if(event->button() == Qt::MouseButton::RightButton && event->type() == QEvent::Type::MouseButtonPress)
    {
            auto node = mSphere(20000.0f);

            osg::ClipNode* clipnode = new osg::ClipNode;
            osg::ClipPlane* clipplane = new osg::ClipPlane();
            clipplane->setClipPlane(0, 1, 0, 1);

            clipnode->addClipPlane(clipplane);
            clipnode->addChild(node);
            //osgEarth::GeoPoint point(osgEarth::SpatialReference::get("wgs84"), 52.859, 35.461);
// geoPos.z() += 20000;
            node->setPosition(geoPos);
            mMap3dWidget->addNode(clipnode);
            mMap3dWidget->goPosition(geoPos.x(), geoPos.y(), 100000);

    }
}

void Visibility::drawLine(QMouseEvent *event, GeoPoint geoPos)
{
    if(event->button() == Qt::MouseButton::RightButton && event->type() == QEvent::Type::MouseButtonPress)
    {
        FeatureNode* pathNode = nullptr;
            {
                Geometry* path = new LineString();
                path->push_back(geoPos.vec3d());
                path->push_back(geoPos.vec3d()+osg::Vec3d(5,6,7));

                Feature* pathFeature = new Feature(path, osgEarth::SpatialReference::get("wgs84"));
                pathFeature->geoInterp() = GEOINTERP_GREAT_CIRCLE;


                Style pathStyle;
                pathStyle.getOrCreate<LineSymbol>()->stroke()->color() = Color::White;
                pathStyle.getOrCreate<LineSymbol>()->stroke()->width() = 1.0f;
                pathStyle.getOrCreate<LineSymbol>()->tessellationSize() = 75000;
                pathStyle.getOrCreate<PointSymbol>()->size() = 5;
                pathStyle.getOrCreate<PointSymbol>()->fill()->color() = Color::Red;
                pathStyle.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
                pathStyle.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;

                //OE_INFO << "Path extent = " << pathFeature->getExtent().toString() << std::endl;

                pathNode = new FeatureNode(pathFeature, pathStyle);
                mMap3dWidget->addNode(pathNode);
}
    }
//                //labelGroup->addChild(new LabelNode(mapNode, GeoPoint(geoSRS, -170, 61.2), "Great circle path", labelStyle));
//            }


//        osg::Geode *geode = new osg::Geode;
//        osg::Geometry* geo = new osg::Geometry();

//        // define some vertices
//        osg::Vec3Array* v = new osg::Vec3Array;
//        v->push_back(geoPos.vec3d());
//        v->push_back(geoPos.vec3d()+osg::Vec3d(0.2, 0.3, 0.4));
//        v->dirty();
//        osg::LineWidth* linewidth = new osg::LineWidth();
//        linewidth->setWidth(50.0f);
//        geode->getOrCreateStateSet()->setAttributeAndModes(linewidth,
//                                                             osg::StateAttribute::ON);
//        osg::Vec4Array* c = new osg::Vec4Array;
//        c->push_back(osg::Vec4(1,0,0,1));
//        geo->setColorArray(c);
//        geo->setColorBinding(osg::Geometry::BIND_OVERALL);
//        geo->setVertexArray(v);

//        geo->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP,0, v->size()));
//        geode->addDrawable(geo);

//        osgEarth::Symbology::Style geomStyle;
//        geomStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_TO_TERRAIN;
//        geomStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_MAP;
//        geomStyle.getOrCreate<osgEarth::Symbology::ModelSymbol>()->setModel(geode);
//        osg::ref_ptr<osgEarth::Annotation::ModelNode> model;
//        model = new osgEarth::Annotation::ModelNode(mMap3dWidget->getMapNode(), geomStyle);

//        osg::Geode *geode = new osg::Geode;
//        osg::Geometry *g = new osg::Geometry;
//        osg::Vec3Array *v = new osg::Vec3Array;
//        osg::Vec3d(30000,30000,30000);
//        v->push_back(geoPos.vec3d());
//        v->push_back(geoPos.vec3d()+osg::Vec3d(0.2,0.3,0.4));
////        v->push_back(10,0,10);
////        v->push_back(0,0,10);

//        osg::DrawArrays *da = new
//        osg::DrawArrays(osg::PrimitiveSet::LINES,0,2,1);

//        g->setVertexArray(v);
//        g->addPrimitiveSet(da);

//        geode->addDrawable(g);
//        geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

//        Geometry* geom = new Polygon ();
//        geom->push_back(osg::Vec3d(0, 40, 0));
//                geom->push_back(osg::Vec3d(-60, 40, 0));

//                Feature* feature = new Feature(geom, osgEarth::SpatialReference::get("wgs84"));
//                feature->geoInterp() = GEOINTERP_RHUMB_LINE;

//                Style geomStyle;
//                geomStyle.getOrCreate<LineSymbol>()->stroke()->color() = Color::Cyan;
//                geomStyle.getOrCreate<LineSymbol>()->stroke()->width() = 5.0f;
//                geomStyle.getOrCreate<LineSymbol>()->tessellationSize() = 75000;
//                geomStyle.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
//                geomStyle.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;

//                FeatureNode* fnode = new FeatureNode(feature, geomStyle);




//        mMap3dWidget->addNode(fnode);

//    }
}

//void Visibility::onMouseEvent(QMouseEvent *event, osgEarth::GeoPoint geoPos)
//{
// if(event->button() == Qt::MouseButton::RightButton && event->type() == QEvent::Type::MouseButtonPress)
// {

// mMap3dWidget->removeNode(mBackVisibilityNode);
// mMap3dWidget->removeNode(mVisibilityNode);

// geoPos.makeGeographic();
//// mMainWindow->webSocket()->sendMessage(QString::fromStdString(geoPos.toString()));

// mBackVisibilityNode = makeBackground(20000.0f);
// //osgEarth::GeoPoint point(osgEarth::SpatialReference::get("wgs84"), 52.859, 35.461);
// mBackVisibilityNode->setPosition(geoPos);
// mMap3dWidget->addNode(mBackVisibilityNode);
// ///////////
// QVector<osg::Vec3d> vertices;
// vertices.push_back( osg::Vec3d(geoPos.x() - 0.089,geoPos.y() + 0.059, 0));
//// vertices.push_back( osg::Vec3d(52.86,35.55, 0) );
// vertices.push_back( osg::Vec3d(geoPos.x() + 0.001,geoPos.y() + 0.089, 0));
//// vertices.push_back( osg::Vec3d(52.96,35.52, 0) );
// vertices.push_back( osg::Vec3d(geoPos.x() + 0.101,geoPos.y() + 0.059, 0));
//// vertices.push_back( osg::Vec3d(53.01,35.47, 0) );
// vertices.push_back( osg::Vec3d(geoPos.x() + 0.151,geoPos.y() + 0.009, 0));
//// vertices.push_back( osg::Vec3d(52.92,35.37, 0) );
// vertices.push_back( osg::Vec3d(geoPos.x() + 0.061,geoPos.y() - 0.091, 0));
//// vertices.push_back( osg::Vec3d(52.80,35.34, 0) );
// vertices.push_back( osg::Vec3d(geoPos.x() - 0.059,geoPos.y() - 0.121, 0));
//// vertices.push_back( osg::Vec3d(52.76,35.40, 0) );
// vertices.push_back( osg::Vec3d(geoPos.x() - 0.099,geoPos.y() - 0.061, 0));
//// vertices.push_back( osg::Vec3d(52.74,35.49, 0) );
// vertices.push_back( osg::Vec3d(geoPos.x() - 0.119,geoPos.y() + 0.029, 0));

// mVisibilityNode = makepolygan(vertices);
// mMap3dWidget->addNode(mVisibilityNode);

// //Set view point------------------------------------------------------------------
// mMap3dWidget->goPosition(geoPos.x(), geoPos.y(), 100000);
// }

// if(event->button() == Qt::MouseButton::LeftButton && event->type() == QEvent::Type::MouseButtonDblClick)
// {
// osgEarth::Symbology::Style pm;
// pm.getOrCreate<osgEarth::Symbology::IconSymbol>()->url()->setLiteral("/home/client110/Downloads/setting.png");
// pm.getOrCreate<osgEarth::Symbology::IconSymbol>()->declutter() = true;
// pm.getOrCreate<osgEarth::Symbology::TextSymbol>()->halo() = osgEarth::Color("#5f5f5f");

// auto pn = new osgEarth::Annotation::PlaceNode(geoPos, "", pm);
// pn->setScale(osg::Vec3(0.5,0.5,0.5));
// mMap3dWidget->addNode(pn);
// }
//}

osgEarth::Annotation::FeatureNode* Visibility::makepolygan(QVector<osg::Vec3d> vertices){

    osg::ref_ptr<osgEarth::Symbology::Geometry> geom = new osgEarth::Symbology::Polygon();
    for (int i=0; i<vertices.length();i++){
        geom->push_back(vertices[i]);
    }

    osg::ref_ptr<osgEarth::Features::Feature> feature = new osgEarth::Features::Feature(geom, osgEarth::SpatialReference::get("wgs84"));
    feature->geoInterp() = osgEarth::GEOINTERP_RHUMB_LINE;
    osgEarth::Symbology::Style geomStyle;
    geomStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()->stroke()->color() = osgEarth::Color::Green;
    geomStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()->stroke()->width() = 5.0f;
    geomStyle.getOrCreate<osgEarth::Symbology::PolygonSymbol>()->fill()->color() =osgEarth::Color(osg::Vec4(0.0f,1.0f,0.0f,0.5f));
    //geomStyle.getOrCreate<osgEarth::Symbology::LineSymbol>()->tessellationSize()->set(75000, Units::METERS);
    geomStyle.getOrCreate<osgEarth::Symbology::RenderSymbol>()->depthOffset()->enabled() = true;
    geomStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_RELATIVE_TO_TERRAIN;
    geomStyle.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_DRAPE;
    osg::ref_ptr<osgEarth::Annotation::FeatureNode> gnode = new osgEarth::Annotation::FeatureNode(feature, geomStyle);
    return gnode.release();

}

osgEarth::Annotation::ModelNode *Visibility::mSphere(float radius)
{
    osg::Vec3 eye(0.3f,0.2f,1.0f);
    osg::ref_ptr<osg::Sphere> pSphereShape = new osg::Sphere(eye, radius);
    osg::ref_ptr<osg::ShapeDrawable> pShapeDrawable = new osg::ShapeDrawable(pSphereShape.get());

    pShapeDrawable->setColor(osg::Vec4(0.0, 0.5f, 1.0, 0.3f));

    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(1.0), osg::StateAttribute::ON);

    geode->addDrawable(pShapeDrawable.get());



    // osg::ref_ptr<osg::Node> mDrownode = makeShape(osg::Vec3(position.x(),position.y(),position.z()),20000.0f);
    osgEarth::Symbology::Style style;

    style.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_ABSOLUTE;
    style.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_DRAPE;
    style.getOrCreate<osgEarth::Symbology::ModelSymbol>()->setModel(geode);

    osg::ref_ptr<osgEarth::Annotation::ModelNode> model;
    model = new osgEarth::Annotation::ModelNode(mMap3dWidget->getMapNode(), style);

    return model.release();
}


//osgEarth::Annotation::ModelNode *Visibility::makeBackground(float radius)
//{
// osg::Vec3 eye(0.3f,0.2f,1.0f);
// osg::ref_ptr<osg::Sphere> pSphereShape = new osg::Sphere(eye, radius);
// osg::ref_ptr<osg::ShapeDrawable> pShapeDrawable = new osg::ShapeDrawable(pSphereShape.get());

// pShapeDrawable->setColor(osg::Vec4(1.0, 0.0, 0.0, 0.3f));

// osg::ref_ptr<osg::Geode> geode = new osg::Geode();
// geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
// geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(1.0), osg::StateAttribute::ON);

// geode->addDrawable(pShapeDrawable.get());



// // osg::ref_ptr<osg::Node> mDrownode = makeShape(osg::Vec3(position.x(),position.y(),position.z()),20000.0f);
// osgEarth::Symbology::Style style;

// style.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()->clamping() = osgEarth::Symbology::AltitudeSymbol::CLAMP_RELATIVE_TO_TERRAIN;
// style.getOrCreate<osgEarth::Symbology::AltitudeSymbol>()->technique() = osgEarth::Symbology::AltitudeSymbol::TECHNIQUE_DRAPE;
// style.getOrCreate<osgEarth::Symbology::ModelSymbol>()->setModel(geode);

// osg::ref_ptr<osgEarth::Annotation::ModelNode> model;
// model = new osgEarth::Annotation::ModelNode(mMap3dWidget->getMapNode(), style);

// return model.release();
//}


