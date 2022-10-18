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
#include <vehicle.h>
#include "truck.h"
#include<QDebug>
#include "fly.h"

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

    widget->getOsgViewer()->getSceneData();
    osgGA::NodeTrackerManipulator* g_ntm = new osgGA::NodeTrackerManipulator;
    osg::Group *pack = new osg::Group;
    //model_3d = new vehicle;
    //model_3d->movePack(osg::Vec3(5,5,0),10);
    //model_3d->spinHolder(osg::Vec3(-20,20,0));

    truck = new Truck(pack);
    rocket = new FlyModel(pack, "../../../QTMAP3D-DATA/dataosgearth/model/truck/rocket.osgt");
    pack->addChild(truck);
    pack->addChild(rocket);

    truck->moveTo(osg::Vec3d(-20, -40, 10), 5);
    truck->aimTarget(osg::Vec3(5,10,6));

    rocket->flyTo(osg::Vec3(8,10,12),5);

    widget->getOsgViewer()->setCameraManipulator(g_ntm);
    widget->getOsgViewer()->setSceneData(pack);

    //g_ntm->setTrackNode(pack);
    //g_ntm->setDistance(50.0);
    //g_ntm->setTrackNode(model_3d);
    //widget->getOsgViewer()->setSceneData(model_3d);
}

void MainWindow::on_pushButton_toggled(bool checked)
{
    truck->moveTo(osg::Vec3d(20, 0, 0), 5);
    truck->aimTarget(osg::Vec3(-5,-5,1));
    //model_3d->setPause(checked);

    truck->shoot(1);
}
