#include "truck.h"


Truck::Truck()
{

    _truck     = osgDB::readRefNodeFile("../../../QTMAP3D-DATA/dataosgearth/model/truck/truck-body.osgt");
    _wheel     = osgDB::readRefNodeFile("../../../QTMAP3D-DATA/dataosgearth/model/truck/wheel.osgt");
    _dualWheel = osgDB::readRefNodeFile("../../../QTMAP3D-DATA/dataosgearth/model/truck/wheel-dual.osgt");
    _spiner    = osgDB::readRefNodeFile("../../../QTMAP3D-DATA/dataosgearth/model/truck/truck-spiner.osgt");
    _holder    = osgDB::readRefNodeFile("../../../QTMAP3D-DATA/dataosgearth/model/truck/truck-holder.osgt");


    _wholeTruckTransform = new osg::MatrixTransform();

    _truckTransform = new osg::MatrixTransform();
    _truckTransform->addChild(_truck);

    _holderTransform = new osg::MatrixTransform();
    _holderTransform->setMatrix(osg::Matrix::translate(osg::Vec3(-2, 0, 1.3)));
    _holderTransform->addChild(_holder);

    _spinerTransform = new osg::MatrixTransform();
    _spinerTransform->setMatrix(osg::Matrix::translate(osg::Vec3(-5, 0, 2.6)));
    _spinerTransform->addChild(_spiner);
    _spinerTransform->addChild(_holderTransform);

    _rightWheelRotation = new osg::MatrixTransform;
    _rightWheelRotation->addChild(_wheel);
    _leftWheelRotation = new osg::MatrixTransform;
    _leftWheelRotation->addChild(_wheel);

    _wheelTransformFr = new osg::MatrixTransform();
    _wheelTransformFr->addChild(_rightWheelRotation);
    _wheelTransformFr->setMatrix(osg::Matrix::rotate(osg::Quat(osg::inDegrees(180.0),osg::X_AXIS))*
                           osg::Matrix::scale(2,2,2)*
                           osg::Matrix::translate(osg::Vec3(3.2f,-1.7f,0.8f)));

    _wheelTransformFl = new osg::MatrixTransform();
    _wheelTransformFl->addChild(_leftWheelRotation);
    _wheelTransformFl->setMatrix(osg::Matrix::scale(2,2,2)*
                           osg::Matrix::translate(osg::Vec3(3.2f,1.7f,0.8f)));


    _rightDualWheelRotation = new osg::MatrixTransform;
    _rightDualWheelRotation->addChild(_dualWheel);
    _leftDualWheelRotation = new osg::MatrixTransform;
    _leftDualWheelRotation->addChild(_dualWheel);


    _wheelTransformRl1 = new osg::MatrixTransform();
    _wheelTransformRl1->addChild(_leftDualWheelRotation);
    _wheelTransformRl1->setMatrix(osg::Matrix::scale(2,2,2)*
                            osg::Matrix::translate(osg::Vec3(-3.7f,1.7f,0.8f)));

    _wheelTransformRr1 = new osg::MatrixTransform();
    _wheelTransformRr1->addChild(_rightDualWheelRotation);
    _wheelTransformRr1->setMatrix(osg::Matrix::scale(2,2,2)*
                            osg::Matrix::rotate(osg::Quat(osg::inDegrees(180.0),osg::X_AXIS))*
                            osg::Matrix::translate(osg::Vec3(-3.7f,-1.7f,0.8f)));

    _wheelTransformRl2 = new osg::MatrixTransform();
    _wheelTransformRl2->addChild(_leftDualWheelRotation);
    _wheelTransformRl2->setMatrix(osg::Matrix::scale(2,2,2)*
                            osg::Matrix::translate(osg::Vec3(-5.7f,1.7f,0.8f)));

    _wheelTransformRr2 = new osg::MatrixTransform();
    _wheelTransformRr2->addChild(_rightDualWheelRotation);
    _wheelTransformRr2->setMatrix(osg::Matrix::scale(2,2,2)*
                            osg::Matrix::rotate(osg::Quat(osg::inDegrees(180.0),osg::X_AXIS))*
                            osg::Matrix::translate(osg::Vec3(-5.7f,-1.7f,0.8f)));

    _wholeTruckTransform->addChild(_truckTransform);
    _wholeTruckTransform->addChild(_spinerTransform);
    _wholeTruckTransform->addChild(_wheelTransformFr);
    _wholeTruckTransform->addChild(_wheelTransformFl);
    _wholeTruckTransform->addChild(_wheelTransformRl1);
    _wholeTruckTransform->addChild(_wheelTransformRr1);
    _wholeTruckTransform->addChild(_wheelTransformRl2);
    _wholeTruckTransform->addChild(_wheelTransformRr2);


    this->addChild(_wholeTruckTransform);


    _wholeTruckUpdateCallback = new TruckUpdateCallback;
    _leftWheelUpdateCallback      = new TruckUpdateCallback;
    _rightWheelUpdateCallback      = new TruckUpdateCallback;
    _spinerUpdateCallback     = new TruckUpdateCallback;
    _holderUpdateCallback     = new TruckUpdateCallback;


    _wholeTruckAnimPath = new osg::AnimationPath;
    _leftWheelAnimPath  = new osg::AnimationPath;
    _rightWheelAnimPath = new osg::AnimationPath;
    _spinerAnimPath     = new osg::AnimationPath;
    _holderAnimPath     = new osg::AnimationPath;

    _wholeTruckUpdateCallback->setAnimationPath(_wholeTruckAnimPath);
    _leftWheelUpdateCallback->setAnimationPath(_leftWheelAnimPath);
    _rightWheelUpdateCallback->setAnimationPath(_rightWheelAnimPath);
    _spinerUpdateCallback->setAnimationPath(_spinerAnimPath);
    _holderUpdateCallback->setAnimationPath(_holderAnimPath);

    _wholeTruckAnimPath->setLoopMode(osg::AnimationPath::LoopMode::NO_LOOPING);
    _leftWheelAnimPath->setLoopMode(osg::AnimationPath::LoopMode::LOOP);
    _rightWheelAnimPath->setLoopMode(osg::AnimationPath::LoopMode::LOOP);
    _spinerAnimPath->setLoopMode(osg::AnimationPath::LoopMode::NO_LOOPING);
    _holderAnimPath->setLoopMode(osg::AnimationPath::LoopMode::NO_LOOPING);

    _wholeTruckTransform->setUpdateCallback(_wholeTruckUpdateCallback);
    _rightWheelRotation->setUpdateCallback(_rightWheelUpdateCallback);
    _leftWheelRotation->setUpdateCallback(_leftWheelUpdateCallback);
    _rightDualWheelRotation->setUpdateCallback(_rightWheelUpdateCallback);
    _leftDualWheelRotation->setUpdateCallback(_leftWheelUpdateCallback);
    _spinerTransform->setUpdateCallback(_spinerUpdateCallback);
    _holderTransform->setUpdateCallback(_holderUpdateCallback);

}

