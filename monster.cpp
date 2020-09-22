#include "monster.h"
#include <QDebug>
Monster::Monster() : QObject()
{
    QPixmap pic(":/pic/qrc/monster.png");
    setPixmap(pic.scaledToWidth(50));
    QTimer *timer =new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(check_bound()));
    timer->start(10);
}

void Monster::check_bound()
{
    if(y()>=700-35){
        delete this;
    }
}
