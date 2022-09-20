#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setPlugin("data","qrc:/res/icons8-location-96.png","File");
    w.setPlugin("image","qrc:/res/icons8-location-96.png","Image");
    w.setPlugin("t","qrc:/res/icons8-location-96.png","Analyze");
    w.show();
    return a.exec();
}
