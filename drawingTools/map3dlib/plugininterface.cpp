#include "map3dwidget.h"
#include "plugininterface.h"
#include "toolbarwidget.h"
#include "websocketclient.h"

#include <QVBoxLayout>

PluginInterface::PluginInterface(QObject *parent)
    : QObject(parent)
{
}

void PluginInterface::setMainWindow(Map3dlib *mainWindow)
{
    mMainWindow = mainWindow;
}

void PluginInterface::setMap3dWidget(Map3dWidget *value)
{
    mMap3dWidget = value;
}

void PluginInterface::setToolBar(ToolBarWidget *toolBar)
{
    mToolBar = toolBar;
}

void PluginInterface::setName(const QString &name)
{
    mName = name;
}

void PluginInterface::createWebSocket()
{
    if(!mWebSocket)
        mWebSocket = new WebSocketClient(mName, this);
}
