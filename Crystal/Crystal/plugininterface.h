
#ifndef PluginInterface_H
#define PluginInterface_H


#include <QObject>
#include <QString>

class QQmlEngine;
class QQmlComponent;
class MapController;

namespace osgViewer {
    class Viewer;
};

struct ToolboxItem
{
    QString name;
    QString category;
    QString iconUrl;
    bool    checkable;
};

struct PluginQMLDesc
{
    bool           pluginHasSideItem = false;
    QString        sideItemMenuBarTitle;
    QString        sideItemMenuBarIconUrl;
    QString        sideItemUrl;

    QList<ToolboxItem> toolboxItemsList;
};

class PluginInterface
{
public:
    virtual ~PluginInterface() { }

    virtual bool initializeQMLDesc(QQmlEngine *engine, PluginQMLDesc *desc) = 0;
    virtual void onSideItemCreated(int index, QObject *sideItem) = 0;
    virtual void onToolboxItemClicked(QString name, QString category) = 0;

    virtual bool initialize3D(MapController *mapController) = 0;

};


QT_BEGIN_NAMESPACE
#define PluginInterface_iid "map3d.hooshan.ir"
Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)
QT_END_NAMESPACE

#endif // PluginInterface_H
