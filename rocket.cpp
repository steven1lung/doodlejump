#include "rocket.h"

Rocket::Rocket(QObject *parent) : QObject(parent)
{
    QPixmap pic(":/pic/qrc/rocket.png");
    setPixmap(pic.scaledToWidth(50));

    timer=new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(check()));
    timer->start(10);
}

void Rocket::pause()
{
    timer->stop();
}

void Rocket::start()
{
    timer->start(10);
}

void Rocket::check()
{
    if(y()>700){
        scene()->removeItem(this);
        delete this;
    }
}
