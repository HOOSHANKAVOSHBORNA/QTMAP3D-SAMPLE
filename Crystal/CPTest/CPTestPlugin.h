
#ifndef CPTESTPLUGIN_H
#define CPTESTPLUGIN_H

#include "CrystalPluginInterface.h"

class CPTestPlugin : public QObject, public CrystalPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID CrystalPluginInterface_iid FILE "CPTestPlugin.json")
    Q_INTERFACES(CrystalPluginInterface)

public:
    explicit CPTestPlugin();

public:
    virtual bool initializeQMLDesc(QQmlEngine *engine, CrystalPluginQMLDesc *pDesc) override;
    virtual void onSideItemCreated(int index, QObject *pSideItem) override;
    virtual void onToolboxItemClicked(QString name, QString category) override;

    virtual bool initialize3D(CrystalMapController *pMapController) override;
};

#endif // CPTESTPLUGIN_H
