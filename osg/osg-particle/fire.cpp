
#include <iostream>
#include <string>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>
#include <osg/ShapeDrawable>
#include <osgViewer/Viewer>
#include <osg/ArgumentParser>
#include <osgGA/TrackballManipulator>
#include <osgGA/GUIEventHandler>
#include <osgParticle/SmokeEffect>
#include <osgParticle/FireEffect>
#include <osgAnimation/Animation>
#include <osgAnimation/EaseMotion>
#include <osg/AnimationPath>

int main(int argc, char *argv[])
{
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
    viewer->setUpViewInWindow(100, 100, 800, 600);
    osg::Group *root = new osg::Group;

    osgParticle::FireEffect *fire = new osgParticle::FireEffect(osg::Vec3(), 10.0f, 2.0f);
    fire->setParticleDuration(1.5);
    fire->setEmitterDuration(10.0);
    //fire->setUseLocalParticleSystem(false);
    //fire->setTextureFileName("/home/client112/Desktop/fire.png");
    root->addChild(fire);

    osgAnimation::Vec3CubicBezierSampler sampler;
    sampler.getOrCreateKeyframeContainer();

    viewer->setCameraManipulator(new osgGA::TrackballManipulator);
    viewer->setSceneData(root);

    return viewer->run();
}
