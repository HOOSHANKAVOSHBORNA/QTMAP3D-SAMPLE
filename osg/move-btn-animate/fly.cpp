#include "fly.h"
#include <osgParticle/SmokeEffect>
#include <osgParticle/FireEffect>
#include <osgAnimation/Animation>

FlyModel::FlyModel(osg::Group *parent, std::string flyModel)
{
    _model = osgDB::readRefNodeFile(flyModel);
    this->addChild(_model);

    osgParticle::FireEffect *fire = new osgParticle::FireEffect(osg::Vec3(-7.0, 0.0, 0.0), 1.0f, 2.0f);
    fire->setParticleDuration(6);
    fire->setEmitterDuration(10.0);
    fire->setUseLocalParticleSystem(false);
    fire->setTextureFileName("/home/client111/Downloads/fire.png");
    this->addChild(fire);
    osgAnimation::Vec3CubicBezierSampler sampler;
    sampler.getOrCreateKeyframeContainer();

    if (parent)
        parent->addChild(fire->getParticleSystem());
}

void FlyModel::flyTo(osg::Vec3d target, double speed)
{
        _animPC = new osg::AnimationPathCallback;
        //_animPC->setPivotPoint(osg::Vec3d(-5,0,0));
        _animPC->setAnimationPath(flyPath(target, speed));
        this->setUpdateCallback(_animPC);
}

osg::AnimationPath *FlyModel::flyPath(osg::Vec3d &dest, double velocity)
{
       osg::AnimationPath* path = new osg::AnimationPath;

            osg::Vec3d currentPos = this->getPosition();
            osg::Quat rotate;
            osg::Vec3f axis = dest - currentPos;
            rotate.makeRotate(osg::Y_AXIS, axis);

            osg::AnimationPath::ControlPoint cp0;
            osg::AnimationPath::ControlPoint cp1;

            cp0.setPosition(this->getPosition());
            cp1.setPosition(dest);

            cp0.setScale(this->getScale());
            cp1.setScale(this->getScale());

            cp0.setRotation(this->getAttitude());
            cp1.setRotation(rotate);

            const double time = static_cast<double>(axis.length())/velocity;

            path->insert(0, cp0);
            path->insert(time, cp1);

            path->setLoopMode(osg::AnimationPath::NO_LOOPING);

        return path;
}
