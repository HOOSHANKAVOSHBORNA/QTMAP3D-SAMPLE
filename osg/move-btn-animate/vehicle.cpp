#include "vehicle.h"
#include <osg/MatrixTransform>
#include <list>
#include <QDebug>

void vehicle::movePack(osg::Vec3d desti, float speedd)
{
    carAnimPC = new osg::AnimationPathCallback;

    carAnimPC->setAnimationPath(run(desti,speedd));
    carPath->setLoopMode(osg::AnimationPath::NO_LOOPING);
    QuantomMt->setUpdateCallback(carAnimPC);
    wheelRot();


}

void vehicle::wheelRot()
{
    wheelAnimPcFr = new osg::AnimationPathCallback;
    wheelAnimPcFl = new osg::AnimationPathCallback;
    wheelAnimPcRr1 = new osg::AnimationPathCallback;
    wheelAnimPcRl1 = new osg::AnimationPathCallback;
    wheelAnimPcRr2 = new osg::AnimationPathCallback;
    wheelAnimPcRl2 = new osg::AnimationPathCallback;


    wheelAnimPcFr->setAnimationPath(wheelAnimationPath(wheelPosFr->getPosition(),0));

    wheelAnimPcFl->setAnimationPath(wheelAnimationPath(wheelPosFl->getPosition(),0));

    wheelAnimPcRr1->setAnimationPath(wheelAnimationPath(wheelPosRr1->getPosition(),0));

    wheelAnimPcRl1->setAnimationPath(wheelAnimationPath(wheelPosRl1->getPosition(),0));

    wheelAnimPcRr2->setAnimationPath(wheelAnimationPath(wheelPosRr2->getPosition(),0));

    wheelAnimPcRl2->setAnimationPath(wheelAnimationPath(wheelPosRl2->getPosition(),0));


    wheelPosFr->setUpdateCallback(wheelAnimPcFr);
    wheelPosFl->setUpdateCallback(wheelAnimPcFl);
    wheelPosRr1->setUpdateCallback(wheelAnimPcRr1);
    wheelPosRl1->setUpdateCallback(wheelAnimPcRl1);
    wheelPosRr2->setUpdateCallback(wheelAnimPcRr2);
    wheelPosRl2->setUpdateCallback(wheelAnimPcRl2);
}

vehicle::vehicle()
{
    car = osgDB::readRefNodeFile("../../../QTMAP3D-DATA/dataosgearth/model/truck/truck-body.osgt");
    wheel = osgDB::readRefNodeFile("../../../QTMAP3D-DATA/dataosgearth/model/truck/wheel.osgt");
    dualWheel = osgDB::readRefNodeFile("../../../QTMAP3D-DATA/dataosgearth/model/truck/wheel-dual.osgt");
    QuantomMt = new osg::MatrixTransform;

    carPath = new osg::AnimationPath;

    carPos = new osg::PositionAttitudeTransform();
    carPos->setScale(osg::Vec3(1,1,1));
    carPos->setPosition(osg::Vec3(0,0,0));
    carPos->addChild(car);

    wheelPosFr = new osg::PositionAttitudeTransform();
    wheelPosFr->addChild(wheel);
    wheelPosFr->setScale(osg::Vec3(2,2,2));
    wheelPosFr->setPosition(osg::Vec3(3.2f,-1.7f,0.8f));
    wheelPosFr->setAttitude(osg::Quat(osg::inDegrees(180.0),osg::X_AXIS));

    wheelPosFl = new osg::PositionAttitudeTransform();
    wheelPosFl->addChild(wheel);
    wheelPosFl->setScale(osg::Vec3(2,2,2));
    wheelPosFl->setPosition(osg::Vec3(3.2f,1.7f,0.8f));


    wheelPosRl1 = new osg::PositionAttitudeTransform();
    wheelPosRl1->addChild(dualWheel);
    wheelPosRl1->setScale(osg::Vec3(2,2,2));
    wheelPosRl1->setPosition(osg::Vec3(-3.7f,1.7f,0.8f));


    wheelPosRr1 = new osg::PositionAttitudeTransform();
    wheelPosRr1->addChild(dualWheel);
    wheelPosRr1->setScale(osg::Vec3(2,2,2));
    wheelPosRr1->setPosition(osg::Vec3(-3.7f,-1.7f,0.8f));
    wheelPosRr1->setAttitude(osg::Quat(osg::inDegrees(180.0),osg::X_AXIS));

    wheelPosRl2 = new osg::PositionAttitudeTransform();
    wheelPosRl2->addChild(dualWheel);
    wheelPosRl2->setScale(osg::Vec3(2,2,2));
    wheelPosRl2->setPosition(osg::Vec3(-5.7f,1.7f,0.8f));


    wheelPosRr2 = new osg::PositionAttitudeTransform();
    wheelPosRr2->addChild(dualWheel);
    wheelPosRr2->setScale(osg::Vec3(2,2,2));
    wheelPosRr2->setPosition(osg::Vec3(-5.7f,-1.7f,0.8f));
    wheelPosRr2->setAttitude(osg::Quat(osg::inDegrees(180.0),osg::X_AXIS));


    QuantomMt->addChild(carPos);
    QuantomMt->addChild(wheelPosFr);
    QuantomMt->addChild(wheelPosFl);
    QuantomMt->addChild(wheelPosRl1);
    QuantomMt->addChild(wheelPosRr1);
    QuantomMt->addChild(wheelPosRl2);
    QuantomMt->addChild(wheelPosRr2);

    this->addChild(QuantomMt);

}

