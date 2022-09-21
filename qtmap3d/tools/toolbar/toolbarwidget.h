#ifndef TOOLBARWIDGET_H
#define TOOLBARWIDGET_H

//#include <QWidget>
#include <QDockWidget>
//#include <QQuickWidget>
//  library for display qml  in widget
#include <QWidget>
#include <QVariant>
//#include <QQmlContext>



class QQuickWidget;

class ToolBarWidget : public QWidget
{
    Q_OBJECT

public:
    ToolBarWidget(QWidget *parent = nullptr);
    void addItem(QString name , QString icon , QString category);
    Q_INVOKABLE  QVariant getNamePlugin() ;
    Q_INVOKABLE  QVariant getIconPlugin() ;
    Q_INVOKABLE  QVariant getCategoryPlugin() ;
public slots:


    void onGetClicked(QString category ,QString name);

signals:

    void onClickedPlugin(QString category ,QString name);
    Q_INVOKABLE void onPin (bool t);
    Q_INVOKABLE void itemAdded ();

private:
    QQuickWidget *mQQuickWidget;
    QVariant    mNamePlugin ;
    QVariant    mIconPlugin ;
    QVariant    mCategoryPlugin;

};
#endif // TOOLBARWIDGET_H
