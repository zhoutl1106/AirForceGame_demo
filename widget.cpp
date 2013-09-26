#include "widget.h"
#include "ui_widget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setMouseTracking(true);
    setCursor(QCursor(Qt::BlankCursor));

    image[TYPE_ME] = QImage(":me.bmp");
    imageWidth = image[TYPE_ME].width()/2;
    image[TYPE_SMALL] = QImage(":small.bmp");
    image[TYPE_MEDIUM] = QImage(":medium.bmp");
    image[TYPE_BIG] = QImage(":big.bmp");
    image[TYPE_BOOM] = QImage(":boom.bmp");

    ammoTimer = new QTimer(this);
    ammoTimer->setInterval(30);
    connect(ammoTimer,SIGNAL(timeout()),this,SLOT(ammoTimeOut()));
    ammoTimer->start();

    enemyTimer = new QTimer(this);
    enemyTimer->setInterval(2000);
    connect(enemyTimer,SIGNAL(timeout()),this,SLOT(enemyTimeOut()));
    enemyTimer->start();

    isAmmoGenerateFlag = true;
    totalPoint = 0;
    ui->pushButton->setVisible(false);

    QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    currentMousePoint = e->pos();
}

void Widget::resizeEvent(QResizeEvent *e)
{
    ui->pushButton->move(width()/2 - 200,height()/2 - 100);
}

void Widget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.fillRect(0,0,width(),height(),QColor(192,192,192));
    p.drawImage(currentMousePoint,image[0]);
    p.fillRect(ammoPos.x(),ammoPos.y(),2,4,Qt::black);
    for(int i=0;i<enemyList.size();i++)
    {
        p.drawImage(enemyList.at(i).m_p,image[enemyList.at(i).m_type]);
        if(enemyList.at(i).m_type == TYPE_BOOM)
        {
            switch(enemyList.at(i).m_preType)
            {
            case TYPE_SMALL:totalPoint += 1000;break;
            case TYPE_MEDIUM:totalPoint += 5000;break;
            case TYPE_BIG:totalPoint += 30000;break;
            }

            if(totalPoint > 500000)
                enemyTimer->setInterval(100);
            else
                enemyTimer->setInterval(-0.004*totalPoint + 2100);



            enemyList.removeAt(i);
            i--;
        }
    }

    p.setFont(QFont("",20));
    p.drawText(0,50,QString::number(totalPoint));
}

void Widget::ammoTimeOut()
{
    //ammo
    if(isAmmoGenerateFlag)
    {
        ammoPos = QPoint(currentMousePoint.x()+imageWidth,currentMousePoint.y());
        isAmmoGenerateFlag = false;
    }
    else
    {
        ammoPos.setY(ammoPos.y() - 50);
        if(ammoPos.y() < 0)
            isAmmoGenerateFlag = true;
    }

    //enemy
    QList<MyEnemy>::iterator enemyIterator = enemyList.begin();
    while(enemyIterator < enemyList.end())
    {
        (*enemyIterator).moveDown();
        if(ammoPos.x() > (*enemyIterator).m_p.x() &&
                ammoPos.x() < (*enemyIterator).m_p.x() + image[(*enemyIterator).m_type].width() &&
                ammoPos.y() > (*enemyIterator).m_p.y() &&
                ammoPos.y() < (*enemyIterator).m_p.y() + image[(*enemyIterator).m_type].height() + 50)
        {
            (*enemyIterator).hit();
            isAmmoGenerateFlag = true;
        }

        if(currentMousePoint.x() > (*enemyIterator).m_p.x() &&
                currentMousePoint.x() < (*enemyIterator).m_p.x() + image[(*enemyIterator).m_type].width() &&
                currentMousePoint.y() > (*enemyIterator).m_p.y() &&
                currentMousePoint.y() < (*enemyIterator).m_p.y() + image[(*enemyIterator).m_type].height())
        {
            ammoTimer->stop();
            enemyTimer->stop();
            ui->pushButton->setVisible(true);
            ui->pushButton->setText("Game Over\nYour total point is "+QString::number(totalPoint));
            setCursor(QCursor(Qt::ArrowCursor));
        }

        enemyIterator++;
    }

    update();
}

void Widget::enemyTimeOut()
{
    int temp_x = qrand()%width() + imageWidth;
    int temp_type = qrand()%10;
    switch(temp_type)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        temp_type = TYPE_SMALL;
        break;
    case 6:
    case 7:
    case 8:
        temp_type = TYPE_MEDIUM;
        break;
    case 9:
        temp_type = TYPE_BIG;
    }

    MyEnemy temp = MyEnemy(QPoint(temp_x,0),temp_type);
    enemyList.append(temp);
}

void Widget::on_pushButton_clicked()
{
    totalPoint = 0;
    ammoTimer->start();
    enemyTimer->start();
    setCursor(QCursor(Qt::BlankCursor));
    ui->pushButton->setVisible(false);
    enemyList.clear();
    enemyTimer->setInterval(2000);
}
