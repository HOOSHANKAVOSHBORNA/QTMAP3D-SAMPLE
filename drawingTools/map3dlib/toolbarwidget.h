#ifndef TOOLBARWIDGET_H
#define TOOLBARWIDGET_H

#include <QWidget>
#include <QVariant>
#include <QtQuickWidgets/QQuickWidget>
class QQuickWidget;

class ToolBarWidget : public QQuickWidget
{
    Q_OBJECT
public:
    enum Category{
        File,
        Draw,
        Effect,
        Feature,
        Image,
        Measure,
        Model,
        Terrain,
        Analyze,
        Other
    };

public:
    ToolBarWidget(QWidget *parent = nullptr);
    void addItem(Category category, QString name , QString icon = "", bool checkable=false);
    Q_INVOKABLE  QVariant getItemName() ;
    Q_INVOKABLE  QVariant getItemIcon() ;
    Q_INVOKABLE  QVariant getItemCategory() ;
    void setClose();
public slots:
    void onGetItemClicked(QString category , QString name, bool ischeck);
    void setSizeWidget(bool t);

signals:
    void onItemClicked(Category category ,QString name,bool ischeck);


protected:
    void resizeEvent(QResizeEvent* event) override;
private:
    QString categoryString(Category category);
    Category categoryEnum(QString category);
private slots:

signals:
   void changeSize(bool t);
   Q_INVOKABLE void isclose();
   Q_INVOKABLE void onPin(bool t);
   Q_INVOKABLE void itemAdded (bool t);
   Q_INVOKABLE void isDock(int height);
private:
    QVariant    mItemName;
    QVariant    mItemIcon;
    QVariant    mItemCategory;

};
#endif // TOOLBARWIDGET_H
