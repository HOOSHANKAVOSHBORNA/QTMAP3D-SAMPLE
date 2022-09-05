#ifndef GETDATA_H
#define GETDATA_H

#include <QWidget>

class GetData : public QWidget
{
    Q_OBJECT
public:
       explicit GetData(QWidget *parent = nullptr);
        void setRotate(float t_rotate);
signals:
        void rotateChange(float t_newRotate);
public slots:
    Q_INVOKABLE int getRotate();

private:
    float m_rotate;
};

#endif // GETDATA_H
