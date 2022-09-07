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


    model_3d = new osg::Group;

    osg::Vec3 center(0.0f,0.0f,0.f);

    locationTree = new osg::MatrixTransform();
    locationCar = new osg::MatrixTransform();


    osg::ref_ptr<osg::Node> baseModel = createBase(osg::Vec3(center.x(), center.y(), center.z()),100);

    osg::ref_ptr<osg::Node> tree = osgDB::readRefNodeFile("/home/client111/Documents/OpenSceneGraph-Data/cow.osgt");
    int x =0;
    for (int i;i<100;i++) {
        locationTree = new osg::MatrixTransform();
        locationTree->setMatrix(osg::Matrix::translate(osg::Vec3(center.x()-4955+x,center.y()+3,center.z()+1))*
                                                    osg::Matrix::scale(1,1,1)*
                                                    osg::Matrix::rotate(osg::inDegrees(90.0f),0.0f,0.0f,1.0f));
        locationTree->addChild(tree);
        model_3d->addChild(locationTree);
        x+=100;

    }




    osg::ref_ptr<osg::Node> car = osgDB::readRefNodeFile("/home/client111/Documents/project/fly-track/glider.osgt");
    car->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
    locationCar->setMatrix(osg::Matrix::scale(10.0, 10.0, 10.0) * osg::Matrix::rotate(osg::inDegrees(-90.0), osg::Z_AXIS));
    locationCar->addChild(car);
    locationCar->addUpdateCallback(new osg::AnimationPathCallback(carAnimationPath()));
    model_3d->addChild(locationCar);
    model_3d->addChild(baseModel);
    widget->getOsgViewer()->setCameraManipulator(g_ntm);
    g_ntm->setTrackNode(car);
    widget->getOsgViewer()->setSceneData(model_3d);
    g_ntm->setDistance(50.0);
    g_ntm->setElevation(-10);
}




osg::AnimationPath *MainWindow::carAnimationPath()
{
osg::AnimationPath* path = new osg::AnimationPath();
path->setLoopMode(osg::AnimationPath::LOOP);


/** point 1 - start point **/
path->insert(0.0, osg::AnimationPath::ControlPoint(osg::Vec3d(0.0,-2495.0,0.0),
osg::Quat(osg::inDegrees(0.0f),osg::Z_AXIS)));
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

static double de = 0;
void MainWindow::on_pushButton_clicked()
{
    de = de+10;
    osg::AnimationPath* path = new osg::AnimationPath();

    /** point 1 - start point **/
    path->insert(10, osg::AnimationPath::ControlPoint(osg::Vec3d(0.0,-2495.0 + de*3,de),
    osg::Quat(osg::inDegrees(90.0),osg::Z_AXIS)));
    locationCar->addUpdateCallback(new osg::AnimationPathCallback(path));
}
