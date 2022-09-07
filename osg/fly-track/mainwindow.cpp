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
#include <osgGA/GUIEventHandler>
#include <osgUtil/LineSegmentIntersector>
#include <osg/ShapeDrawable>
#include <osg/LineWidth>
#include <osgAnimation/BasicAnimationManager>
#include <osg/MatrixTransform>
#include <osg/io_utils>
#include <osg/NodeVisitor>

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

void MainWindow::initOpenglWidget()
{
    osg::Vec3Array* keyPoint = new osg::Vec3Array;
        keyPoint->push_back(osg::Vec3(-5.15, -88.89, 8.0));
        keyPoint->push_back(osg::Vec3(50.1688, -62.9621, 39.0));
        keyPoint->push_back(osg::Vec3(79.1318, -46.6088, 15.0));
        keyPoint->push_back(osg::Vec3(80.03, -26.95, 29.0));
        keyPoint->push_back(osg::Vec3(81.41, -6.42, 12.0));
        keyPoint->push_back(osg::Vec3(70.11, 12.47, 29.0));
        keyPoint->push_back(osg::Vec3(57.51, 28.49, 12.0));
        keyPoint->push_back(osg::Vec3(38.83, 45.23, 29.0));
        keyPoint->push_back(osg::Vec3(6.98, 61.87, 12.0));
        keyPoint->push_back(osg::Vec3(-23.46, 43.42, 29.0));
        keyPoint->push_back(osg::Vec3(-36.27, 22.40, 15.0));
        keyPoint->push_back(osg::Vec3(-42.94, -13.22, 29.0));
        keyPoint->push_back(osg::Vec3(-60.78, -41.55, 8.0));
        keyPoint->push_back(osg::Vec3(-41.95, -49.65, 29.0));
        osg::Node* ceep = osgDB::readNodeFile("/home/client111/Documents/project/fly-track/test.osgb");

//        // scene ceep
        osg::Group* root = new osg::Group;
        root->addChild(ceep);
        // Marking of key points and paths
        root->addChild(createMark(keyPoint));

        MainWindow::g_ntm = new osgGA::NodeTrackerManipulator;
        // Add a moving plane
        osg::Node* fly = loadFly(CreateAnimate(keyPoint, 7.0));
        root->addChild(fly);


        // Trace operator


        widget->getOsgViewer()->setCameraManipulator(g_ntm);
        widget->getOsgViewer()->setSceneData(root);

}



// Given vertex , And the speed of travel , Create a path
osg::AnimationPath* MainWindow::CreateAnimate(osg::Vec3Array* keyPoint, float speed)
{

    // Only 1 A little bit , Can't form a path
    if (keyPoint->size() <= 1)
    {

        return nullptr;
    }

    osg::AnimationPath* animationPath = new osg::AnimationPath;
    animationPath->setLoopMode(osg::AnimationPath::LOOP);

    // The time corresponding to the key point
    float t = 0.0;
    // toward
    osg::Quat rotate;
    for (int i = 0; i < keyPoint->size(); i++)
    {

        // The last point , Just press in the first point , Form a loop
        if ((keyPoint->size() - 1) == i)
        {

            // The orientation of the last point is not calculated , Just use the orientation of the last point
            animationPath->insert(t, osg::AnimationPath::ControlPoint(keyPoint->at(i), rotate));

            // Calculate the time of the last point
            t += ((keyPoint->at(0) - keyPoint->at(i)).length() / speed);

            // The orientation of the first point still points to the second point
            rotate.makeRotate(osg::Y_AXIS, keyPoint->at(1) - keyPoint->at(0));
            animationPath->insert(t, osg::AnimationPath::ControlPoint(keyPoint->at(0), rotate));
            // The loop ends
            break;
        }
        else
        {

            // Other points
            // If it's the first point , In time t=0.0,  The orientation is determined by the orientation of the first point and the second point
            // Calculate the orientation of the current point , Because our orientation changes horizontally on only one axis , So you can use a simple method
            // The viewport defaults to Y Axis , We want to turn it to a vector that looks from the first point to the second point
            rotate.makeRotate(osg::Y_AXIS, keyPoint->at(i + 1) - keyPoint->at(i));
            animationPath->insert(t, osg::AnimationPath::ControlPoint(keyPoint->at(i), rotate));
        }

        // The distance between two points divided by the speed
        t += ((keyPoint->at(i + 1) - keyPoint->at(i)).length() / speed);

    }

    return animationPath;
}

// Create a red ball as a sign , Given the center and radius
osg::Node* MainWindow::CreateSphere(osg::Vec3 center, float r)
{

    osg::Geode* gnode = new osg::Geode;
    osg::ShapeDrawable* sd = new osg::ShapeDrawable(new osg::Sphere(center, r));
    sd->setColor(osg::Vec4(1.0, 0.0, 0.0, 1.0));// Red
    gnode->addDrawable(sd);
    return gnode;
}

// Create lines , Given vertex and red width ,
osg::Node* MainWindow::CreateLine(osg::Vec3Array* vertex, float lineWidth)
{

    osg::Geode* gnode = new osg::Geode;
    osg::Geometry* geom = new osg::Geometry;
    gnode->addDrawable(geom);

    // Set vertex
    geom->setVertexArray(vertex);

    // Set the color
    osg::Vec4Array* color = new osg::Vec4Array();
    color->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));
    geom->setColorArray(color, osg::Array::BIND_OVERALL);

    // Set the line width
    osg::LineWidth* lw = new osg::LineWidth(lineWidth);
    geom->getOrCreateStateSet()->setAttribute(lw, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);
    // Turn off the light to make it brighter
    geom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);

    // Set add as line
    geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, vertex->size()));

    return gnode;
}

osg::Group* MainWindow::createMark(osg::Vec3Array* keyPoint)
{

    osg::Group* markGroup = new osg::Group();

    // Add a red ball as a key
    for (int i = 0; i < keyPoint->size(); i++)
    {

        markGroup->addChild(CreateSphere(keyPoint->at(i), 0.5));
    }

    // Add line
    markGroup->addChild(CreateLine(keyPoint, 1.0));

    return markGroup;
}


// Add a moving plane
osg::Node* MainWindow::loadFly(osg::AnimationPath* animation)
{

    // For rotating aircraft , Orient it properly
    osg::MatrixTransform* mt = new osg::MatrixTransform;

    osg::Node* glider = osgDB::readNodeFile("/home/client111/Documents/project/fly-track/glider.osgt");
    glider->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
    // The plane defaults to X Axis negative direction , Let's go around Z pivot -90 degree , Turn it towards Y Affirmative direction
    mt->setMatrix(osg::Matrix::scale(10.0, 10.0, 10.0) * osg::Matrix::rotate(osg::inDegrees(-90.0), osg::Z_AXIS));
    mt->addChild(glider);

    // Actual path control
    osg::MatrixTransform* persionMT = new osg::MatrixTransform;
    persionMT->setUpdateCallback(new osg::AnimationPathCallback(animation));
    persionMT->addChild(mt);

    // The trace operator sets the trace node
    g_ntm->setTrackNode(mt);
    g_ntm->setTrackerMode(osgGA::NodeTrackerManipulator::NODE_CENTER_AND_ROTATION);
    g_ntm->setRotationMode(osgGA::NodeTrackerManipulator::TRACKBALL);
    g_ntm->setAutoComputeHomePosition(false);
    g_ntm->setDistance(5.0);


    return persionMT;
}

