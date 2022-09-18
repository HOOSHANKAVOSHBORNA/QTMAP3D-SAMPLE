#include "vehicle.h"

vehicle::vehicle(osg::ref_ptr<osg::Node> car, osg::ref_ptr<osg::Node> wheel)
{

}

void vehicle::setWehicleModel(std::string addr)
{
    car = osgDB::readRefNodeFile(addr);


}

void vehicle::setWheelModel(std::string addr)
{
    wheel = osgDB::readRefNodeFile(addr);
}

osg::AnimationPath *vehicle::carAnimationPath(QVector<vehicle::anim> a)
{
    osg::AnimationPath* path = new osg::AnimationPath();
    path->setLoopMode(osg::AnimationPath::LOOP);

    for(int i=0 ; i<a.length();i++){
        path->insert(a[i].time, osg::AnimationPath::ControlPoint(a[i].pos,
        osg::Quat(osg::inDegrees(0.0),osg::Z_AXIS)));
    }
}



