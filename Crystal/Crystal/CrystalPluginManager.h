#ifndef CRYSTALPLUGINMANAGER_H
#define CRYSTALPLUGINMANAGER_H

#include <QObject>
#include <QQmlEngine>

class CrystalMapController;

class CrystalPluginManager : public QObject
{
    Q_OBJECT

public:
    explicit CrystalPluginManager(QObject *parent = nullptr);

signals:

public slots:
    void loadPlugins();
    void beginPluginsInitQML(QQmlEngine *qmlEngine);
    void endPluginsInitQML();
    void performPluginsInit3D(CrystalMapController *mapController);

};

#endif // CRYSTALPLUGINMANAGER_H
