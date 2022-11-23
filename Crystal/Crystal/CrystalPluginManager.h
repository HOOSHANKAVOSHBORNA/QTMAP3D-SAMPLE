
#ifndef CRYSTALPLUGINMANAGER_H
#define CRYSTALPLUGINMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include <list>
#include <utility>
#include <tuple>

#include "CrystalPluginInterface.h"

class CrystalMapController;
class CrystalPluginInterface;

struct CrystalPluginInfo
{
    CrystalPluginInterface *pInterface = nullptr;
    CrystalPluginQMLDesc   *qmlDesc    = nullptr;
    int                     sideItemIndex      = -1;

};

class CrystalPluginManager : public QObject
{
    Q_OBJECT

public:
    explicit CrystalPluginManager(QObject *parent = nullptr);

signals:

public:
    void loadPlugins();
    void performPluginsInitQMLDesc(QQmlEngine *qmlEngine);
    void performPluginsInit3D(CrystalMapController *mapController);

    std::list<CrystalPluginInfo>& pluginsInfoList();

public slots:
    void onSideItemCreated(int index, QObject *pSideItem);

private:
    std::list<CrystalPluginInfo> m_pluginsInfoList;
};

#endif // CRYSTALPLUGINMANAGER_H
