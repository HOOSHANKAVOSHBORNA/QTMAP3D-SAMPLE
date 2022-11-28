#ifndef CRYSTALWINDOW_H
#define CRYSTALWINDOW_H

#include <QQmlComponent>
#include "OsgQuickWindow.h"

class CrystalPluginInfo;
class CrystalPluginInterface;

class CrystalWindow : public OsgQuickWindow
{
    Q_OBJECT
    Q_PROPERTY(qreal headingAngle READ headingAngle WRITE setHeadingAngle NOTIFY headingAngleChanged)

public:
    CrystalWindow(QWindow *parent = nullptr);
    ~CrystalWindow();

    qreal headingAngle() const;

signals:
    void sideItemCreated(int index, QObject *pSideItem);
    void toolboxItemCreated(QString itemName, QString categoryName,
                            CrystalPluginInterface *pInterface);
    void toolboxItemClicked(QString itemName, QString categoryName);

    void homeButtonClicked();
    void projectionButtonClicked();
    void zoomInButtonClicked();
    void zoomOutButtonClicked();
    void upButtonClicked();
    void downButtonClicked();
    void leftButtonClicked();
    void rightButtonClicked();
    void rotateUpButtonClicked();
    void rotateDownButtonClicked();
    void rotateLeftButtonClicked();
    void rotateRightButtonClicked();

    void headingAngleChanged(qreal angle);

public slots:
    void initializePluginsUI(std::list<CrystalPluginInfo> pluginsInfoList);
    void setHeadingAngle(qreal angle);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    qreal m_headingAngle = 0.0;
};

#endif // CRYSTALWINDOW_H
