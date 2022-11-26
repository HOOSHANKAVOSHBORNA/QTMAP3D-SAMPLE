#ifndef CRYSTALAPPLICATION_H
#define CRYSTALAPPLICATION_H

#include <QObject>
#include <QUrl>
#include <list>

#include "CrystalPluginInterface.h"
#include "CrystalPluginManager.h"


class CrystalWindow;
class CRYSTAL_PLUGIN_QML_INPUT_DESC;
class QQmlApplicationEngine;

class CrystalApplication : public QObject
{
    Q_OBJECT

private:
    explicit CrystalApplication();

public:
    static CrystalApplication *instance();
    int main(int argc, char **argv);

signals:
    void  mainWindowCreated();


private:
    void initializeSurfaceFormat();
    void registerTypes();
    void initializeQmlEngine();
    void createMainWindow();

private slots:
    void onQmlObjectCreated(QObject *obj, const QUrl &objUrl);
    void onMainWindowCreated();
    void initialize3D();

signals:

private:
    QQmlApplicationEngine *m_pQmlEngine = nullptr;
    const QUrl m_mainUrl{QStringLiteral("qrc:///Main.qml")};
    CrystalWindow *m_pMainWindow = nullptr;

    CrystalPluginManager *m_pPluginManager = nullptr;
};

#endif // CRYSTALAPPLICATION_H
