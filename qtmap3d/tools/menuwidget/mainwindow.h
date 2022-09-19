#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickWidget>
//  library for display qml  in widget
#include <QWidget>
#include <QQmlContext>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct ListPlugin {
    QString name;
    QString pathicon;
};

class MainWindow : public QMainWindow
{

    Q_OBJECT
public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setListPlugin(const QVariantList & v);
    Q_INVOKABLE  QVariantList getListNamePlugin() ;
    Q_INVOKABLE  QVariantList getListiconPlugin() ;
    Q_INVOKABLE  QVariantList getLisCategortPlugin() ;

public slots:
    void onGetClicked(QString category ,QString name);
signals:
    void onClickedPlugin(QString category ,QString name);
    Q_INVOKABLE void onPin (bool t);
private:
    Ui::MainWindow *ui;
    QQuickWidget *mQQuickWidget;
    QDockWidget *mDock;
    QVariantList mListNamePlugin ;
    QVariantList mIconPlugin ;
    QVariantList mCategoryPlugin;


};
#endif // MAINWINDOW_H
