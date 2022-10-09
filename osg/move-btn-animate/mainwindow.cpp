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

    osgGA::NodeTrackerManipulator* g_ntm = new osgGA::NodeTrackerManipulator;


    //model_3d = new vehicle;
    //model_3d->movePack(osg::Vec3(5,5,0),10);
    //model_3d->spinHolder(osg::Vec3(-20,20,0));



    truck = new Truck;


    truck->moveTo(osg::Vec3d(-20, 0, 0), 5);
    truck->aimTarget(osg::Vec3(5,5,6));

    widget->getOsgViewer()->setCameraManipulator(g_ntm);
    //g_ntm->setTrackNode(model_3d);
    //g_ntm->setTrackNode(truck);
    //widget->getOsgViewer()->setSceneData(model_3d);
    widget->getOsgViewer()->setSceneData(truck);
    //g_ntm->setDistance(50.0);
}

void MainWindow::on_pushButton_toggled(bool checked)
{
    //model_3d->setPause(checked);

    truck->moveTo(osg::Vec3d(20, 0, 0), 5);
    truck->aimTarget(osg::Vec3(-5,-5,1));

}
