#ifndef ROCKET_H
#define ROCKET_H
#include <osgQOpenGL/osgQOpenGLWidget>
#include <osg/Group>
#include <osgDB/ReadFile>
#include <osg/PositionAttitudeTransform>

class FlyModel: public osg::PositionAttitudeTransform
{
public:
    FlyModel(osg::Group* parent, std::string flyModel);
    void flyTo(osg::Vec3d target, double speed);
    osg::AnimationPath* flyPath(osg::Vec3d& dest, double velocity);
private:
    osg::ref_ptr<osg::Node> _model;
    osg::AnimationPathCallback* _animPC;
    osg::AnimationPath* _animPath;
};

#endif // ROCKET_H
