
#include <iostream>
#include "CPTestPlugin.h"

CPTestPlugin::CPTestPlugin()
{
    Q_INIT_RESOURCE(CPTestPlugin);
}

bool CPTestPlugin::initializeQMLDesc(QQmlEngine *engine, PluginQMLDesc *pDesc)
{
    pDesc->pluginHasSideItem = true;
    pDesc->sideItemMenuBarTitle = "Layers";
    pDesc->sideItemMenuBarIconUrl = "qrc:///CPTestPlugin/Resources/Layers.png";
    pDesc->sideItemUrl = "qrc:///CPTestPlugin/Layers.qml";

    pDesc->toolboxItemsList.push_back(ToolboxItem{"One", "Two", "", true});

    return true;
}

void CPTestPlugin::onSideItemCreated(int index, QObject *pSideItem)
{

}

void CPTestPlugin::onToolboxItemClicked(QString name, QString category)
{
    std::cout << "Hello from plugin: " << name.toStdString() << " , " << category.toStdString() << std::endl;
}

bool CPTestPlugin::initialize3D(MapController *pMapController)
{

    return true;
}
