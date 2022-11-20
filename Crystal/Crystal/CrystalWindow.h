#ifndef CRYSTALWINDOW_H
#define CRYSTALWINDOW_H

#include "OsgQuickWindow.h"
#include <QQmlComponent>

class CrystalWindow : public OsgQuickWindow
{
    Q_OBJECT

public:
    CrystalWindow(QWindow *parent = nullptr);
    ~CrystalWindow();

public slots:


protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    osg::ref_ptr<osgEarth::MapNode> mMapNodeGeo;
    osg::ref_ptr<osg::Group> mMapRoot;

};

#endif // CRYSTALWINDOW_H
