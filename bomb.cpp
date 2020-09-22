#include "bomb.h"
#include <QDebug>
Bomb::Bomb() : QObject()
{

    QPixmap pic(":/pic/qrc/bomb.png");
    setPixmap(pic.scaledToHeight(75));

    timer_b=new QTimer();
    connect(timer_b,SIGNAL(timeout()),this,SLOT(fly()));

    timer_b->start(20);

    QTimer* test = new QTimer();
    test->start(10);
    timer_b=test;
}

void Bomb::pause()
{
    stop=1;
    timer_b->stop();
}

void Bomb::startgo()
{
    stop=0;
    timer_b->start(20);
}

void Bomb::fly()
{
    (dy<10)?dy+=0.11:dy=10;

    if(!stop)
        setY(y()+dy);

}
