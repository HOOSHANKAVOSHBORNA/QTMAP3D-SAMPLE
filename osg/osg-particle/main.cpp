
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
#include <osgParticle/SmokeTrailEffect>
#include <osgParticle/FireEffect>
#include <osgAnimation/Animation>
#include <osgAnimation/EaseMotion>
#include <osg/AnimationPath>
#include <osg/MatrixTransform>
#include <osgParticle/ExplosionEffect>
#include <osgParticle/ExplosionDebrisEffect>
#include <osg/Timer>

int main(int argc, char *argv[])
{
    osg::DisplaySettings::instance()->setNumMultiSamples(4);

    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
    viewer->setUpViewInWindow(100, 100, 800, 600);
    osg::Group *root = new osg::Group;




    osg::Geode *pSphereGeode = new osg::Geode;
    pSphereGeode->addDrawable(new osg::ShapeDrawable(new osg::Sphere()));

    osg::Group *pSphereGroup = new osg::Group;

    osg::MatrixTransform *pSphereTransform = new osg::MatrixTransform;
    pSphereTransform->setMatrix(osg::Matrix::translate(osg::Vec3f(0.0f, 0.0f, -5.0f)));

    osg::ShapeDrawable *pBox = new osg::ShapeDrawable(new osg::Box());

    osg::Geode *pBoxGeode = new osg::Geode;
    pBoxGeode->addDrawable(pBox);

    osg::AnimationPathCallback *pAPC = new osg::AnimationPathCallback;
    osg::AnimationPath *pAP = new osg::AnimationPath;


    for (int i = 0; i < 100; i++) {
        osg::AnimationPath::ControlPoint cp0;
        cp0.setPosition(osg::Vec3d(10*std::sin(2.0*osg::PI*i/100.0), 10*std::cos(2.0*osg::PI*i/100.0), -5.0));

        pAP->insert(i * (0.1), cp0);
    }


    osgParticle::FireEffect *fire = new osgParticle::FireEffect(osg::Vec3(0.0, 0.0, 0.0), 2.0f, 20.0f);
    osgParticle::SmokeTrailEffect *smoke = new osgParticle::SmokeTrailEffect(osg::Vec3(0.0, 0.0, 0.0), 1.0f, 1000.1f);
    osgParticle::ExplosionEffect *explosion = new osgParticle::ExplosionEffect(osg::Vec3(0.0, 0.0, 0.0), 2.0f, 1.0f);
    osgParticle::ExplosionDebrisEffect *debris = new osgParticle::ExplosionDebrisEffect(osg::Vec3(0.0, 0.0, 0.0), 2.0f, 1.0f);



    fire->setEmitterDuration(360000);
    smoke->setEmitterDuration(360000);

    //pSphereGroup->addChild(fire);
    //pSphereGroup->addChild(smoke);
    pSphereGroup->addChild(explosion);
    pSphereGroup->addChild(debris);

    fire->setUseLocalParticleSystem(false);
    smoke->setUseLocalParticleSystem(false);
    //explosion->setUseLocalParticleSystem(false);
    //debris->setUseLocalParticleSystem(false);

    //root->addChild(fire->getParticleSystem());
    //root->addChild(smoke->getParticleSystem());
    //root->addChild(explosion->getParticleSystem());
    //root->addChild(debris->getParticleSystem());


    pAPC->setAnimationPath(pAP);

    pSphereTransform->setUpdateCallback(pAPC);

    pSphereGroup->addChild(pSphereGeode);
    pSphereTransform->addChild(pSphereGroup);
    root->addChild(pBoxGeode);
    root->addChild(pSphereTransform);


    osgGA::TrackballManipulator *manip = new osgGA::TrackballManipulator;

    viewer->setCameraManipulator(manip);
    viewer->setSceneData(root);

    return viewer->run();
}
