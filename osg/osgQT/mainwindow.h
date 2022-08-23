#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <osgSim/OverlayNode>
#include <QMainWindow>
//#include<osg/Node>
namespace osg {
class Node;
class Group;
}
class osgQOpenGLWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MyTransformCallback : public osg::NodeCallback
{
protected:
    osg::Vec3 move;
    public:
        MyTransformCallback(float x, float y, float z)
        {
            move = osg::Vec3(x,y,z);

        }

        virtual void operator() (osg::Node* node, osg::NodeVisitor* nv);

};



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    osg::Node* createBase(const osg::Vec3& center,float radius);
    osg::Node* createModel(const osg::Vec3& center, float radius);
    osg::ref_ptr<osg::Group> model_3d ;
    osg::ref_ptr<osg::Node> tower;
    osg::MatrixTransform* positioned;
    osg::ref_ptr<osg::Node> milad;


    ~MainWindow();
public slots:
    void initOpenglWidget();

private slots:
    void on_pushButton_pressed();

private:
    Ui::MainWindow *ui;
    osgQOpenGLWidget *widget;

};
#endif // MAINWINDOW_H
class moveNodeCallback : public osg::NodeCallback
{

};

