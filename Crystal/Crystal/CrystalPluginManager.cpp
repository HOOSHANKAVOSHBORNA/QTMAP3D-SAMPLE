
#include <QDir>
#include <QPluginLoader>
#include <QCoreApplication>
#include <iostream>
#include <algorithm>
#include <iterator>

#include "CrystalPluginManager.h"
#include "CrystalPluginInterface.h"

CrystalPluginManager::CrystalPluginManager(QObject *parent) : QObject(parent)
{

}

void CrystalPluginManager::loadPlugins()
{

    QDir pluginsDir = QCoreApplication::applicationDirPath();
    pluginsDir.cd("../../CPTest/build");


    for (const QString& fileName : pluginsDir.entryList(QDir::Files)) {

        if ((fileName.split('.').back() == "so") || (fileName.split('.').back() == "dll"))
        {
            const QString filePath = pluginsDir.absoluteFilePath(fileName);
            QPluginLoader pluginLoader(filePath);

            QObject* instance = pluginLoader.instance();

            if (!instance)
                continue;

            CrystalPluginInterface *pluginInterface =
                    dynamic_cast<CrystalPluginInterface*>(instance);

            if (pluginInterface) {
                CrystalPluginInfo cpi;
                cpi.pInterface = pluginInterface;
                cpi.qmlDesc    = new CrystalPluginQMLDesc;
                cpi.sideItemIndex = -1;
                m_pluginsInfoList.push_back(std::move(cpi));
            }
        }
    }

}

void CrystalPluginManager::performPluginsInitQMLDesc(QQmlEngine *qmlEngine)
{
    for (const auto& item : m_pluginsInfoList) {
        item.pInterface->initializeQMLDesc(qmlEngine, item.qmlDesc);
    }
}


void CrystalPluginManager::performPluginsInit3D(CrystalMapController *mapController)
{
    for (const auto& item : m_pluginsInfoList) {
        item.pInterface->initialize3D(mapController);
    }
}

std::list<CrystalPluginInfo> &CrystalPluginManager::pluginsInfoList()
{
    return m_pluginsInfoList;
}

void CrystalPluginManager::onSideItemCreated(int index, QObject *pSideItem)
{
    const auto it = std::find_if(m_pluginsInfoList.begin(),
                 m_pluginsInfoList.end(),
                 [index](const CrystalPluginInfo& item){
        return (item.sideItemIndex == index);
    });

    if (it != m_pluginsInfoList.end()) {
        it->pInterface->onSideItemCreated(index, pSideItem);
    }
}
