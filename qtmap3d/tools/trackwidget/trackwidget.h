#ifndef TRACKWIDGET_H
#define TRACKWIDGET_H

#include <QJsonValue>
#include <QWidget>


class QQuickWidget;

class TrackWidget : public QWidget
{
    Q_OBJECT

public:
    TrackWidget(QWidget *parent = nullptr);
    void addObject(double latitude , double longitude , double height,
                   QString name, QString type, QJsonObject info);
    void getChangeCoordinates(QString mname, double latitude , double longitude , double height);

public slots:
    Q_INVOKABLE double getLatitude();
    Q_INVOKABLE double getLongitude();
    Q_INVOKABLE double getHeight();
    Q_INVOKABLE QString getName();
    Q_INVOKABLE QString getType();
    Q_INVOKABLE QJsonValue getInfo();
     void onClickedCloseMenu();

signals:
    Q_INVOKABLE void onPin (bool t);
    Q_INVOKABLE void objectAdded ();
    Q_INVOKABLE void closeMenu();
    Q_INVOKABLE void chengeCoordinates(QString mname, double latitude , double longitude , double height);

private:
    QQuickWidget *mQQuickWidget;
    double mLatitude;
    double mLongitude;
    double mHeight;
    QString mName;
    QString mType;
    QJsonValue mInfo;

};
#endif // TRACKWIDGET_H
