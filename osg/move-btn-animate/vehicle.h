#ifndef VEHICLE_H
#define VEHICLE_H

#include <osgQOpenGL/osgQOpenGLWidget>
#include <osgSim/OverlayNode>
#include <osg/AnimationPath>
#include <osg/PositionAttitudeTransform>
#include <osg/Group>
#include <osgDB/ReadFile>
#include <QObject>

class vehicle : public QObject , osg::Group
{
    Q_OBJECT
public:
    struct anim{
        double time;
        osg::Vec3 pos;
        osg::Quat rotate;
    };
    explicit vehicle(osg::ref_ptr<osg::Node> car, osg::ref_ptr<osg::Node> wheel);

    void setWehicleModel(std::string addr);
    void setWheelModel(std::string addr);
    osg::AnimationPath* carAnimationPath(QVector<anim> a);



private:
    osg::ref_ptr<osg::Node> car = osgDB::readRefNodeFile("/home/client111/Documents/project/fly-track/glider.osgt");
    osg::ref_ptr<osg::Node> wheel = osgDB::readRefNodeFile("/home/client111/Documents/project/glider/move-btn-animate/wheel.osgt");

signals:

public slots:
};

#endif // VEHICLE_H
