#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include "myenemy.h"

#define TYPE_ME 0
#define TYPE_SMALL 1
#define TYPE_MEDIUM 2
#define TYPE_BIG 3
#define TYPE_BOOM 4

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);

private slots:
    void ammoTimeOut();
    void enemyTimeOut();
    
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QPoint currentMousePoint;
    QImage image[5];
    int imageWidth;
    QTimer *ammoTimer;
    QTimer *enemyTimer;

    QPoint ammoPos;
    bool isAmmoGenerateFlag;
    QList<MyEnemy> enemyList;

    int totalPoint;

};

#endif // WIDGET_H
