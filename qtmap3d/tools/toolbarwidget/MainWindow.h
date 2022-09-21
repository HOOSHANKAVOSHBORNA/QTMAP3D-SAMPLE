#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QQuickWidget>
//  library for display qml  in widget
#include <QWidget>
#include <QQmlContext>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{

    Q_OBJECT
public:

    MainWindow( QWidget *parent = nullptr);
    ~MainWindow();

    void setPlugin(QString name , QString icon , QString category);
    Q_INVOKABLE  QVariant getNamePlugin() ;
    Q_INVOKABLE  QVariant getIconPlugin() ;
    Q_INVOKABLE  QVariant getCategoryPlugin() ;




public slots:


    void onGetClicked(QString category ,QString name);

signals:

    void onClickedPlugin(QString category ,QString name);
    Q_INVOKABLE void onPin (bool t);
    Q_INVOKABLE void taggel ();

private:

    Ui::MainWindow *ui;
    QQuickWidget *mQQuickWidget;
    QDockWidget *mDock;
    QVariant    mNamePlugin ;
    QVariant    mIconPlugin ;
    QVariant    mCategoryPlugin;


};
#endif // MAINWINDOW_H
