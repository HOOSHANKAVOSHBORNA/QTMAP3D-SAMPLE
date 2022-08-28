#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <osgQOpenGL/osgQOpenGLWidget>
#include <osgDB/ReadFile>
#include <osgGA/TerrainManipulator>
#include <osgViewer/Viewer>

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
    osgGA::TerrainManipulator* terrain = new osgGA::TerrainManipulator;
    widget->getOsgViewer()->setCameraManipulator(terrain);
    osg::ref_ptr<osg::Node> milad = osgDB::readRefNodeFile("/home/client112/Downloads/OBJ/Milad.osgb");
    widget->getOsgViewer()->setSceneData(milad);
}