void Truck::moveTo(osg::Vec3d desti, float speed)
{
    _wholeTruckUpdateCallback->stop();
    _leftWheelUpdateCallback->stop();
    _rightWheelUpdateCallback->stop();

    _wholeTruckAnimPath->clear();
    _leftWheelAnimPath->clear();
    _rightWheelAnimPath->clear();

    osg::AnimationPath::ControlPoint truck_cp0;
    osg::AnimationPath::ControlPoint truck_cp1;

    osg::AnimationPath::ControlPoint r_wheel_cp0;
    osg::AnimationPath::ControlPoint r_wheel_cp1;
    osg::AnimationPath::ControlPoint r_wheel_cp2;

    osg::AnimationPath::ControlPoint l_wheel_cp0;
    osg::AnimationPath::ControlPoint l_wheel_cp1;
    osg::AnimationPath::ControlPoint l_wheel_cp2;

    osg::Vec3d currentTruckPos = _wholeTruckTransform->getMatrix().getTrans();
    osg::Vec3d axis = desti - currentTruckPos;

    osg::Quat rotate;
    rotate.makeRotate(osg::Vec3d(osg::X_AXIS), axis);
    const float time = static_cast<float>(axis.length())/speed;


    truck_cp0.setPosition(currentTruckPos);
    truck_cp1.setPosition(desti);

    truck_cp0.setScale(_wholeTruckTransform->getMatrix().getScale());
    truck_cp1.setScale(_wholeTruckTransform->getMatrix().getScale());

    truck_cp0.setRotation(rotate);
    truck_cp1.setRotation(rotate);

    _wholeTruckAnimPath->insert(0.0 ,truck_cp0);
    _wholeTruckAnimPath->insert(time,truck_cp1);



    r_wheel_cp0.setRotation(osg::Quat());
    r_wheel_cp1.setRotation(osg::Quat(osg::inDegrees(-180.0), osg::Y_AXIS));
    r_wheel_cp2.setRotation(osg::Quat(osg::inDegrees(-359.99), osg::Y_AXIS));

    _rightWheelAnimPath->insert(0.0, r_wheel_cp0);
    _rightWheelAnimPath->insert(1, r_wheel_cp1);
    _rightWheelAnimPath->insert(2, r_wheel_cp2);



    l_wheel_cp0.setRotation(osg::Quat());
    l_wheel_cp1.setRotation(osg::Quat(osg::inDegrees(180.0), osg::Y_AXIS));
    l_wheel_cp2.setRotation(osg::Quat(osg::inDegrees(359.99), osg::Y_AXIS));

    _leftWheelAnimPath->insert(0.0, l_wheel_cp0);
    _leftWheelAnimPath->insert(1, l_wheel_cp1);
    _leftWheelAnimPath->insert(2, l_wheel_cp2);


    _wholeTruckUpdateCallback->start();
    _rightWheelUpdateCallback->start();
    _leftWheelUpdateCallback->start();


    QObject::connect(_wholeTruckUpdateCallback,
                     &TruckUpdateCallback::finished,
                     _leftWheelUpdateCallback,
                     &TruckUpdateCallback::stop);

    QObject::connect(_wholeTruckUpdateCallback,
                     &TruckUpdateCallback::finished,
                     _rightWheelUpdateCallback,
                     &TruckUpdateCallback::stop);
}

