#ifndef LOCATIONWIDGET_H
#define LOCATIONWIDGET_H

#include <QWidget>

class QQuickWidget;

class LocationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LocationWidget(QWidget *parent = nullptr);
    void addItemPositio(double latitude ,double longitude ,double altitude);


public slots:

signals:
    void goPosition(float latitude ,float longitude);

private:
    QQuickWidget *mQQuickWidget;
private slots:

signals :
   void itemPositionAdd(double latitude ,double longitude ,double altitude);
};

#endif // LOCATIONWIDGET_H
