
#ifndef CRYSTALPLUGININTERFACE_H
#define CRYSTALPLUGININTERFACE_H


#include <QObject>
#include <QString>

class QQmlEngine;
class QQmlComponent;
class CrystalMapController;

namespace osgViewer {
    class Viewer;
};

struct CRYSTAL_PLUGIN_QML_INPUT_DESC
{
    bool           bPluginHasSideWidget = false;
    QQmlComponent *pSideWidgetComponent = nullptr;
    QString        strSideWidgetMenuBarTitle;
    QString        strSideWidgetMenuBarIconUrl;
};

struct CRYSTAL_PLUGIN_QML_OUTPUT_DESC
{
    QObject *pSideWidgetItem = nullptr;
};

class CrystalPluginInterface
{
public:
    CrystalPluginInterface();
    virtual ~CrystalPluginInterface() { }

public:
    virtual bool beginInitializeQML(QQmlEngine *engine, CRYSTAL_PLUGIN_QML_INPUT_DESC *pDesc) = 0;
    virtual bool endInitializeQML(CRYSTAL_PLUGIN_QML_OUTPUT_DESC *pDesc) = 0;
    virtual bool initialize3D(CrystalMapController *pMapController) = 0;

protected:

};

#endif // CRYSTALPLUGININTERFACE_H
