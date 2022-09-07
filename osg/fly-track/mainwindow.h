#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <osgQOpenGL/osgQOpenGLWidget>
#include <osgSim/OverlayNode>
#include <osg/AnimationPath>
#include <osgGA/NodeTrackerManipulator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    osg::AnimationPath* CreateAnimate(osg::Vec3Array* keyPoint, float speed);
    osg::Node* CreateSphere(osg::Vec3 center, float r);
    osg::Node* CreateLine(osg::Vec3Array* vertex, float lineWidth);
    osg::Group* createMark(osg::Vec3Array* keyPoint);
    osg::Node* loadFly(osg::AnimationPath* animation);

public slots:
    void initOpenglWidget();
private:
    Ui::MainWindow *ui;
    osgQOpenGLWidget *widget;
    osgGA::NodeTrackerManipulator* g_ntm ;
};
#endif // MAINWINDOW_H
