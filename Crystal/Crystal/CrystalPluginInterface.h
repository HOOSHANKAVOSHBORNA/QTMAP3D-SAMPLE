
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

struct ToolboxItem
{
    QString name;
    QString category;
    QString iconUrl;
    bool    checkable;
};

struct CrystalPluginQMLDesc
{
    bool           bPluginHasSideItem = false;
    QString        strSideItemMenuBarTitle;
    QString        strSideItemMenuBarIconUrl;
    QString        strSideItemUrl;

    QList<ToolboxItem> toolboxItemsList;
};

class CrystalPluginInterface
{
public:
    virtual ~CrystalPluginInterface() { }

    virtual bool initializeQMLDesc(QQmlEngine *engine, CrystalPluginQMLDesc *pDesc) = 0;
    virtual void onSideItemCreated(int index, QObject *pSideItem) = 0;
    virtual void onToolboxItemClicked(QString name, QString category) = 0;

    virtual bool initialize3D(CrystalMapController *pMapController) = 0;

};


QT_BEGIN_NAMESPACE
#define CrystalPluginInterface_iid "ali.askari.crystal"
Q_DECLARE_INTERFACE(CrystalPluginInterface, CrystalPluginInterface_iid)
QT_END_NAMESPACE

#endif // CRYSTALPLUGININTERFACE_H