void Truck::aimTarget(osg::Vec3d target)
{

    _spinerUpdateCallback->stop();
    _holderUpdateCallback->stop();

    _spinerAnimPath->clear();
    _holderAnimPath->clear();

    osg::AnimationPath::ControlPoint spiner_cp0;
    osg::AnimationPath::ControlPoint spiner_cp1;
    osg::AnimationPath::ControlPoint holder_cp0;
    osg::AnimationPath::ControlPoint holder_cp1;

    osg::Vec3d currentSpinPos = _spinerTransform->getMatrix().getTrans();
    osg::Vec3d axis = target - currentSpinPos;

    osg::Quat rotate;
    axis.z() = 0;
    rotate.makeRotate(osg::Vec3d(osg::X_AXIS), axis);


    spiner_cp0.setPosition(_spinerTransform->getMatrix().getTrans());
    spiner_cp1.setPosition(_spinerTransform->getMatrix().getTrans());

    spiner_cp0.setRotation(_spinerTransform->getMatrix().getRotate());
    spiner_cp1.setRotation(rotate);
//    curSpinRotate = rotate;

    _spinerAnimPath->insert(0.0, spiner_cp0);
    _spinerAnimPath->insert(3, spiner_cp1);

    osg::Vec3d currentHoldPos = _holderTransform->getMatrix().getTrans();
    osg::Vec3d axisH = target - currentHoldPos;



    osg::Quat rotateH;
    axisH.x() = std::sqrt(std::pow(axisH.x(), 2.0) + std::pow(axisH.y(),2.0));
    axisH.y() = 0;
    rotateH.makeRotate(osg::Vec3d(osg::X_AXIS), axisH);


    holder_cp0.setPosition(_holderTransform->getMatrix().getTrans());
    holder_cp1.setPosition(_holderTransform->getMatrix().getTrans());

    holder_cp0.setRotation(_holderTransform->getMatrix().getRotate());
    holder_cp1.setRotation(rotateH);
//    curHoldRotate = rotateH;

    _holderAnimPath->insert(0.0, holder_cp0);
    _holderAnimPath->insert(3, holder_cp1);

    _spinerUpdateCallback->start();
    _holderUpdateCallback->start();
}












TruckUpdateCallback::TruckUpdateCallback()
{
}

void TruckUpdateCallback::operator()(osg::Node *node, osg::NodeVisitor *nv)
{
    auto _path = getAnimationPath();
    if (nv->getVisitorType() == osg::NodeVisitor::UPDATE_VISITOR &&
            nv->getFrameStamp() &&
            nv->getFrameStamp()->getFrameNumber() != _lastUpdate) {

        if (_playing && _path) {

            _currentTime = osg::Timer::instance()->tick();
            const double t = osg::Timer::instance()->delta_s(_startTime, _currentTime);

            if (_path->getLoopMode() == osg::AnimationPath::LoopMode::NO_LOOPING) {
                if (t >= _path->getPeriod()) {
                    stop();
                    //return;
                }
            }

//            osg::AnimationPath::ControlPoint cp;
//            _path->getInterpolatedControlPoint(t, cp);
//            osg::MatrixTransform *mt = dynamic_cast<osg::MatrixTransform*>(node);
//            if (!mt)
//                return;
//            osg::Matrix m;
//            cp.getMatrix(m);
//            mt->setMatrix(m);
        }
    }
//    traverse(node,nv);
    AnimationPathCallback::operator()(node,nv);
}

void TruckUpdateCallback::start()
{
    if (_playing == false) {
        setPause(false);
        _startTime = osg::Timer::instance()->tick();
        _currentTime = _startTime;
        _playing = true;
        AnimationPathCallback::reset();


        emit started();
    }
}

void TruckUpdateCallback::stop()
{
    if (_playing == true) {
        _currentTime = _startTime;
        _playing = false;
        setPause(true);

        emit finished();
    }
}
