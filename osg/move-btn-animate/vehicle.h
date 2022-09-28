#ifndef VEHICLE_H
#define VEHICLE_H

#include <osgQOpenGL/osgQOpenGLWidget>
#include <osgSim/OverlayNode>
#include <osg/AnimationPath>
#include <osg/PositionAttitudeTransform>
#include <osg/Group>
#include <osgDB/ReadFile>
#include <QObject>


class vehicle : public osg::Group
{

public:
    void movePack(osg::Vec3d desti, float speedd);
    void wheelRot();
    osg::AnimationPath* run(osg::Vec3d dest, float speed);
    osg::AnimationPath* wheelAnimationPath(osg::Vec3d wheelLoc, float RotDeg);
    void setPause(bool pause);


//    struct anim{
//        double time;
//        osg::Vec3 pos;
//        osg::Quat rotate;
//    };
    explicit vehicle();

//    void setWehicleModel(std::string addr);
//    void setWheelModel(std::string addr);
//    osg::AnimationPath* carAnimationPath(QVector<anim> a);



private:
    float stop;
    float time;
    osg::ref_ptr<osg::Node> car;
    osg::ref_ptr<osg::Node> wheel ;
    osg::ref_ptr<osg::Node> dualWheel ;
    osg::MatrixTransform* QuantomMt;
    osg::PositionAttitudeTransform* carPos;
    osg::PositionAttitudeTransform* wheelPosFr;
    osg::PositionAttitudeTransform* wheelPosFl;
    osg::PositionAttitudeTransform* wheelPosRr1;
    osg::PositionAttitudeTransform* wheelPosRl1;
    osg::PositionAttitudeTransform* wheelPosRr2;
    osg::PositionAttitudeTransform* wheelPosRl2;




    osg::AnimationPathCallback* carAnimPC;
    osg::AnimationPath* carPath;


    osg::AnimationPathCallback* wheelAnimPcFr;
    osg::AnimationPathCallback* wheelAnimPcFl;
    osg::AnimationPathCallback* wheelAnimPcRr1;
    osg::AnimationPathCallback* wheelAnimPcRl1;
    osg::AnimationPathCallback* wheelAnimPcRr2;
    osg::AnimationPathCallback* wheelAnimPcRl2;

signals:

public slots:
};

#endif // VEHICLE_H
