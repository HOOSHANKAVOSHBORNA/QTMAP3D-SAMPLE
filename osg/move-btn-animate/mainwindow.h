#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <osgQOpenGL/osgQOpenGLWidget>
#include <osgSim/OverlayNode>
#include <osg/AnimationPath>
#include <osg/PositionAttitudeTransform>
#include "vehicle.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    osg::ref_ptr<vehicle> model_3d ;
    AnimtkUpdateCallback* animCall = new AnimtkUpdateCallback;
    ~MainWindow();

public slots:
    void initOpenglWidget();
private slots:
    void on_pushButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    osgQOpenGLWidget *widget;
};
#endif // MAINWINDOW_H
