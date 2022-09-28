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

    model_3d = new vehicle;
    model_3d->movePack(osg::Vec3(0,1000,0),100);

    widget->getOsgViewer()->setCameraManipulator(g_ntm);
    g_ntm->setTrackNode(model_3d);
    widget->getOsgViewer()->setSceneData(model_3d);
    g_ntm->setDistance(50.0);
}

void MainWindow::on_pushButton_toggled(bool checked)
{
    model_3d->setPause(checked);
}
