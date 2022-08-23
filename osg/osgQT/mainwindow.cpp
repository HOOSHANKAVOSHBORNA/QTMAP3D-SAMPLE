#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <osgQOpenGL/osgQOpenGLWidget>

#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osg/CoordinateSystemNode>
#include <osg/ShapeDrawable>
#include <osgDB/FileUtils>


#include <osg/MatrixTransform>
#include <osg/Switch>
#include <osg/Types>
#include <osgText/Text>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/PositionAttitudeTransform>
#include <osgSim/OverlayNode>

#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/SphericalManipulator>

#include <osgGA/Device>

#include <QApplication>
#include <QSurfaceFormat>

#include <iostream>

#include <osg/io_utils>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    widget = new osgQOpenGLWidget(this);
    QObject::connect(widget, &osgQOpenGLWidget::initialized, this, &MainWindow::initOpenglWidget);

    ui->verticalLayout_2->addWidget(widget);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initOpenglWidget()
{
    // set up the camera manipulators.
    {
//        osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;

//        keyswitchManipulator->addMatrixManipulator('1', "Trackball", new osgGA::TrackballManipulator());
//        keyswitchManipulator->addMatrixManipulator('2', "Flight", new osgGA::FlightManipulator());
//        keyswitchManipulator->addMatrixManipulator('3', "Drive", new osgGA::DriveManipulator());
//        keyswitchManipulator->addMatrixManipulator('4', "Terrain", new osgGA::TerrainManipulator());
//        keyswitchManipulator->addMatrixManipulator('5', "Orbit", new osgGA::OrbitManipulator());
//        keyswitchManipulator->addMatrixManipulator('6', "FirstPerson", new osgGA::FirstPersonManipulator());
//        keyswitchManipulator->addMatrixManipulator('7', "Spherical", new osgGA::SphericalManipulator());

        osgGA::TerrainManipulator* terrain = new osgGA::TerrainManipulator;
        widget->getOsgViewer()->setCameraManipulator(terrain);
    }

    osg::Vec3 center(0.0f,0.0f,0.f);
    float radius = 80.0f;
    double baseHeight = center.z()-radius*0.5;


    model_3d = new osg::Group;
    osg::ref_ptr<osg::Node> baseModel = createBase(osg::Vec3(center.x(), center.y(), center.z()),100);
    tower = createModel(osg::Vec3(15, center.y(), 0),radius*2.f);




    //model_3d->addChild(james_web);
    model_3d->addChild(tower);
    model_3d->addChild(baseModel);





    widget->getOsgViewer()->setSceneData(model_3d);









    //osg::ref_ptr<osg::Node> earth = createEarth();
    //model_3d->addChild(earth);
    //model_3d->addChild(milad);
    // optimize the scene graph, remove redundant nodes and state etc.
    osgUtil::Optimizer optimizer;
    optimizer.optimize(model_3d);

    //widget->getOsgViewer()->getCamera()->setClearColor(osg::Vec4(255.0f,33.0f,43.0f,100.0f));
    //widget->getOsgViewer()->getCamera()->setViewport(200,67,600,500);

}






