#ifndef TRUCK_H
#define TRUCK_H

#include <QObject>
#include <osgQOpenGL/osgQOpenGLWidget>
#include <osgSim/OverlayNode>
#include <osg/AnimationPath>
#include <osg/PositionAttitudeTransform>
#include <osg/Group>
#include <osg/AnimationPath>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <QObject>
#include <QDebug>
#include <osgAnimation/Sampler>
#include <QTextStream>


class TruckUpdateCallback;

class Truck: public osg::Group
{
public:
    Truck();
    void moveTo(osg::Vec3d desti, float speed);
    void aimTarget(osg::Vec3d target);
private:
    osg::MatrixTransform* _wholeTruckTransform;
    osg::MatrixTransform* _truckTransform;
    osg::MatrixTransform* _spinerTransform;
    osg::MatrixTransform* _holderTransform;
    osg::MatrixTransform* _wheelTransformFr;
    osg::MatrixTransform* _wheelTransformFl;
    osg::MatrixTransform* _wheelTransformRr1;
    osg::MatrixTransform* _wheelTransformRl1;
    osg::MatrixTransform* _wheelTransformRr2;
    osg::MatrixTransform* _wheelTransformRl2;


    osg::ref_ptr<osg::MatrixTransform> _leftWheelRotation;
    osg::ref_ptr<osg::MatrixTransform> _rightWheelRotation;
    osg::ref_ptr<osg::MatrixTransform> _leftDualWheelRotation;
    osg::ref_ptr<osg::MatrixTransform> _rightDualWheelRotation;

    osg::ref_ptr<osg::Node> _truck;
    osg::ref_ptr<osg::Node> _wheel;
    osg::ref_ptr<osg::Node> _dualWheel;
    osg::ref_ptr<osg::Node> _spiner;
    osg::ref_ptr<osg::Node> _holder;

    TruckUpdateCallback *_wholeTruckUpdateCallback = nullptr;
    TruckUpdateCallback *_leftWheelUpdateCallback      = nullptr;
    TruckUpdateCallback *_rightWheelUpdateCallback      = nullptr;
    TruckUpdateCallback *_spinerUpdateCallback     = nullptr;
    TruckUpdateCallback *_holderUpdateCallback     = nullptr;

    osg::AnimationPath *_wholeTruckAnimPath = nullptr;
    osg::AnimationPath *_rightWheelAnimPath      = nullptr;
    osg::AnimationPath *_leftWheelAnimPath      = nullptr;
    osg::AnimationPath *_spinerAnimPath     = nullptr;
    osg::AnimationPath *_holderAnimPath     = nullptr;

    osg::Quat curSpinRotate {osg::Quat()};
    osg::Quat curHoldRotate {osg::Quat()};

};

class TruckUpdateCallback : public QObject, public osg::AnimationPathCallback{

    Q_OBJECT
public:
    TruckUpdateCallback();

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv) override;

public slots:
    void start();
    void stop();

signals:
    void started();
    void finished();

private:
    osg::Timer_t        _startTime   = 0;
    osg::Timer_t        _currentTime = 0;
    unsigned int        _lastUpdate  = 0;
    bool                _playing     = false;

};



#endif // TRUCK_H
