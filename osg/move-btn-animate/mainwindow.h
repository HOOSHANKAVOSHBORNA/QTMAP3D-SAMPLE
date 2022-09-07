#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <osgQOpenGL/osgQOpenGLWidget>
#include <osgSim/OverlayNode>
#include <osg/AnimationPath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    osg::ref_ptr<osg::Group> model_3d ;
    osg::Node* createBase(const osg::Vec3& center,float radius);
    osg::MatrixTransform* locationTree;
    osg::MatrixTransform* locationCar;
    osg::AnimationPath* carAnimationPath();
    ~MainWindow();

public slots:
    void initOpenglWidget();
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    osgQOpenGLWidget *widget;
};
#endif // MAINWINDOW_H
