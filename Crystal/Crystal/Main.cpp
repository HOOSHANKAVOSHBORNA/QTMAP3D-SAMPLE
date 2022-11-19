
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include <QSurfaceFormat>
#include <iostream>
#include <QObject>

#include "CrystalApplication.h"


int main(int argc, char *argv[])
{
    CrystalApplication *const app = CrystalApplication::instance();

    return app->main(argc, argv);
}
