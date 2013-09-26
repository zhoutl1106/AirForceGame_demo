#include "myenemy.h"
#include <QDebug>

MyEnemy::MyEnemy(QPoint p, int type)
{
    m_p = p;
    m_type = type;
    m_preType = type;
    m_hitCount = 0;

    switch(type)
    {
    case 1:m_speed = 10;break;
    case 2:m_speed = 7;break;
    case 3:m_speed = 3;break;
    }
}

void MyEnemy::moveDown()
{
    m_p.setY(m_p.y()+m_speed);
}

void MyEnemy::hit()
{
    m_hitCount ++;
    switch(m_type)
    {
    case 1:if(m_hitCount > 0)m_type = 4;break;
    case 2:if(m_hitCount > 5)m_type = 4;break;
    case 3:if(m_hitCount > 30)m_type = 4;break;
    }
}
