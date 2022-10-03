#ifndef LOCATIONWIDGET_H
#define LOCATIONWIDGET_H

#include <QWidget>
#include <osgEarth/Viewpoint>

class QQuickWidget;
namespace  osgEarth{
class Viewpoint;
}


class LocationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LocationWidget(QWidget *parent = nullptr);
    void addViewPoint(osgEarth::Viewpoint point);


public slots:
    void setMousePosition(double latitude ,double longitude ,double altitude);

signals:
    void goPosition(float latitude ,float longitude ,float range);
    void onClickedPosition(osgEarth::Viewpoint point);
    void sendNamePosition(QString name);

private:
    QQuickWidget *mQQuickWidget;
    QList <osgEarth::Viewpoint> mListViewpoint;
private slots:

signals :
   void savePosition(QString str , double x  , double y);
   void onOpenWidget(bool a , bool b, bool c);
   void changePosition(double latitude ,double longitude ,double altitude);
   void onCurrentClicked(QString name);
};

#endif // LOCATIONWIDGET_H
