#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <osgQOpenGL/osgQOpenGLWidget>
#include <osgDB/ReadFile>
#include <osgGA/TerrainManipulator>
#include <osgViewer/Viewer>
#include <osgSim/OverlayNode>
#include <osg/MatrixTransform>
#include <osg/AnimationPath>
#include <osgGA/NodeTrackerManipulator>

#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    widget = new osgQOpenGLWidget(this);
    QObject::connect(widget, &osgQOpenGLWidget::initialized, this, &MainWindow::initOpenglWidget);
    ui->horizontalLayout->addWidget(widget);

}

MainWindow::~MainWindow()
{
    delete ui;
}


osg::Node* MainWindow::createBase(const osg::Vec3 &center, float radius)
{

    int numTilesX = 8;
    int numTilesY = 5;

    float width = radius/15;
    float height = 100*radius;

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





void MainWindow::initOpenglWidget()
{
//    osgGA::TerrainManipulator* terrain = new osgGA::TerrainManipulator;
//    widget->getOsgViewer()->setCameraManipulator(terrain);
    osgGA::NodeTrackerManipulator* g_ntm = new osgGA::NodeTrackerManipulator;

    carAnim = new osg::AnimationPathCallback;
    cowAnim = new osg::AnimationPathCallback;
    wheelAnimR = new osg::AnimationPathCallback;
    wheelAnimR->setPivotPoint(osg::Vec3(0,0,25));
    wheelPathR = new osg::AnimationPath();

    wheelAnimL = new osg::AnimationPathCallback;
    wheelAnimL->setPivotPoint(osg::Vec3(0,0,25));
    wheelPathL = new osg::AnimationPath();


    rotate = new osg::AnimationPath();
    rotate->setLoopMode(osg::AnimationPath::LoopMode::LOOP);

    model_3d = new osg::Group;


    osg::Vec3 center(0.0f,0.0f,0.f);

    locationTree = new osg::MatrixTransform();
    locationCar = new osg::PositionAttitudeTransform();


    osg::ref_ptr<osg::Node> baseModel = createBase(osg::Vec3(center.x(), center.y(), center.z()),100);

    osg::ref_ptr<osg::Node> tree = osgDB::readRefNodeFile("/home/client111/Documents/OpenSceneGraph-Data/spaceship.osgt");
    int x =0;
    for (int i;i<100;i++) {
        locationTree = new osg::MatrixTransform();
        locationTree->setMatrix(osg::Matrix::translate(osg::Vec3(center.x()-10000+x,center.y()+10,center.z()+3))*
                                                    osg::Matrix::scale(1,1,1)*
                                                    osg::Matrix::rotate(osg::inDegrees(90.0),0.0,0.0,1.0));
        locationTree->addChild(tree);
        model_3d->addChild(locationTree);
        x+=100;

    }

    cowPos = new osg::PositionAttitudeTransform;
    cowPos->setPosition(osg::Vec3d(0,0,1.5));
    cowPos->setScale(osg::Vec3d(0.1,0.1,0.1));
    osg::Node* cow = osgDB::readNodeFile("/home/client111/Documents/OpenSceneGraph-Data/cow.osgt");
    cowPos->addChild(cow);

    mt = new osg::MatrixTransform;

    osg::ref_ptr<osg::Node> car = osgDB::readRefNodeFile("/home/client111/Documents/project/fly-track/glider.osgt");
    car->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
//    locationCar->setMatrix(osg::Matrix::scale(10.0, 10.0, 10.0) * osg::Matrix::rotate(osg::inDegrees(-90.0), osg::Z_AXIS));
    locationCar->setScale(osg::Vec3(4,4,4));
    locationCar->setPosition(osg::Vec3(0,0,1.0f));
    locationCar->setAttitude(osg::Quat(osg::inDegrees(-90.0),osg::Z_AXIS));
    locationCar->addChild(car);
    mt->addChild(locationCar);
    mt->addChild(cowPos);
    carAnim->setAnimationPath(carAnimationPath());
    mt->setUpdateCallback(carAnim);

    osg::ref_ptr<osg::Node> wheel = osgDB::readRefNodeFile("/home/client111/Documents/project/glider/move-btn-animate/wheel.osgt");

    wheelPosR = new osg::PositionAttitudeTransform;


    wheelPosR->addChild(wheel);
    wheelPosR->setPosition(osg::Vec3(2,-0.55f,0.5));
    wheelPosR->setScale(osg::Vec3(0.02f,0.02f,0.02f));
    mt->addChild(wheelPosR);
    wheelAnimR->setAnimationPath(wheelAnimationPathR());
    wheelPosR->setUpdateCallback(wheelAnimR);

    wheelPosL = new osg::PositionAttitudeTransform;
    wheelPosL->addChild(wheel);
    wheelPosL->setPosition(osg::Vec3(-2.0,-0.55f,0.5));
    wheelPosL->setScale(osg::Vec3(0.02f,0.02f,0.02f));
    wheelPosL->setAttitude(osg::Quat(osg::inDegrees(180.0),osg::Z_AXIS));

    mt->addChild(wheelPosL);
    wheelAnimL->setAnimationPath(wheelAnimationPathL());
    wheelPosL->setUpdateCallback(wheelAnimL);



    model_3d->addChild(mt);
    model_3d->addChild(baseModel);
    widget->getOsgViewer()->setCameraManipulator(g_ntm);
    g_ntm->setTrackNode(car);
    widget->getOsgViewer()->setSceneData(model_3d);
    g_ntm->setDistance(50.0);


    cowAnim->setAnimationPath(rotate);
    cowPos->setUpdateCallback(cowAnim);
//    g_ntm->setElevation(-10);
}




osg::AnimationPath *MainWindow::carAnimationPath()
{
osg::AnimationPath* path = new osg::AnimationPath();
path->setLoopMode(osg::AnimationPath::LOOP);


/** point 1 - start point **/
path->insert(0.0, osg::AnimationPath::ControlPoint(osg::Vec3d(0.0,-2495.0,0.0),
osg::Quat(osg::inDegrees(0.0),osg::Z_AXIS)));
path->insert(30, osg::AnimationPath::ControlPoint(osg::Vec3d(0.0,-500.0,0.0)));
//           osg::Quat(osg::inDegrees(90.0f),osg::Z_AXIS)));
/** point 2 **/
//path->insert(1.2, osg::AnimationPath::ControlPoint(osg::Vec3d(-60.0,+60.0,0.0)));
//           osg::Quat(osg::inDegrees(90.0f),osg::Z_AXIS)));
//path->insert(1.7, osg::AnimationPath::ControlPoint(osg::Vec3d(60.0,-60.0,0.0),
//           osg::Quat(osg::inDegrees(180.0f),osg::Z_AXIS)));

/** point 3 **/
//path->insert(2.7, osg::AnimationPath::ControlPoint(osg::Vec3d(-60.0,+60.0,0.0)));
//           osg::Quat(osg::inDegrees(180.0f),osg::Z_AXIS)));
//path->insert(2.9, osg::AnimationPath::ControlPoint(osg::Vec3d(60.0,60.0,0.0),
//           osg::Quat(osg::inDegrees(270.0f),osg::Z_AXIS)));

///** point 4 **/
//path->insert(3.9, osg::AnimationPath::ControlPoint(osg::Vec3d(-60.0,+60.0,0.0)));
//           osg::Quat(osg::inDegrees(270.0f),osg::Z_AXIS)));
//path->insert(4.1, osg::AnimationPath::ControlPoint(osg::Vec3d(-60.0,60.0,0.0),
//           osg::Quat(osg::inDegrees(360.0f),osg::Z_AXIS)));

///** back to point 1 **/
//path->insert(5.1, osg::AnimationPath::ControlPoint(osg::Vec3d(-60.0,+60.0,0.0)));
//           osg::Quat(osg::inDegrees(360.0f),osg::Z_AXIS)));

return path;
}

osg::AnimationPath *MainWindow::wheelAnimationPathR()
{

    osg::AnimationPath::ControlPoint cp;
    osg::AnimationPath::ControlPoint cp2;
    osg::AnimationPath::ControlPoint cp3;

    cp3.setRotation(osg::Quat(osg::inDegrees(359.9),osg::X_AXIS));
    cp2.setRotation(osg::Quat(osg::inDegrees(180.0),osg::X_AXIS));
    cp.setRotation(osg::Quat(osg::inDegrees(0.0),osg::X_AXIS));

    cp.setScale(wheelPosR->getScale());
    cp.setPosition(wheelPosR->getPosition());
    cp2.setScale(wheelPosR->getScale());
    cp2.setPosition(wheelPosR->getPosition());
    cp3.setScale(wheelPosR->getScale());
    cp3.setPosition(wheelPosR->getPosition());




    wheelPathR->setLoopMode(osg::AnimationPath::LOOP);
    wheelPathR->insert(0.0,cp);
    wheelPathR->insert(0.5,cp2);
    wheelPathR->insert(1.0,cp3);

    return wheelPathR;
}

osg::AnimationPath *MainWindow::wheelAnimationPathL()
{
    osg::AnimationPath::ControlPoint cp1;
    osg::AnimationPath::ControlPoint cp2;
    osg::AnimationPath::ControlPoint cp3;


    cp1.setRotation(osg::Quat(osg::inDegrees(0.0),osg::X_AXIS,osg::inDegrees(0.0),osg::Y_AXIS,osg::inDegrees(180.0),osg::Z_AXIS));
    cp2.setRotation(osg::Quat(osg::inDegrees(180.0),osg::X_AXIS,osg::inDegrees(0.0),osg::Y_AXIS,osg::inDegrees(180.0),osg::Z_AXIS));
    cp3.setRotation(osg::Quat(osg::inDegrees(359.9),osg::X_AXIS,osg::inDegrees(0.0),osg::Y_AXIS,osg::inDegrees(180.0),osg::Z_AXIS));


    cp1.setScale(wheelPosL->getScale());
    cp1.setPosition(wheelPosL->getPosition());
    cp2.setScale(wheelPosL->getScale());
    cp2.setPosition(wheelPosL->getPosition());
    cp3.setScale(wheelPosL->getScale());
    cp3.setPosition(wheelPosL->getPosition());




    wheelPathL->setLoopMode(osg::AnimationPath::LOOP);
    wheelPathL->insert(0,cp1);
    wheelPathL->insert(0.5,cp2);
    wheelPathL->insert(1.0,cp3);

    return wheelPathL;
}

void MainWindow::on_pushButton_clicked()
{
    osg::AnimationPath::ControlPoint cp;
    osg::AnimationPath::ControlPoint cp2;
    osg::AnimationPath::ControlPoint cp3;

    cp3.setRotation(osg::Quat(osg::inDegrees(359.9),osg::Z_AXIS));
    cp2.setRotation(osg::Quat(osg::inDegrees(180.0),osg::Z_AXIS));
    cp.setRotation(osg::Quat(osg::inDegrees(0.0),osg::Z_AXIS));

    cp.setScale(cowPos->getScale());
    cp.setPosition(cowPos->getPosition());
    cp2.setScale(cowPos->getScale());
    cp2.setPosition(cowPos->getPosition());
    cp3.setScale(cowPos->getScale());
    cp3.setPosition(cowPos->getPosition());

    rotate->insert(0,cp);
    rotate->insert(2,cp2);
    rotate->insert(4,cp3);

}
