#ifndef CRYSTALWINDOW_H
#define CRYSTALWINDOW_H

#include <QQmlComponent>
#include "OsgQuickWindow.h"

class CrystalPluginInfo;

class CrystalWindow : public OsgQuickWindow
{
    Q_OBJECT


public:
    CrystalWindow(QWindow *parent = nullptr);
    ~CrystalWindow();


signals:
    void sideItemCreated(int index, QObject *pSideItem);

public slots:
    void initializePluginsUI(std::list<CrystalPluginInfo> pluginsInfoList);


protected:
    void keyPressEvent(QKeyEvent *event) override;


};

#endif // CRYSTALWINDOW_H
