
#include <iostream>
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

    pDesc->toolboxItemsList.push_back(ToolboxItem{"One", "Two"});

    return true;
}

void CPTestPlugin::onSideItemCreated(int index, QObject *pSideItem)
{

}

void CPTestPlugin::onToolboxItemClicked(QString name, QString category)
{
    std::cout << "Hello from plugin: " << name.toStdString() << " , " << category.toStdString() << std::endl;
}

bool CPTestPlugin::initialize3D(CrystalMapController *pMapController)
{

    return true;
}
