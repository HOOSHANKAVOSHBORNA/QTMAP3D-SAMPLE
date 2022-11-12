
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include <QSurfaceFormat>
#include <iostream>
#include <QObject>

#include "OsgQuickWindow.h"
#include "CrystalWindow.h"


int main(int argc, char *argv[])
{

    qputenv("QSG_RENDER_LOOP", "basic"); // This line is very important and can not be removed

    QSurfaceFormat fmt;
    fmt.setVersion(2, 0);
    fmt.setProfile(QSurfaceFormat::OpenGLContextProfile::CompatibilityProfile);
    fmt.setSamples(2);
    QSurfaceFormat::setDefaultFormat(fmt);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<CrystalWindow>("Crystal", 1, 0, "CrystalWindow");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:///Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
