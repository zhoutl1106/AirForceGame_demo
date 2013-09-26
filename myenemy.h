#ifndef MYENEMY_H
#define MYENEMY_H

#include <QPoint>

class MyEnemy
{
public:
    MyEnemy(QPoint p, int type);
    void moveDown();
    void hit();
    QPoint m_p;
    int m_type;
    int m_preType;
private:
    int m_speed;
    int m_hitCount;
};

#endif // MYENEMY_H
