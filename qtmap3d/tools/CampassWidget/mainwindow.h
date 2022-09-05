#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickView>
#include <QQuickWidget>
//  library for display qml  in widget
#include <QWidget>
#include <QQmlContext>
#include <QQmlEngine>
#include "getdata.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QQuickWidget *mQQuickWidget;
        // class widget for display qml
    QWidget *m_qmlwidget;
    GetData *m_data;
};
#endif // MAINWINDOW_H
