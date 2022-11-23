#include "CPTestPlugin.h"

CPTestPlugin::CPTestPlugin()
{
    Q_INIT_RESOURCE(CPTestPlugin);
}

bool CPTestPlugin::initializeQMLDesc(QQmlEngine *engine, CrystalPluginQMLDesc *pDesc)
{
    pDesc->bPluginHasSideItem = true;
    pDesc->strSideItemMenuBarTitle = "Layers";
    pDesc->strSideItemMenuBarIconUrl = "qrc:///CPTestPlugin/Resources/Layers.png";
    pDesc->strSideItemUrl = "qrc:///CPTestPlugin/Layers.qml";

    return true;
}

void CPTestPlugin::onSideItemCreated(int index, QObject *pSideItem)
{

}

bool CPTestPlugin::initialize3D(CrystalMapController *pMapController)
{

    return true;
}
