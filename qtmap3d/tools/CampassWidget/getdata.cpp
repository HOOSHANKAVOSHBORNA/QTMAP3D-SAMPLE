#include "getdata.h"

GetData::GetData(QWidget *parent) : QWidget(parent)
{

}

void GetData::setRotate(float t_rotate)
{
    if (t_rotate!=m_rotate){
        m_rotate = t_rotate;
        emit rotateChange(t_rotate);
    }
}

int GetData::getRotate()
{
    return m_rotate;
}
