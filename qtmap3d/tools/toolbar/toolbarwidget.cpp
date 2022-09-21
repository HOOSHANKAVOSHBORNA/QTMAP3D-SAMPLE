#include "toolbarwidget.h"
#include <QDockWidget>
#include <QQmlEngine>
#include <QQuickWidget>
#include <QQmlContext>
ToolBarWidget::ToolBarWidget(QWidget *parent)
    : QWidget(parent)

{
    //ui->dockWidget->setFeatures(ui->dockWidget->features() & ~QDockWidget::DockWidgetClosable);
    //ui->dockWidget->setFeatures(ui->dockWidget->features() & ~QDockWidget::DockWidgetFloatable);

    mQQuickWidget = new QQuickWidget(QUrl(QStringLiteral("qrc:/toolbar/MenuSlide.qml")),this);
            mQQuickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
            mQQuickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
            mQQuickWidget->setClearColor(Qt::transparent);
            mQQuickWidget->resize(200, 450);
            mQQuickWidget->raise();

     mQQuickWidget->engine()->rootContext()->setContextProperty("NamePlugin",this);
     setMinimumSize(200,450);
     setMaximumSize(200,450);

}




void ToolBarWidget::addItem(QString name, QString icon, QString category)
{
    mNamePlugin = name;
    mIconPlugin = icon;
    mCategoryPlugin = category;
    emit itemAdded();
}

QVariant ToolBarWidget::getNamePlugin()
{
    return mNamePlugin;
}




QVariant ToolBarWidget::getIconPlugin()
{
   return mIconPlugin;
}

QVariant ToolBarWidget::getCategoryPlugin()
{
   return mCategoryPlugin;
}

void ToolBarWidget::onGetClicked(QString category, QString name)
{
    emit onClickedPlugin(category,name);
}
