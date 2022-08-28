#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <osgQOpenGL/osgQOpenGLWidget>

#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osg/CoordinateSystemNode>
#include <osg/ShapeDrawable>
#include <osgDB/FileUtils>

#include <QDebug>

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

    ui->gridLayout->addWidget(widget);

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
    model_3d = new osg::Group;
    osg::ref_ptr<osg::Node> baseModel = createBase(osg::Vec3(center.x(), center.y(), center.z()),100);
    tower = createModel();
    model_3d->addChild(tower);
    model_3d->addChild(baseModel);
    widget->getOsgViewer()->setSceneData(model_3d);


    osgUtil::Optimizer optimizer;
    optimizer.optimize(model_3d);

    //widget->getOsgViewer()->getCamera()->setClearColor(osg::Vec4(255.0f,33.0f,43.0f,100.0f));
    widget->getOsgViewer()->getCamera()->setViewport(20,67,800,600);

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

osg::Node* MainWindow::createModel()
{
    milad = osgDB::readRefNodeFile("/home/client112/Downloads/OBJ/Milad.osgb");
    james_web = osgDB::readRefNodeFile("/home/client112/Downloads/james-web.osg");
    if (milad)
        {
                positioned = new osg::MatrixTransform;
                positioned->setDataVariance(osg::Object::DYNAMIC);

//                positioned->setMatrix(osg::Matrix::translate(osg::Vec3(center.x(),center.y(),center.z()))*
//                                             osg::Matrix::scale(size,size,size)*
//                                             osg::Matrix::rotate(osg::inDegrees(90.0f),0.0f,0.0f,1.0f));

                positioned->setMatrix(osg::Matrix::translate(0,0,0));
                //positioned->setUpdateCallback(new MyTransformCallback(0,0,0));
                positioned->addChild(milad);

    }

    return positioned;
}


//delete model on runtime
void MainWindow::on_pushButton_pressed()
{

    //positioned->setUpdateCallback(new MyTransformCallback(3,6,100));

    positioned->setMatrix(osg::Matrix::scale(10,10,10));
    positioned->removeChild(james_web);
    positioned->setMatrix(osg::Matrix::translate(10,15,30));

}

void MyTransformCallback::operator()(osg::Node *node, osg::NodeVisitor *nv)
{
    osg::MatrixTransform* transform = dynamic_cast<osg::MatrixTransform*>(node);
    if (nv && transform && nv->getFrameStamp())
    {

        transform->setMatrix(osg::Matrix::translate(move));
        traverse(node,nv);
}
}
//add model on runtime
void MainWindow::on_pushButton_2_clicked()
{
    positioned->setMatrix(osg::Matrix::scale(10,10,10));
    positioned->addChild(james_web);

}


//toggle visibilty of model
void MainWindow::on_pushButton_3_toggled(bool checked)
{
        james_web->setNodeMask(!checked);

        if (!checked){
            ui->pushButton_3->setText("Hide");
        }
        else {
            ui->pushButton_3->setText("Show");
        }
}































