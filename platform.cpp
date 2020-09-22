#include "platform.h"
#include <QDebug>

Platform::Platform(QObject *parent) : QObject(parent)
{
    QPixmap pic(":/pic/qrc/board-3.png");
    setPixmap(pic.scaledToWidth(100));
    QRandomGenerator ran;
    monster_gen=1;





    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(monster_move()));
    timer->start(10);

//    QTimer* timer_gen = new QTimer();
//    connect(timer,SIGNAL(timeout()),this,SLOT(generate()));
//    timer_gen->start(5000);


}

void Platform::generate()
{
//    if(monster_gen){

//        mons=new Monster();
//        scene()->addItem(mons);
//        mons->setPos(x()+18,y()-35);

//    }
}

void Platform::move()
{

}

void Platform::pause()
{

}

void Platform::start()
{

}

void Platform::monster_move()
{
//    if(monster_gen)
//        mons->setPos(x()+18,y()-35);
}

