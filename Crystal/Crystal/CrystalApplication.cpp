
#include <QSurfaceFormat>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QPluginLoader>
#include <QDir>

#include "CrystalApplication.h"
#include "CrystalWindow.h"

CrystalApplication::CrystalApplication() :
    m_pPluginManager(new CrystalPluginManager)
{
}

CrystalApplication *CrystalApplication::instance()
{
    static CrystalApplication app;
    return &app;
}

int CrystalApplication::main(int argc, char **argv)
{
    qputenv("QSG_RENDER_LOOP", "basic"); // This line is very important and can not be removed

    initializeSurfaceFormat();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);


    registerTypes();
    initializeQmlEngine();

    m_pPluginManager->loadPlugins();
    QObject::connect(this, &CrystalApplication::mainWindowCreated,
                     this, &CrystalApplication::onMainWindowCreated,
                     Qt::DirectConnection);

    createMainWindow();

    return app.exec();
}

void CrystalApplication::initializeSurfaceFormat()
{
    QSurfaceFormat fmt;
    fmt.setVersion(2, 0);
    fmt.setProfile(QSurfaceFormat::OpenGLContextProfile::CompatibilityProfile);
    fmt.setSamples(4);
    QSurfaceFormat::setDefaultFormat(fmt);
}

void CrystalApplication::registerTypes()
{
    qmlRegisterType<CrystalWindow>("Crystal", 1, 0, "CrystalWindow");
}

void CrystalApplication::initializeQmlEngine()
{
    m_pQmlEngine = new QQmlApplicationEngine();
}


void CrystalApplication::createMainWindow()
{
    QObject::connect(m_pQmlEngine, &QQmlApplicationEngine::objectCreated,
                     this, &CrystalApplication::onQmlObjectCreated,
                     Qt::DirectConnection);
    m_pQmlEngine->load(m_mainUrl);
}

void CrystalApplication::onQmlObjectCreated(QObject *obj, const QUrl &objUrl)
{

    if (!obj && m_mainUrl == objUrl)
        QCoreApplication::exit(-1);
    CrystalWindow *wnd = qobject_cast<CrystalWindow*>(obj);
    if (wnd && !m_pMainWindow) {
        m_pMainWindow = wnd;
        emit mainWindowCreated();
    }

}

void CrystalApplication::onMainWindowCreated()
{
    m_pPluginManager->beginPluginsInitQML(m_pQmlEngine);

    m_pPluginManager->endPluginsInitQML();
    QObject::connect(m_pMainWindow, &CrystalWindow::osgInitialized,
                     this, &CrystalApplication::initialize3D,
                     Qt::DirectConnection);
}

void CrystalApplication::initialize3D()
{
    m_pPluginManager->performPluginsInit3D(m_pMainWindow->mapController());
}

