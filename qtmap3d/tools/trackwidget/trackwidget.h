#ifndef TRACKWIDGET_H
#define TRACKWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class TrackWidget; }
QT_END_NAMESPACE

class TrackWidget : public QWidget
{
    Q_OBJECT

public:
    TrackWidget(QWidget *parent = nullptr);
    ~TrackWidget();

private:
    Ui::TrackWidget *ui;
};
#endif // TRACKWIDGET_H