osg::Node* MainWindow::createBase(const osg::Vec3 &center, float radius)
{

    int numTilesX = 5;
    int numTilesY = 5;

    float width = 2*radius;
    float height = 2*radius;

    osg::Vec3 v000(center - osg::Vec3(width*0.5f,height*0.5f,0.0f));
    osg::Vec3 dx(osg::Vec3(width/((float)numTilesX),0.0,0.0f));
    osg::Vec3 dy(osg::Vec3(0.0f,height/((float)numTilesY),0.0f));

    // fill in vertices for grid, note numTilesX+1 * numTilesY+1...
    osg::Vec3Array* coords = new osg::Vec3Array;
    int iy;
    for(iy=0;iy<=numTilesY;++iy)
    {
        for(int ix=0;ix<=numTilesX;++ix)
        {
            coords->push_back(v000+dx*(float)ix+dy*(float)iy);
        }
    }

    //Just two colours - black and white.
    osg::Vec4Array* colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(1.0f,1.0f,1.0f,1.0f)); // white
    colors->push_back(osg::Vec4(0.0f,0.0f,0.0f,1.0f)); // black
    //Drawing Quads
    osg::ref_ptr<osg::DrawElementsUShort> whitePrimitives = new osg::DrawElementsUShort(GL_QUADS);
    osg::ref_ptr<osg::DrawElementsUShort> blackPrimitives = new osg::DrawElementsUShort(GL_QUADS);

    int numIndicesPerRow=numTilesX+1;
    for(iy=0;iy<numTilesY;++iy)
    {
        for(int ix=0;ix<numTilesX;++ix)
        {
            osg::DrawElementsUShort* primitives = ((iy+ix)%2==0) ? whitePrimitives.get() : blackPrimitives.get();
            primitives->push_back(ix    +(iy+1)*numIndicesPerRow);
            primitives->push_back(ix    +iy*numIndicesPerRow);
            primitives->push_back((ix+1)+iy*numIndicesPerRow);
            primitives->push_back((ix+1)+(iy+1)*numIndicesPerRow);
        }
    }

    // set up a single normal
    osg::Vec3Array* normals = new osg::Vec3Array;
    normals->push_back(osg::Vec3(0.0f,0.0f,100.0f));

    osg::Geometry* geom = new osg::Geometry;

    geom->setVertexArray(coords);


    geom->setColorArray(colors, osg::Array::BIND_PER_PRIMITIVE_SET);

    geom->setNormalArray(normals, osg::Array::BIND_OVERALL);

    geom->addPrimitiveSet(whitePrimitives.get());
    geom->addPrimitiveSet(blackPrimitives.get());

    osg::Geode* geode = new osg::Geode;
    geode->addDrawable(geom);

    return geode;

}

osg::Node* MainWindow::createModel(const osg::Vec3& center, float radius)
{
    osg::ref_ptr<osg::Group> miladmodel = new osg::Group;
    osg::ref_ptr<osg::Node> milad = osgDB::readRefNodeFile("/home/client112/Downloads/OBJ/Milad.osgb");
    if (milad)
        {
        const osg::BoundingSphere& bs = milad->getBound();
        float size = radius/bs.radius()*0.3f;
                positioned = new osg::MatrixTransform;
                positioned->setDataVariance(osg::Object::STATIC);
                positioned->setMatrix(osg::Matrix::translate(osg::Vec3(center.x(),center.y(),center.z()))*
                                             osg::Matrix::scale(size,size,size)*
                                             osg::Matrix::rotate(osg::inDegrees(90.0f),0.0f,0.0f,1.0f));

                positioned->addChild(milad);

    }
#ifndef OSG_GLES2_AVAILABLE
    milad->getOrCreateStateSet()->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
    #endif

//    return miladmodel.release();
    return positioned;
}

osg::MatrixTransform MainWindow::updatePose(float x, float y, float z)
{
    positioned->setMatrix(osg::Matrix::translate(osg::Vec3(x,y,z))*
                                 osg::Matrix::scale(6.1,6.1,6.1)*
                                 osg::Matrix::rotate(osg::inDegrees(90.0f),2.0f,0.0f,1.0f));
    //return *positioned;
}









void MainWindow::on_pushButton_pressed()
{

    osg::ref_ptr<osg::MatrixTransform> update = new osg::MatrixTransform;
    update->setMatrix(osg::Matrix::translate(osg::Vec3(5,6,7))*
                      osg::Matrix::scale(8,8,8)*
                      osg::Matrix::rotate(osg::inDegrees(90.0f),0.0f,0.0f,1.0f));

    //update->setUpdateCallback(updatePose(8,5,6),4,6);\

    //update->addChild(tower);
//    positioned->setMatrix(osg::Matrix::translate(osg::Vec3(5,6,7))*
//                          osg::Matrix::scale(8,8,8)*
//                          osg::Matrix::rotate(osg::inDegrees(90.0f),0.0f,0.0f,1.0f));

    //positioned->addChild(tower);
    //positioned->setUpdateCallback(update);


    //model_3d->addChild(movingModel);


}
