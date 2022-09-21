#ifndef TRACKWIDGET_H
#define TRACKWIDGET_H

#include <QWidget>


class QQuickWidget;

class TrackWidget : public QWidget
{
    Q_OBJECT

public:
    TrackWidget(QWidget *parent = nullptr);

private:
    QQuickWidget *mQQuickWidget;

};
#endif // TRACKWIDGET_H