osg::AnimationPath *vehicle::run(osg::Vec3d dest, float speed)
{
    time = (dest-carPos->getPosition()).length()/speed;
    osg::AnimationPath::ControlPoint cp0;
    osg::AnimationPath::ControlPoint cp1;

    cp0.setPosition(carPos->getPosition());
    cp1.setPosition(dest);

    cp0.setScale(carPos->getScale());
    cp0.setRotation(carPos->getAttitude());
    cp1.setScale(carPos->getScale());
    cp1.setRotation(carPos->getAttitude());

    carPath->insert(0.0,cp0);
    carPath->insert(time,cp1);

   qDebug() <<carPath->getPeriod();
    return carPath;

}

osg::AnimationPath *vehicle::wheelAnimationPath(osg::Vec3d wheelLoc, float RotDeg)
{
    osg::AnimationPath* wheelPath = new osg::AnimationPath;
    wheelPath->setLoopMode(osg::AnimationPath::LOOP);

    osg::AnimationPath::ControlPoint cp0;
    osg::AnimationPath::ControlPoint cp1;
    osg::AnimationPath::ControlPoint cp2;

    cp0.setRotation(osg::Quat(osg::inDegrees(0.0),osg::X_AXIS,osg::inDegrees(0.0),osg::Y_AXIS,osg::inDegrees(RotDeg),osg::Z_AXIS));
    cp1.setRotation(osg::Quat(osg::inDegrees(0.0),osg::X_AXIS,osg::inDegrees(180.0),osg::Y_AXIS,osg::inDegrees(RotDeg),osg::Z_AXIS));
    cp2.setRotation(osg::Quat(osg::inDegrees(0.0),osg::X_AXIS,osg::inDegrees(359.9),osg::Y_AXIS,osg::inDegrees(RotDeg),osg::Z_AXIS));

    cp0.setScale(osg::Vec3(2.f,2.f,2.f));
    cp0.setPosition(wheelLoc);
    cp1.setScale(osg::Vec3(2.f,2.f,2.f));
    cp1.setPosition(wheelLoc);
    cp2.setScale(osg::Vec3(2.f,2.f,2.f));
    cp2.setPosition(wheelLoc);

    wheelPath->insert(0,cp0);
    wheelPath->insert(0.5,cp1);
    wheelPath->insert(1,cp2);

return wheelPath;

}

void vehicle::setPause(bool pause)
{
    wheelAnimPcFr->setPause(pause);
    wheelAnimPcFl->setPause(pause);
    wheelAnimPcRl1->setPause(pause);
    wheelAnimPcRr1->setPause(pause);
    carAnimPC->setPause(pause);
}







