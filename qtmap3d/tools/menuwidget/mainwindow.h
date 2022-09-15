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
private:
    Ui::MainWindow *ui;
    QQuickWidget *mQQuickWidget;
    QVariantList mListNamePlugin = {"image","Line","model","meature"};
    QVariantList mIconPlugin = {"qrc:/res/down-r.png","qrc:/res/icons8-chevron-right-96.png","qrc:/res/icons8-ruler-96.png","qrc:/res/icons8-pencil-96.png"};
    QVariantList mCategoryPlugin = {"Image","Trrain","Model","Meature"};


};
#endif // MAINWINDOW_H
